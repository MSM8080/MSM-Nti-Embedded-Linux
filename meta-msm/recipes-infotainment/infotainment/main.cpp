#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <memory>
#include <fstream>
#include "qt_screen_theme.h"
#include "qt_screen_sensors.h"
#include "user_repo.h"
#include "user.h"
#include "ArduinoComm.hpp"

int main(int argc, char *argv[])
{


    // initilize repo by path-pc
    std::string path_pc = "/home/msm/Desktop/2.Technical/6.final-project/msm_project/users_data.txt";
    std::string path_rpi = "/home/weston/users_data.txt";

    // switch betwwen path-pc & path-rpi
    std::unique_ptr<UserRepo> user_repo = std::make_unique<UserRepo>(UserRepo{path_pc});
    if(!user_repo->is_exist())
    {
        // path-rpi
        std::unique_ptr<UserRepo> user_repo_tmp = std::make_unique<UserRepo>(UserRepo{path_rpi});
        user_repo.swap(user_repo_tmp);
        qDebug() << "file is exist: " << user_repo->is_exist();
    }

    // initilize user id path
    std::string id_path_pc = "/home/msm/Desktop/2.Technical/6.final-project/msm_project/login.txt";
    std::string id_path_rpi = "/home/weston/login.txt";

    // switch betwwen id-path-pc & id-path-rpi
    std::unique_ptr<std::fstream> id_file = std::make_unique<std::fstream>();
    id_file->open(id_path_pc, std::ios::in);
    if(!id_file->is_open())
    {
        std::unique_ptr<std::fstream> id_file_tmp = std::make_unique<std::fstream>();
        id_file_tmp->open(id_path_rpi, std::ios::in);
        id_file.swap(id_file_tmp);
    }

    // read the id of user
    std::string id;
    *id_file >> id;

    // initilize user
    std::unique_ptr<User> user = std::make_unique<User>(user_repo->get_user_by_id(id));

    // initilize arduino
    std::unique_ptr<ArduinoComm> arduino =  std::make_unique<ArduinoComm>("/dev/ttyACM0",9600);
    if(!arduino->openPort())
    {
        qDebug() << "Arduino port can't open!!";
    }

    // initlize gui app & qnl engine
    QGuiApplication g_app(argc, argv);
    QQmlApplicationEngine engine;

    // connection for handling failure
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &g_app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // connection for passing current user to qt_theme_changer & qt_sensors_changer
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &g_app,
        [&](QObject *obj, const QUrl &) {
            if (obj) {
                QtScreenTheme* qt_theme_changer = QtScreenTheme::GetInstance(nullptr);
                qt_theme_changer->set_user(user.get());
                emit qt_theme_changer->themeChanged();

                QtScreenSensors* qt_sensors_changer = QtScreenSensors::GetInstance(nullptr);
                qt_sensors_changer->set_user(user.get());
                emit qt_sensors_changer->angleChanged();

                qDebug() << "QML loaded successfully!";
            }
        });

    // initilze timer for recieve & write for arduino
    QTimer* timer = new QTimer(&g_app);
    QObject::connect(timer, &QTimer::timeout,&g_app, [&](){
        arduino->pollAnalogReadings();
        QtScreenSensors* qt_sensors_changer = QtScreenSensors::GetInstance(nullptr);
        // recieve data
        int temp  = static_cast<int>(arduino->getAnalog(0));
        qt_sensors_changer->set_temp(temp);
        // qt_sensors_changer->set_temp(30);

        int speed = static_cast<int>(arduino->getAnalog(1));
        speed = 240.0 * (speed / 1024.0);
        int rpm = speed / 30.0;
        qt_sensors_changer->set_speed(speed);
        qt_sensors_changer->set_rpm(rpm);
        // qt_sensors_changer->set_speed(0);
        // qt_sensors_changer->set_rpm(0);

        // int fuel = static_cast<int>(arduino->getAnalog(3));
        // fuel = 60.0 * (fuel / 1024.0);
        // qt_sensors_changer->set_fuel(fuel);
        qt_sensors_changer->set_fuel(30);

        qDebug() << "Arduino recived data: " << " temp: " << temp << " speed " << speed << " rpm " << rpm;

        // send data
        int angle = qt_sensors_changer->get_angle();
        if(angle < 0)
            angle *= -1;
        arduino->setServo(angle);
        qDebug() << "Arduino send data: " << " angle: " << angle;
    });

    // start the timer every 10ms
    timer->start(500); // 10ms

    // connection for saving the current repo into file
    QObject::connect(
        &g_app,
        &QCoreApplication::aboutToQuit,
        [&](){
                user->set_passwd("semoo");
                user_repo->update_repo(*user);
                user_repo->print_repo();
                user_repo->store_repo();
                arduino->closePort();
            }
        );

    // ensure single instance of QtScreenTheme
    qmlRegisterSingletonInstance("msm_project", 1, 0, "QtScreenTheme", QtScreenTheme::GetInstance(nullptr));

    // ensure single instance of QtScreenSensors
    qmlRegisterSingletonInstance("msm_project", 1, 0, "QtScreenSensors", QtScreenSensors::GetInstance(nullptr));

    // parse the qml
    engine.loadFromModule("msm_project", "Main");

    // start event-driven system
    return g_app.exec();
}




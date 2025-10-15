#ifndef QT_SCREEN_SENSORS_H
#define QT_SCREEN_SENSORS_H

#include <QObject>
#include <QQmlEngine>
#include "user.h"

class QtScreenSensors : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(int angle READ get_angle WRITE set_angle NOTIFY angleChanged FINAL)
    Q_PROPERTY(int speed READ get_speed WRITE set_speed NOTIFY speedChanged FINAL)
    Q_PROPERTY(int rpm READ get_rpm WRITE set_rpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(int temp READ get_temp WRITE set_temp NOTIFY tempChanged FINAL)
    Q_PROPERTY(int fuel READ get_fuel WRITE set_fuel NOTIFY fuelChanged FINAL)

public:
    explicit QtScreenSensors(QObject *parent = nullptr);
    // Singletons should not be cloneable.
    QtScreenSensors(QtScreenSensors &other) = delete;
    // Singletons should not be assignable.
    void operator=(const QtScreenSensors &) = delete;

    // get the only instance created of QtScreenTheme
    static QtScreenSensors *GetInstance(QObject *parent)
    {
        if(_this == nullptr)
        {
            _this = new QtScreenSensors(parent);
        }
        return _this;
    }

    // connect functions
    int get_angle();
    int get_speed();
    int get_rpm();
    int get_temp();
    int get_fuel();

    // signal functions
    Q_INVOKABLE void set_angle(int);

    // set functions
    void set_user(User *user);
    void set_speed(int);
    void set_rpm(int);
    void set_temp(int);
    void set_fuel(int);

signals:
    void angleChanged();
    void speedChanged();
    void rpmChanged();
    void tempChanged();
    void fuelChanged();

protected:
    static QtScreenSensors* _this;
    User* _user;

private:
    int _angle;
    int _speed;
    int _rpm;
    int _temp;
    int _fuel;

};

#endif // QT_SCREEN_SENSORS_H

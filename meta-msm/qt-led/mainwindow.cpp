#include "mainwindow.h"
#include "./ui_mainwindow.h"

// real led on gpio 4 pin
// QString led_path = "/sys/class/gpio/gpio4/value";

// test led file
QString led_path = "./file.txt";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _led_accessibale(1)
{
    ui->setupUi(this);
    QObject::connect(ui->LedButton, SIGNAL(pressed()) , this, SLOT(on_LedButton_pressed()));
    QObject::connect(ui->LedButton, SIGNAL(released()) , this, SLOT(on_LedButton_released()));

    l = new Led{led_path};

    // check led file
    if(!l->is_led_accessible())
    {
        qDebug() << "can't write on led file!! \n";
        _led_accessibale = 0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete l;
}

qint8 MainWindow::is_led_accessibale()
{
    return _led_accessibale;
}

void MainWindow::on_LedButton_pressed()
{
    l->turn_led_on();
    qDebug() << "Led on \n";
}


void MainWindow::on_LedButton_released()
{
    l->turn_led_off();
    qDebug() << "Led off \n";
}

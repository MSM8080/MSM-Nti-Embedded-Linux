#include "mainwindow.h"
#include <QApplication>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(!w.is_led_accessibale())
    {
        return a.exec();
    }
    w.show();
    return a.exec();
}

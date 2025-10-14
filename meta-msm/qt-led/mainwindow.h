#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "led-switch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Led* l;
    qint8 _led_accessibale;
    qint8 is_led_accessibale();

private slots:
    void on_LedButton_pressed();

    void on_LedButton_released();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H



#include "qt_screen_sensors.h"
/***********************************************************
 * Class QtScreenTheme
 ***********************************************************/
QtScreenSensors* QtScreenSensors::_this = nullptr;
// ---------------------------------------------------------
QtScreenSensors::QtScreenSensors(QObject *parent): QObject{parent}, _user{nullptr}
{

}
// ---------------------------------------------------------
int QtScreenSensors::get_angle()
{
    return _angle;
}
// ---------------------------------------------------------
int QtScreenSensors::get_speed()
{
    return _speed;
}
// ---------------------------------------------------------
int QtScreenSensors::get_rpm()
{
    return _rpm;
}
// ---------------------------------------------------------
int QtScreenSensors::get_temp()
{
    return _temp;
}
// ---------------------------------------------------------
int QtScreenSensors::get_fuel()
{
    return _fuel;
}
// ---------------------------------------------------------
Q_INVOKABLE void QtScreenSensors::set_angle(int new_angle)
{
    _angle = new_angle;
    _user->set_angle(std::to_string(_angle));
    emit angleChanged();
}
// ---------------------------------------------------------
void QtScreenSensors::set_speed(int new_speed)
{
    _speed = new_speed;
    emit speedChanged();
}

// ---------------------------------------------------------
void QtScreenSensors::set_rpm(int new_rpm)
{
    _rpm = new_rpm;
    emit rpmChanged();
}
// ---------------------------------------------------------
void QtScreenSensors::set_temp(int new_temp)
{
    _temp = new_temp;
    emit tempChanged();
}
// ---------------------------------------------------------
void QtScreenSensors::set_fuel(int new_fuel)
{
    _fuel = new_fuel;
    emit fuelChanged();
}
// ---------------------------------------------------------
void QtScreenSensors::set_user(User *user)
{
    _user = user;
    _angle = std::stoi(_user->get_angle());
    emit angleChanged();
}

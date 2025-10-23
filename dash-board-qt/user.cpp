#include "user.h"
/***********************************************************
 * Class User
 ***********************************************************/
User::User(){}
// --------------------------------------------------------
int User::get_id() const
{
    return _id;
}
// --------------------------------------------------------
std::string User::get_name() const
{
    return _name;
}
// --------------------------------------------------------
std::string User::get_passwd() const
{
    return _passwd;
}
// --------------------------------------------------------
std::string User::get_theme() const
{
    return _theme;
}
// --------------------------------------------------------
std::string User::get_angle() const
{
    return _angle;
}
// --------------------------------------------------------
void User::set_id(int id)
{
    _id = id;
}
// --------------------------------------------------------
void User::set_name(std::string name)
{
    _name = name;
}
// --------------------------------------------------------
void User::set_passwd(std::string passwd)
{
    _passwd = passwd;
}
// --------------------------------------------------------
void User::set_theme(std::string theme)
{
    _theme = theme;
}
// --------------------------------------------------------
void User::set_angle(std::string angle)
{
    _angle = angle;
}
// --------------------------------------------------------
void User::set_exist(bool exist)
{
    _user_exist = exist;
}
// --------------------------------------------------------
bool User::is_exist()
{
    return _user_exist;
}
// --------------------------------------------------------

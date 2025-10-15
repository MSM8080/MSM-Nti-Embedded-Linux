#include "qt_screen_theme.h"
/***********************************************************
 * Class QtScreenTheme
 ***********************************************************/
QtScreenTheme* QtScreenTheme::_this = nullptr;
// ---------------------------------------------------------
QtScreenTheme::QtScreenTheme(QObject *parent): QObject{parent}, _user(nullptr)
{

}
// ---------------------------------------------------------
QString QtScreenTheme::get_theme()
{
    // qDebug() << "get done" << _theme;
    return _theme;
}
// ---------------------------------------------------------
Q_INVOKABLE void QtScreenTheme::set_theme(QString new_theme)
{
    _theme = new_theme;
    emit themeChanged();

    _user->set_theme(_theme.toStdString());
    // qDebug() << _user->get_id();
    // qDebug() << _user->get_name();
    // qDebug() << _user->get_passwd();
    // qDebug() << _user->get_theme();

}
// ---------------------------------------------------------
void QtScreenTheme::set_user(User *user)
{
    _user = user;
    _theme = QString::fromStdString(_user->get_theme());
}



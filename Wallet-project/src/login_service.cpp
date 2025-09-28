#include "../include/login_service.h"

// -------------------------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                          Class LoginService                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// -------------------------------------------------------------------
LoginService::LoginService(App* app) : _name("\0"), _passwd("\0"), _name_exist(0) , _passwd_correct(0)
{
    _app = app;
    _repo = _app->get_current_repo();
}
// -------------------------------------------------------------------
void LoginService::login_name(std::string name)
{
    // search for user by name in the repo
    _new_user = _repo->get_user_by_name(name);

    // check if user exist
    if(_new_user.is_exist())
    {
        _name_exist = 1;
        _name = name;
    }
    else
    {
        _name_exist = 0;
    }
    
    return;
}
// -------------------------------------------------------------------
void LoginService::login_passwd(std::string passwd)
{
    
    if(_new_user.get_passwd() == passwd)
    {
        _passwd_correct = 1;
        // change current user in app to the new user
        _app->set_current_user(new User{_new_user});        
    }
    else
        _passwd_correct = 0;

    return;
}
// -------------------------------------------------------------------
bool LoginService::is_name_exist()
{
    return _name_exist;
}
// -------------------------------------------------------------------
bool LoginService::is_passwd_correct()
{
    return _passwd_correct;
}

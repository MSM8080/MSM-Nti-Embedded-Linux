#include "app.h"
/***********************************************************
 * Class App
 ***********************************************************/
App::App(std::string users_path)
{
    _user_repo = std::make_unique<UserRepo>(users_path);
    _user = std::make_unique<User>();
}
// ---------------------------------------------------------
UserRepo* App::get_current_repo()
{
    return _user_repo.get();
}
// ---------------------------------------------------------
User* App::get_currrent_user()
{
    return _user.get();
}
// ---------------------------------------------------------
void App::set_current_user(User* user)
{
    _user.reset(user);
}

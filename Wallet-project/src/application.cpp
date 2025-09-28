#include "application.h"
// -------------------------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                          Class App                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// -------------------------------------------------------------------
App::App(const std::string& users_path, std::string transictions_path)
{
    _user_repo = std::make_unique<UserRepo>(users_path);
    _user = std::make_unique<User>();
    // _navigator = std::make_unique<PageNavigator>(this);
    _navigator = new PageNavigator(this);

    // _user_repo->print_users_data();

}
// -------------------------------------------------------------------
void App::run()
{
    _navigator->navigate();
}
// -------------------------------------------------------------------
UserRepo* App::get_current_repo()
{
    return _user_repo.get();
}
// -------------------------------------------------------------------
User* App::get_currrent_user()
{
    return _user.get();
}
// -------------------------------------------------------------------
void App::set_current_user(User* user)
{
    _user.reset(user);
}
// -------------------------------------------------------------------
void App::save_app_data()
{
    _user_repo->store_user_data();

    std::cout << "\033[1;36m \n## Thanks for using our services\n\033[0m" << std::endl;
}
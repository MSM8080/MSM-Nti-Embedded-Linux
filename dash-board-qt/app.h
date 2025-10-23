#ifndef APP_H
#define APP_H
#include <memory>
#include "user.h"
#include "user_repo.h"
#include "qt_screen_theme.h"
// --------------------------------------------------------
class App
{
public:
    App(const App&) = delete;
    App() = delete;
    App(std::string users_path);
    void run();

    // get functions
    UserRepo* get_current_repo();
    User* get_currrent_user();

    // set functions
    void set_current_user(User* user);

protected:
    std::unique_ptr<UserRepo> _user_repo;
    std::unique_ptr<User> _user;
};
// --------------------------------------------------------
#endif // APP_H

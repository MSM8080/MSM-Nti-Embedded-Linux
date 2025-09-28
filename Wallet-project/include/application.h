#pragma once

#include "navigator.h"
#include "user_repository.h"

class UserRepo;
class User;
class PageNavigator;

// --------------------------------------------------------------------------------------
/*
 * provide tools access current user data
 */ 
class App
{
    public:
        App(const App&) = delete;
        App() = delete;
        App(std::string users_path, std::string transictions_path);
        void run();

        // get functions
        UserRepo* get_current_repo();
        User* get_currrent_user();

        // set functions
        void set_current_user(User* user);
  
    protected:
        std::unique_ptr<UserRepo> _user_repo;
        std::unique_ptr<User> _user;      
        // std::unique_ptr<PageNavigator> _navigator;
        PageNavigator* _navigator;
};

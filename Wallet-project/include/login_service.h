#pragma once 
#include "application.h"
#include "user_repository.h"

class App;
class UserRepo;


// --------------------------------------------------------------------------------------
/*
 * provide tools to login a user
 */ 

class LoginService
{
    public:
        LoginService(App* app);
        void login_name(std::string name);
        void login_passwd(std::string passwd);
        bool is_name_exist();
        bool is_passwd_correct();

    protected:
        UserRepo* _repo;
        App* _app;
        std::string _name;
        std::string _passwd;
        bool _name_exist;
        bool _passwd_correct;
        User _new_user;
};
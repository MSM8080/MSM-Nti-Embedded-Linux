# pragma once
#include <string>

#include "utilities.h"
#include "user.h"

class User;

// --------------------------------------------------------------------------------------
/*
 * provide tools access repository of users
 */ 
class UserRepo
{
    public:
        UserRepo(const std::string &file_path);
        User get_user_by_name(std::string name);
        void update_user_data(const User &user);
        void store_user_data();
        void print_users_data();
        bool is_exist();
        bool is_empty();
        
    protected:
        std::vector<std::vector<std::string>> _users_data;  
        bool _repo_exist;
        bool _repo_empty;
        std::string _file_path;
};

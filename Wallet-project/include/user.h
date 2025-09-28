#pragma once
#include <iostream>
#include <map>
#include <string>

// --------------------------------------------------------------------------------------
/*
 * provide tools access current user data
 */ 
class User
{
    
    public:
        User();

        // get function
        int get_id() const; 
        std::string get_name() const;
        std::string get_passwd() const;
        double get_balance() const;
        
        // set function
        void set_id(int id);
        void set_name(std::string name);
        void set_balance(double balance);
        void set_passwd(std::string passwd);
        void set_exist(bool exist);
        bool is_exist();
        
        // others
        void increase_balance(double amount);
        void decrease_balance(double amount);

    protected:
        std::string _name;
        int _id;
        double _balance;
        std::string _passwd;
        bool _user_exist;
        
};
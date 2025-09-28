#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cstring>
#include "application.h"
#include "login_service.h"

class App;
class LoginService;
class PageNavigator;

// --------------------------------------------------------------------------------------
class Page 
{       
    public:
        // constructor & destructor
        Page(App* app);
        virtual ~Page();

        // virtual functions
        // virtual Page* page_check_and_reaction(std::string s) = 0;
        virtual void print_page();
        virtual void prompt();
        
        // function
        void print_logo();
        void clear_page();
        std::unique_ptr<Page> get_next_page();

    protected:
        std::string _input;
        std::unique_ptr<Page> _next_page;
        App* _app;
        
        
};
// --------------------------------------------------------------------------------------
class LoginPage : public Page
{
    protected:
        std::string _user_name;
        std::string _user_passwd;
        unsigned int _user_id;
        std::unique_ptr<LoginService> _login;
        
    public:
        LoginPage(App* app);
        ~LoginPage();
        void prompt() override;
        void print_page() override;
  

};

// --------------------------------------------------------------------------------------
class MainPage : public Page
{
    protected:
        int _option;
    public:
        MainPage(App* app);
        ~MainPage();
        void print_page() override;
        void prompt() override;
  
};
// --------------------------------------------------------------------------------------
class WithdrawalPage : public Page
{
    protected:
        int _amount;

    public:
        WithdrawalPage(App* app);
        ~WithdrawalPage();
        void print_page() override;
        void prompt() override;
  
};
// --------------------------------------------------------------------------------------
class DepositPage : public Page
{
    protected:
        int _amount;

    public:
        DepositPage(App* app);
        ~DepositPage();
        void print_page() override;
        void prompt() override;
  
};
// --------------------------------------------------------------------------------------
class TransferPage : public Page
{
    protected:
        int _amount;

    public:
        TransferPage(App* app);
        ~TransferPage();
        void print_page() override;
        void prompt() override;
  
};
// --------------------------------------------------------------------------------------
class ChangePINPage : public Page
{
    protected:
        std::string _new_passwd;

    public:
        ChangePINPage(App* app);
        ~ChangePINPage();
        void print_page() override;
        void prompt() override;
        
};
// --------------------------------------------------------------------------------------
class WalletBalancePage : public Page
{
    protected:
        std::string _balance;
        const char* s;

    public:
        WalletBalancePage(App* app);
        ~WalletBalancePage();
        void print_page() override;
        void prompt() override;
};



// --------------------------------------------------------------------------------------
/*
*** cout ACII color code refrence ***

* std::cout << "\033[1;31m Red Text \033[0m" << std::endl;    // Red
* std::cout << "\033[1;32m Green Text \033[0m" << std::endl;  // Green
* std::cout << "\033[1;33m Yellow Text \033[0m" << std::endl; // Yellow
* std::cout << "\033[1;34m Blue Text \033[0m" << std::endl;   // Blue
* std::cout << "\033[1;35m Magenta Text \033[0m" << std::endl;// Magenta
* std::cout << "\033[1;36m Cyan Text \033[0m" << std::endl;   // Cyan
* std::cout << "\033[1;37m White Text \033[0m" << std::endl;  // White

*/

/*

    \033[1,30m    \033[0m          Black
    \033[1,31m    \033[0m          Red
    \033[1,32m    \033[0m         Green
    \033[1,33m    \033[0m          Yellow
    \033[1,34m    \033[0m          Blue
    \033[1,35m    \033[0m          Magenta
    \033[1,36m    \033[0m          Cyan
    \033[1,37m    \033[0m          White

*/
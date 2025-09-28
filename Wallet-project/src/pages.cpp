#include "../include/pages.h"

// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class Page #####################################################
// #####################################################################################################################
// -------------------------------------------------------------------
Page::Page(App* app) : _input("\0")
{
    _app = app;
}
// -------------------------------------------------------------------
Page::~Page()
{
}
// -------------------------------------------------------------------
void Page::print_page()
{
}
// -------------------------------------------------------------------
void Page::prompt()
{
}
// -------------------------------------------------------------------
void Page::print_logo()
{
    std::cout << std::endl;
    std::cout << "\033[1;35m_____________________________________________________________\033[0m\n";
    std::cout << "\033[1;35m_____________________________________________________________\033[0m\n";

    std::cout << "\033[1;36m ___  ___       _        _____      _       ______  __     __\033[0m\n";
    std::cout << "\033[1;36m|   \\/   |     / \\      / ____|    / \\     /  __  \\ \\ \\   / /\033[0m\n";
    std::cout << "\033[1;36m| |\\  /| |    / _ \\    | (___     / _ \\    | |__/ /  \\ \\_/ / \033[0m\n";
    std::cout << "\033[1;36m| | \\/ | |   / /_\\ \\    \\___ \\   / /_\\ \\   |  _  /    \\   /  \033[0m\n";
    std::cout << "\033[1;36m| |    | |  /  ___  \\   ____) | /  ___  \\  | | \\ \\     | |   \033[0m\n";
    std::cout << "\033[1;36m|_|    |_| /_/     \\_\\ |_____/ /_/     \\_\\ |_|  \\_\\    |_|  \033[0m\n";

    std::cout << "\033[1;35m_____________________________________________________________\033[0m\n";
    std::cout << "\033[1;35m_____________________________________________________________\033[0m\n";
    std::cout << std::endl;
}
// -------------------------------------------------------------------
void Page::clear_page()
{
    std::system("clear");
}
// -------------------------------------------------------------------
std::unique_ptr<Page> Page::get_next_page()
{
    // return with moving ownership to Navigator
    return std::move(_next_page);
}
// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class LoginPage ################################################
// #####################################################################################################################
// -------------------------------------------------------------------
LoginPage::LoginPage(App* app) : Page(app)
{
    _login = std::make_unique<LoginService>(_app);
}
// -------------------------------------------------------------------
LoginPage::~LoginPage() {}
// -------------------------------------------------------------------
void LoginPage::print_page()
{
    // welcomming message
    std::cout << std::endl;

    std::cout << "\033[1;36m            ## Welcome to Masary Wallet ##\n \033[0m";                   // in cyan
    std::cout << "\033[1;36m ## Where to finish all your transictions just in clics ##\n\n \033[0m"; // in cyan
    std::cout << "\033[1;36m ## Login: \n\n \033[0m";                                                // in cyan
    std::cout << "\033[1;31m (e) Exit\n \033[0m";                                                    // in RED

    std::cout << std::endl;
}
// -------------------------------------------------------------------
void LoginPage::prompt()
{
    // login with correct user name
    bool WANT_TO_EXIT = 0;
    bool NAME_IS_WRONG = 1;
    while (NAME_IS_WRONG && !WANT_TO_EXIT)
    {
        // take input
        std::cout << "\033[1;35mEnter your user name: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to exit
        if (_input[0] == 'e')
        {
            WANT_TO_EXIT = 1;
            _next_page = nullptr;
            return;
        }

        // login by name
        _login->login_name(_input);

        // check name exist
        // exist
        if (_login->is_name_exist()) 
        {
            NAME_IS_WRONG = 0;
            break;
        }
        // not exist
        else 
        {
            std::cout << "\033[1;31mWrong user name !!\033[0m" << std::endl;
        }
    }

    // login with correct user passwd
    bool PASSWD_IS_WRONG = 1;
    while (PASSWD_IS_WRONG && !WANT_TO_EXIT)
    {
        // take input
        std::cout << "\033[1;35mEnter your password: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to exit
        if (_input[0] == 'e')
        {
            WANT_TO_EXIT = 1;
            _next_page = nullptr;
            return;
        }

        // login by passwd
        _login->login_passwd(_input);

        // check [passwd is coreect
        // exist
        if (_login->is_passwd_correct()) 
        {
            PASSWD_IS_WRONG = 0;
            break;;
        }
        // not exist
        else 
        {
            std::cout << "\033[1;31mWrong password !!\033[0m" << std::endl;
            std::cout << std::flush;
        }
    }

    // if correct login , {assume yes for now} //
    if (!WANT_TO_EXIT)
    {
        std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
        _next_page = std::move(temp);
    }

    return;
}
// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class MainPage #################################################
// #####################################################################################################################
// -------------------------------------------------------------------
MainPage::MainPage(App* app) : Page(app)
{}
// -------------------------------------------------------------------
MainPage::~MainPage() {}
// -------------------------------------------------------------------
void MainPage::print_page()
{
    std::cout << std::endl;
    std::cout << "\033[1;36m ## Masary services: \n\n "; // in cyan

    std::cout << "\033[1;33m   (1) Change PIN\n \033[0m";                // in YELLOW
    std::cout << "\033[1;33m   (2) Withdrawal money\n \033[0m";          // in YELLOW
    std::cout << "\033[1;33m   (3) Deposit money\n \033[0m";             // in YELLOW
    std::cout << "\033[1;33m   (4) Transfer money \033[0m      \033[1;36m{Available soon}\n \033[0m";            // in YELLOW
    std::cout << "\033[1;33m   (5) Pay bills \033[0m           \033[1;36m{Available soon}\n \033[0m";                 // in YELLOW
    std::cout << "\033[1;33m   (6) Wallet balance\n \033[0m";            // in YELLOW
    std::cout << "\033[1;33m   (7) Transiction history \033[0m \033[1;36m{Available soon}\n \033[0m"; // in YELLOW

    std::cout << "\033[1;31m   (q) Quit\n \033[0m"; // in RED
    std::cout << "\033[1;31m   (e) Exit\n \033[0m"; // in RED

    std::cout << std::endl;
}
// -------------------------------------------------------------------
void MainPage::prompt()
{

    // acces on current repo & user
    UserRepo* current_repo = _app->get_current_repo();
    User* current_user = _app->get_currrent_user();

    // login with correct user name
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter your option: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // want to exit
        if (_input[0] == 'e')
        {
            // update users repo by new info about current user
            current_repo->update_user_data(*current_user);
            // end program
            _next_page = nullptr;
            break;
        }
        // want to back
        if (_input[0] == 'q')
        {
            // update users repo by new info about current user
            current_repo->update_user_data(*current_user);
            // logout
            std::unique_ptr<Page> temp = std::make_unique<LoginPage>(_app);
            _next_page = std::move(temp);
            break;
        }
        // some checks on user option here //

        // assume correct option //
        if (1)
        {
            _option = atoi(_input.c_str());
        }

        // change page based on options
        // Change PIN service
        if (_option == 1)
        {
            std::unique_ptr<Page> temp = std::make_unique<ChangePINPage>(_app);
            _next_page = std::move(temp);
            break;
        }
        // withdrawal service
        else if (_option == 2)
        {
            std::unique_ptr<Page> temp = std::make_unique<WithdrawalPage>(_app);
            _next_page = std::move(temp);
            break;
        }
        // deposit service
        else if (_option == 3)
        {
            std::unique_ptr<Page> temp = std::make_unique<DepositPage>(_app);
            _next_page = std::move(temp);
            break;
        }
        // Check wallet balance service
        else if (_option == 6)
        {
            std::unique_ptr<Page> temp = std::make_unique<WalletBalancePage>(_app);
            _next_page = std::move(temp);
            break;
        }        
    }
    return;
}
// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class WithdrawalPage ###########################################
// #####################################################################################################################
// -------------------------------------------------------------------
WithdrawalPage::WithdrawalPage(App* app) : Page(app) 
{}
// -------------------------------------------------------------------
WithdrawalPage::~WithdrawalPage() {}
// -------------------------------------------------------------------
void WithdrawalPage::print_page()
{
    std::cout << std::endl;

    std::cout << "\033[1;36m ## Withdrawal service: \n\n \033[0m"; // in cyan
    std::cout << "\033[1;31m   (b) back\n \033[0m";                // in RED
    std::cout << std::endl;
}
// -------------------------------------------------------------------
void WithdrawalPage::prompt()
{
    // access user
    User* current_user = _app->get_currrent_user();

    // enter amount of money fo withdrawal
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter withdrawal amount: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to back , {assume no for now} //
        if (_input[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }

        
        // check input is only numbers
        bool is_just_numbers = std::all_of(_input.begin(), _input.end(), ::isdigit);
        if (!is_just_numbers)
        {
            std::cout << "\033[1;31mInvalid number !!\033[0m" << std::endl;
            continue;
        }

        // check if it within balance of current user
        _amount = std::stod(_input);
        if(_amount > current_user->get_balance())
        {
            std::cout << "\033[1;31mNot enough balance !!\033[0m" << std::endl;
            continue;
        }

        // decrease user balance here and //
        current_user->decrease_balance(_amount);

        // print new balance
        printf("\033[1;35mYour new balance: \033[1;33m%lf$\n\033[0m",current_user->get_balance()); // in magemta & yellow
    }
    return;
}
// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class DepositPage ###########################################
// #####################################################################################################################
// -------------------------------------------------------------------
DepositPage::DepositPage(App* app) : Page(app) 
{}
// -------------------------------------------------------------------
DepositPage::~DepositPage() {}
// -------------------------------------------------------------------
void DepositPage::print_page()
{
    std::cout << std::endl;

    std::cout << "\033[1;36m ## Deposit service: \n\n \033[0m"; // in cyan
    std::cout << "\033[1;31m   (b) back\n \033[0m";             // in RED
    std::cout << std::endl;
}
// -------------------------------------------------------------------
void DepositPage::prompt()
{
    // access user
    User* current_user = _app->get_currrent_user();

    // enter amount of money fo withdrawal
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter deposit amount: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to back , {assume no for now} //
        if (_input[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }

        
        // check input is only numbers
        bool is_just_numbers = std::all_of(_input.begin(), _input.end(), ::isdigit);
        if (!is_just_numbers)
        {
            std::cout << "\033[1;31mInvalid number !!\033[0m" << std::endl;
            continue;
        }

        // increase user balance
        _amount = std::stod(_input);
        current_user->increase_balance(_amount);

        // print new balance
        printf("\033[1;35mYour new balance: \033[1;33m%lf$\n\033[0m",current_user->get_balance()); // in magemta & yellow
    }
    return;
}
// -------------------------------------------------------------------
// #####################################################################################################################
// #################################################### class TransferPage ###########################################
// #####################################################################################################################
// -------------------------------------------------------------------
TransferPage::TransferPage(App* app) : Page(app) 
{}
// -------------------------------------------------------------------
TransferPage::~TransferPage() {}
// -------------------------------------------------------------------
void TransferPage::print_page()
{
    std::cout << std::endl;

    std::cout << "\033[1;36m ## transfer service: \n\n \033[0m"; // in cyan
    std::cout << "\033[1;31m   (b) back\n \033[0m";              // in RED
    std::cout << std::endl;
}
// -------------------------------------------------------------------
void TransferPage::prompt()
{
    // enter amount of money fo withdrawal
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter user name to transfer to: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to back , {assume no for now} //
        if (_input[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }

        // some checks for user to transfer to which exist or not

        // if no user exist
        if (1)

            // some check on _input here is integers or not

            // assume correct input //
            if (1)
            {
                // make it integer
                _amount = atoi(_input.c_str());
            }

        // some checks on user balance here //

        // decrease user balance here and //

        // print the new balance //
    }
    return;
}

// -------------------------------------------------------------------
// #####################################################################################################################
// ########################################## class ChangePINPage ###########################################
// #####################################################################################################################
// -------------------------------------------------------------------
ChangePINPage::ChangePINPage(App* app) : Page(app)
{}
// -------------------------------------------------------------------
ChangePINPage::~ChangePINPage()
{}
// -------------------------------------------------------------------
void ChangePINPage::print_page()
{
    std::cout << std::endl;
    std::cout << "\033[1;36m ## Change passwd: \n\n \033[0m"; // in cyan
    std::cout << "\033[1;31m   (b) back\n \033[0m";           // in RED
    std::cout << std::endl;
}
void ChangePINPage::prompt()
{    
    // access user
    User* current_user = _app->get_currrent_user();

    // enter new passwd
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter new password: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to back , {assume no for now} //
        if (_input[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }

        // take input again
        std::cout << "\033[1;35mEnter new password again: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _new_passwd);

        // if i want to back , {assume no for now} //
        if (_new_passwd[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }

        // check if two new password entered is same or not
        if (_input != _new_passwd)
        {
            std::cout << "\033[1;31mNot Same passwords !!\n\r\033[0m"; // in RED
            continue;
        }
        else
        {
            current_user->set_passwd(_new_passwd);
            std::cout << "\033[1;32mPassword changed\n\r\033[0m"; // in GREEN
        }
    }
    return;
}

// -------------------------------------------------------------------
// #####################################################################################################################
// ########################################## class WalletBalancePage ###########################################
// #####################################################################################################################
// -------------------------------------------------------------------
WalletBalancePage::WalletBalancePage(App* app) : Page(app)
{}
// -------------------------------------------------------------------
WalletBalancePage::~WalletBalancePage(){}
// -------------------------------------------------------------------
void WalletBalancePage::print_page()
{
    std::cout << std::endl;
    std::cout << "\033[1;36m ## Wallet Balance: \n\n \033[0m"; // in cyan
    std::cout << "\033[1;33m   (s) show balance\n \033[0m";  // in YELLOW
    std::cout << "\033[1;31m   (b) back\n \033[0m";           // in RED
    std::cout << std::endl;
}
// -------------------------------------------------------------------
void WalletBalancePage::prompt()
{
    // access user
    User* current_user = _app->get_currrent_user();

    // print first time
    printf("\033[1;35mYour new balance: \033[1;33m%lf$\n\033[0m",current_user->get_balance()); // in magemta & yellow
    
    while (1)
    {
        // take input
        std::cout << "\033[1;35mEnter your option: \033[1;32m$\033[1;34m~: \033[0m"; // $~: in GREEN &
        std::getline(std::cin, _input);

        // if i want to back , {assume no for now} //
        if(_input[0] == 'b')
        {
            std::unique_ptr<Page> temp = std::make_unique<MainPage>(_app);
            _next_page = std::move(temp);
            break;
        }
        else if(_input[0] == 's')
        {
            printf("\033[1;35mYour new balance: \033[1;33m%lf$\n\033[0m",current_user->get_balance()); // in magemta & yellow
        }
    }
    return;
}
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

#include "../include/navigator.h"
#include "../include/pages.h"
#include "../include/utilities.h"
#include "../include/user_repository.h"
#include "../include/user.h"
#include "../include/application.h"

std::string users_path = "user_sample.csv";  
std::string transictions_path = "transaction_sample.csv";

class App;

int main()
{
    App app(users_path, transictions_path);
    app.run();

    
    return 0;
}


/*
    PageNavigator masary;
    masary.navigate();
*/

/*

    std::vector<std::vector<std::string>> data;

    std::string file_path= "user_sample.csv";
    std::unique_ptr<CSVFileRead> file = std::make_unique<CSVFileRead>(file_path);
    file->load_file();
    file->print_file();

    std::cout << std::endl;

    std::cout << file->read_value(2,1) << std::endl;
    file->change_value(1,2,"5555");
    file->change_value(2,2,"4444");
    data = file->get_data();

    std::cout << std::endl;

    file->print_file();


    std::unique_ptr<CSVFileWrite> file_2 = std::make_unique<CSVFileWrite>(file_path,data);
    file_2->update_file();
*/

/*
    std::string file_path= "user_sample.csv";
    std::unique_ptr<UserRepo> user = std::make_unique<UserRepo>(file_path);
    user->get_user_by_name("mohamed");
*/

/*
    std::string file_path = "user_sample.csv";
    std::unique_ptr<UserRepo> user_repo = std::make_unique<UserRepo>(file_path);
    std::cout << user_repo->is_empty() << std::endl;
    std::cout << user_repo->is_exist() << std::endl;
  
    std::unique_ptr<User> user = std::make_unique<User>();
    *user = user_repo->get_user_by_name("mohamed");
    std::cout << user->is_exist() << std::endl;
    std::cout << user->get_id() << std::endl;
    std::cout << user->get_name() << std::endl;
    std::cout << user->get_balance() << std::endl;
    std::cout << user->get_passwd() << std::endl;

    user->increase_balance(1000.222444);
    // user->decrease_balance(0.222);
    user->set_passwd("1945");

    std::cout << user->get_balance() << std::endl;
    std::cout << user->get_passwd() << std::endl;

    user_repo->update_user_data(*user);
    user_repo->print_users_data();
    user_repo->store_user_data();
*/
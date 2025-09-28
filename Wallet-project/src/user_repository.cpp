#include "../include/user_repository.h"
// -------------------------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                          Class UserRepo                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// -------------------------------------------------------------------
UserRepo::UserRepo(const std::string &file_path) : _repo_exist(0), _repo_empty(1), _file_path(file_path)
{
    // read the file
    std::unique_ptr<CSVFileRead> input_file = std::make_unique<CSVFileRead>(_file_path);

    // check if file exist
    if(input_file->is_exist())
        _repo_exist = 1;
    else 
        _repo_exist = 0;

    // load file 
    input_file->load_file();

    // check if file is empty
    if(input_file->is_empty())
        _repo_empty = 1;
    else
        _repo_empty = 0;

    // load users data
    _users_data = input_file->get_data();
}
// -------------------------------------------------------------------
User UserRepo::get_user_by_name(std::string name)
{
    User user;
    std::string id, balance, passwd;

    // search for user in users_data
    for(auto u : _users_data)
    {
        // found user
        if(u[1] == name)
        {
            user.set_id(std::stoi(u[0]));
            user.set_name(u[1]);
            user.set_balance(std::stod(u[2]));
            user.set_passwd(u[3]);
            user.set_exist(1);
            
            return user;
        }
    }

    // no user is founded
    user.set_exist(0);
    return user;
}
// -------------------------------------------------------------------
void UserRepo::update_user_data(const User &user)
{
    // get user data
    std::string id = std::to_string(user.get_id());
    std::string name = user.get_name();
    std::string balance = std::to_string(user.get_balance());
    std::string passwd = user.get_passwd();

    // update _users_data
    for(auto &u : _users_data)
    {
        if(u[0] == id)
        {
            u[1] = name;
            u[2] = balance;
            u[3] = passwd;
            break;
        }
    }
}
// -------------------------------------------------------------------
void UserRepo::store_user_data()
{
    // open file to write
     std::unique_ptr<CSVFileWrite> output_file = std::make_unique<CSVFileWrite>(_file_path,_users_data);

    
    // check if file exist
    if(output_file->is_exist())
    {
        _repo_exist = 1;
    }
    else 
    {
        _repo_exist = 0;
        return;
    }
    
    // write updated data to file
    output_file->update_file();
}
// -------------------------------------------------------------------
void UserRepo::print_users_data()
{
    for(auto row : _users_data)
    {
        for(auto element : row)
        {
            std::cout<< element << " ";
        }
        std::cout<< std::endl;
    }
}
// -------------------------------------------------------------------
bool UserRepo::is_empty()
{
    return _repo_empty;
}
// -------------------------------------------------------------------
bool UserRepo::is_exist()
{
    return _repo_exist;
}

#ifndef USER_REPO_H
#define USER_REPO_H
#include <string>
#include <vector>
#include "user.h"

class UserRepo
{
public:
    UserRepo(const std::string &file_path);
    User get_user_by_name(std::string name);
    User get_user_by_id(std::string id);
    void update_repo(const User &user);
    void store_repo();
    void print_repo();
    bool is_exist();
    bool is_empty();

protected:
    std::vector<std::vector<std::string>> _users_data;
    std::string _file_path;
    bool _repo_exist;
    bool _repo_empty;
};

#endif // USER_REPO_H

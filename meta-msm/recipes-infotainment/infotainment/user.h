#ifndef USER_H
#define USER_H
#include <string>
// --------------------------------------------------------
class User
{
public:
    User();

    // get function
    int get_id() const;
    std::string get_name() const;
    std::string get_passwd() const;
    std::string get_theme() const;
    std::string get_angle() const;


    // set function
    void set_id(int id);
    void set_name(std::string name);
    void set_passwd(std::string passwd);
    void set_theme(std::string theme);
    void set_angle(std::string angle);
    void set_exist(bool exist);

    bool is_exist();

protected:
    int _id;
    std::string _name;
    std::string _passwd;
    std::string _theme;
    std::string _angle;
    bool _user_exist;
};
// --------------------------------------------------------
#endif // USER_H

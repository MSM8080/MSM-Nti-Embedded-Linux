#ifndef CSV_H
#define CSV_H
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
// --------------------------------------------------------
class CSVRead
{
public:
    CSVRead(const std::string &file_path);
    std::vector<std::vector<std::string>> get_data();
    std::string read_value(int i, int j);
    void change_value(int i, int j, std::string value);
    void load_file();
    void print_file();
    bool is_empty();
    bool is_exist();

private:
    std::vector<std::vector<std::string>> _data;
    std::unique_ptr<std::fstream> _i_file;
    int _n_rows;
    bool _file_empty;
    bool _file_exist;
};
// --------------------------------------------------------
class CSVWrite
{
public:
    CSVWrite(const std::string &file_path, std::vector<std::vector<std::string>> data);
    void update_file();
    void print_file();
    bool is_exist();

protected:
    std::vector<std::vector<std::string>> _data;
    std::unique_ptr<std::fstream> _o_file;
    int _n_rows;
    bool _file_exist;
};
// --------------------------------------------------------
#endif // CSV_H


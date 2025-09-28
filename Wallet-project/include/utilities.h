#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

// --------------------------------------------------------------------------------------
class CSVFile
{
public:
    // functions
    CSVFile();
    virtual ~CSVFile();
    void print_file();
    bool is_exist();

protected:
    // members    
    std::vector<std::vector<std::string>> _data;
    int _n_rows; 
    bool _file_exist;   
};
/*
    std::vector<std::vector<std::string>> _data: [["id", "name", "balance", "password"],
                                                 ["0", "Abdo", "40000", "123dfg"],
                                                 ["1", "Mohamed", "10000", "pp23bn"]]
*/
// --------------------------------------------------------------------------------------
class CSVFileRead : public CSVFile
{
    public:
        // functions
        CSVFileRead(const std::string &file_path);
        std::string read_value(int i, int j);
        void change_value(int i, int j, std::string value);
        void load_file();
        std::vector<std::vector<std::string>> get_data();
        bool is_empty();
    protected:
        // members    
        std::unique_ptr<std::fstream> _i_file;
        bool _file_empty;
};
// --------------------------------------------------------------------------------------
class CSVFileWrite : public CSVFile
{
    public:
        // functions
        CSVFileWrite(const std::string &file_path, std::vector<std::vector<std::string>> data);
        void update_file();
    
    protected:
        // members    
        std::unique_ptr<std::fstream> _o_file;
};
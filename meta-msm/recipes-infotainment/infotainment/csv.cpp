#include <sstream>
#include <iostream>
#include "csv.h"
/***********************************************************
 * Class CSVRead
 ***********************************************************/
CSVRead::CSVRead(const std::string &file_path) : _file_empty(1), _file_exist(0), _n_rows(0)
{
    // initilze input file
    _i_file = std::make_unique<std::fstream>();
    _i_file->open(file_path,std::ios::in);

    // check if input file is open ??
    if (_i_file->is_open())
        _file_exist = 1;
    else
        _file_exist = 0;

    // get the number of rows
    std::string line;
    while (std::getline(*_i_file,line))
    {
        _n_rows++;
    }

    if(_n_rows == 0)
        _file_empty = 1;
    else
    {
        _file_empty = 0;
        // resize the _data vector
        _data.resize(_n_rows);
    }
}
// ---------------------------------------------------------
std::vector<std::vector<std::string>> CSVRead::get_data()
{
    return _data;
}
// ---------------------------------------------------------
std::string CSVRead::read_value(int i, int j)
{
    return _data[i][j];
}
// ---------------------------------------------------------
void CSVRead::change_value(int i, int j, std::string value)
{
    _data[i][j].clear();
    _data[i][j] = value;
}
// ---------------------------------------------------------
void CSVRead::load_file()
{
    // get the file ready to read from beggining
    _i_file->clear();  // clear eof flag
    _i_file->seekg(0,std::ios::beg);

    std::string line;
    std::string element;
    std::istringstream line_stream;

    for(auto &row : _data)
    {
        // read the line as string
        std::getline(*_i_file, line);
        // make line as stream itself
        line_stream.str(line);

        while (std::getline(line_stream, element, ','))
        {
            row.push_back(element);
            element.clear();
        }

        // clear them for new operation
        line.clear();
        line_stream.clear();
    }
}
// ---------------------------------------------------------
void CSVRead::print_file()
{
    for(auto row : _data)
    {
        for(auto element : row)
        {
            std::cout<< element << " ";
        }
        std::cout<< std::endl;
    }
}
// ---------------------------------------------------------
bool CSVRead::is_empty()
{
    return _file_empty;
}
// ---------------------------------------------------------
bool CSVRead::is_exist()
{
    return _file_exist;
}
/***********************************************************
 * Class CSVWrite
 ***********************************************************/
CSVWrite::CSVWrite(const std::string &file_path, std::vector<std::vector<std::string>> data) : _file_exist(0), _n_rows(0)
{
    // initilze output file
    _o_file = std::make_unique<std::fstream>();
    _o_file->open(file_path, std::ios::out | std::ios::trunc);


    // // check if output file is open ??
    if (_o_file->is_open())
        _file_exist = 1;
    else
        _file_exist = 0;

    _data = data;
}
// ---------------------------------------------------------
void CSVWrite::update_file()
{
    // get file ready to write
    _o_file->clear();
    _o_file->seekg(0,std::ios::beg);

    for(auto row : _data)
    {
        for(auto element : row)
        {
            *_o_file << element << ",";
        }
        *_o_file << std::endl;
    }
}
// ---------------------------------------------------------
void CSVWrite::print_file()
{
    for(auto row : _data)
    {
        for(auto element : row)
        {
            std::cout<< element << " ";
        }
        std::cout<< std::endl;
    }
}
// ---------------------------------------------------------
bool CSVWrite::is_exist()
{
    return _file_exist;
}
// ---------------------------------------------------------




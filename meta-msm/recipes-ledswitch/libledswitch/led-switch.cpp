#include "led-switch.h"
// --------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                   Class Led                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
// --------------------------------------------------
Led::Led(std::string path) : _led_accessible(0)
{    
    _led_file = new std::fstream;
    _led_file->open(path, std::ios::out);
    
    if(_led_file->is_open())
    {
        _led_accessible = 1;
        std::cout << " led file is open\n";
    }    
    
    else
    {
        _led_accessible = 0;
        std::cout << " led file not open !! \n";
    }
        
}
// --------------------------------------------------
Led::~Led()
{
    delete _led_file;
}
// --------------------------------------------------
void Led::turn_led_on()
{
    *_led_file << '1';
    std::cout << " led on \n";
}
// --------------------------------------------------
void Led::turn_led_off()
{
    *_led_file << '0';
    std::cout << " led off \n";
}
// --------------------------------------------
bool Led::is_led_accessible()
{
    return _led_accessible;
}
// --------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                   Class Switch                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
// --------------------------------------------------
Switch::Switch(std::string path) : _switch_state{'0'}, _switch_accessible{0}
{
    _switch_file = new std::fstream;
    _switch_file->open(path, std::ios::in);

    if(_switch_file->is_open())
    {
        std::cout << " switch file is open\n";
        _switch_accessible = 1;
    }
        
    else
    {
        std::cout << " switch file not open !! \n";
        _switch_accessible = 0;
    }
        
}
// --------------------------------------------------
Switch::~Switch()
{
    delete _switch_file;
}
// --------------------------------------------------
char Switch::switch_read()
{
    *_switch_file >> _switch_state;
    std::cout << " reading from switch file \n";
    return _switch_state;
}
// --------------------------------------------------
bool Switch::is_switch_accessible()
{
    return _switch_accessible;
}

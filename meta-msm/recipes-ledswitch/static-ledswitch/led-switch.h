#pragma once
#include <iostream>
#include <fstream>
// --------------------------------------------------
class Led
{
    public:
        Led(std::string path);
        ~Led();
        void turn_led_on();
        void turn_led_off();
        bool is_led_accessible();

    protected:
        bool _led_accessible;
        std::fstream* _led_file;
};
// --------------------------------------------------
class Switch
{
    public:
        Switch(std::string path);
        ~Switch();
        char switch_read();
        bool is_switch_accessible();

    protected:
        char _switch_state;
        bool _switch_accessible;
        std::fstream* _switch_file;
};




#include "led-switch.h"
#include <string>
#include <cstdlib>

// led
// gpio 516 ----> gpio 4 in real life
std::string gpio_4 = "/sys/class/gpio/gpio4/value";

// switch
// gpio 517 ----> gpio 5 in real life
std::string gpio_5 = "/sys/class/gpio/gpio5/value";


int main()
{

    // get pins files ready
    std::system("echo 4 > /sys/class/gpio/export");
    std::system("echo 5 > /sys/class/gpio/export");
    
    // get pins directions ready
    std::system("echo out > /sys/class/gpio/gpio4/direction");
    std::system("echo in > /sys/class/gpio/gpio5/direction");
    
    Led l{gpio_4};
    Switch s{gpio_5};
    char value;

    // check switch file
    if(!s.is_switch_accessible())
    {
        std::cout << "can't read switch file!! \n";
        return 1;
    }

    // check led file
    if(!l.is_led_accessible())
    {
        std::cout << "can't write on led file!! \n";
        return 1;
    }
    
    // super loop
    while(1)
    {
        // read switch
        value = s.switch_read();
        std::cout << "Swutch: " << value << " | ";

        if (value == '0')
        {
            l.turn_led_on();
            std::cout << "Led: 1 \n";
        }
        else if (value == '1')
        {
            l.turn_led_off();
            std::cout << "Led: 0 \n";
        }
    }
    return 0;
}

#include "led-switch.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <thread> 
#include <chrono> 

std::chrono::seconds delay(1);

// led
// gpio 516 ----> gpio 4 in real life
std::string gpio_4 = "/sys/class/gpio/gpio4/value";

// led
std::string gpio_26 = "/sys/class/gpio/gpio26/value";


//switch
// gpio 517 ----> gpio 5 in real life
std::string gpio_5 = "/sys/class/gpio/gpio5/value";


int main()
{

    // get pins files ready
    std::system("echo 4 > /sys/class/gpio/export");
    std::system("echo 26 > /sys/class/gpio/export");
    std::system("echo 5 > /sys/class/gpio/export");
    
    // get pins directions ready
    std::system("echo out > /sys/class/gpio/gpio4/direction");
    std::system("echo out > /sys/class/gpio/gpio26/direction");
    std::system("echo in > /sys/class/gpio/gpio5/direction");
    
    // Led l{gpio_26};
    // Switch s{gpio_5};
    char value;

    std::fstream test_led;
    test_led.open(gpio_26, std::ios::out | std::ios::trunc);


    std::fstream test_sw;
    test_sw.open(gpio_5, std::ios::in);

    // check switch file
    // if(!s.is_switch_accessible())
    // {
    //     std::cout << "can't read from switch file !! \n";
    //     return 1;
    // }


    if(!test_sw.is_open())
    {
        std::cout << "can't read from switch file !! \n";
        return 1;
    }


    // check led file
    // if(!l.is_led_accessible())
    // {
    //     std::cout << "can't write on led file !! \n";
    //     return 1;
    // }

    if(!test_led.is_open())
    {
        std::cout << "can't write on test led file !! \n";
        return 1;
    }

    test_led.close();
    test_sw.close();
    
    
    // super loop
    while(1)
    {
        // read switch
        // value = s.switch_read();
        test_sw.open(gpio_5, std::ios::in);
        test_sw >> value;
        test_sw.close();
        
        std::cout << "Swutch: " << value << " | ";

        if (value == '0')
        {
            // l.turn_led_on();
            test_led.open(gpio_26, std::ios::out | std::ios::trunc);
            test_led << '1';
            test_led.close();
            std::cout << "Led: 1 \n";
            
        }
        else if (value == '1')
        {
            // l.turn_led_off();
            test_led.open(gpio_26, std::ios::out | std::ios::trunc);
            test_led << '0';
            test_led.close();
            std::cout << "Led: 0 \n";
        }
    }
    return 0;
}
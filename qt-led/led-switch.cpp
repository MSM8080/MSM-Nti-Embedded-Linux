#include "led-switch.h"
// --------------------------------------------------
/* * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                   Class Led                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
// --------------------------------------------------
Led::Led(QString path) : _led_accessible(0)
{
    on = new char('1');
    off = new char('0');

    _led_file = new QFile(path);

    if(_led_file->open(stdin,  QIODevice::Truncate))
        _led_accessible = 1;
    else
        _led_accessible = 0;
}
// --------------------------------------------------
Led::~Led()
{
    delete _led_file;
}
// --------------------------------------------------
void Led::turn_led_on()
{
    _led_file->write(on);
}
// --------------------------------------------------
void Led::turn_led_off()
{
    _led_file->write(off);
}
// --------------------------------------------
bool Led::is_led_accessible()
{
    return _led_accessible;
}

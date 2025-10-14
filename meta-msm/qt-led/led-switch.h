#include <QString>
#include <QFile>
// --------------------------------------------------
class Led
{
    public:
        Led(QString path);
        ~Led();
        void turn_led_on();
        void turn_led_off();
        bool is_led_accessible();

    protected:
        bool _led_accessible;
        QFile* _led_file;
        const char* on;
        const char* off;
};



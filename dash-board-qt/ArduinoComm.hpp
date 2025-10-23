#ifndef ARDUINO_COMM_HPP
#define ARDUINO_COMM_HPP

#include <string>
#include <map>

class ArduinoComm {
public:
    explicit ArduinoComm(const std::string &port = "/dev/ttyACM0", int baudRate = 9600);
    ~ArduinoComm();

    bool openPort();
    void closePort();

    // Continuously read and parse data from Arduino
    void pollAnalogReadings();

    // Get last known analog (or temperature) value
    float getAnalog(int pin) const;

    // Send servo command
    void setServo(int angle);

private:
    std::string port_;
    int baudRate_;
    int serialFd_;
    std::map<int, float> analogBuffer_;
};

#endif // ARDUINO_COMM_HPP

#include "ArduinoComm.hpp"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <sys/ioctl.h>

ArduinoComm::ArduinoComm(const std::string &port, int baudRate)
    : port_(port), baudRate_(baudRate), serialFd_(-1)
{
    // std::cout << "Hi yaaaa Domaaa !!\n" << std::flush;
}

ArduinoComm::~ArduinoComm() {
    closePort();
}

bool ArduinoComm::openPort() {
    serialFd_ = open(port_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (serialFd_ == -1) {
        std::cerr << "Failed to open serial port: " << port_ << std::endl;
        return false;
    }

    struct termios options{};
    if (tcgetattr(serialFd_, &options) != 0) {
        std::cerr << "Error getting serial attributes\n";
        close(serialFd_);
        return false;
    }

    // سرعة الاتصال
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // إعدادات عامة
    options.c_cflag = (options.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    options.c_iflag &= ~IGNBRK;        // no break processing
    options.c_lflag = 0;               // no signaling chars, no echo, no canonical processing
    options.c_oflag = 0;               // no remapping, no delays

    // التحكم في التوقيت والحد الأدنى للقراءة
    options.c_cc[VMIN]  = 1;           // read() waits for at least 1 byte
    options.c_cc[VTIME] = 1;           // timeout = 0.1 second

    // إيقاف التحكم في الـ flow
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_cflag |= (CLOCAL | CREAD); // enable receiver, ignore modem control lines
    options.c_cflag &= ~(PARENB | PARODD); // no parity
    options.c_cflag &= ~CSTOPB;          // one stop bit
    options.c_cflag &= ~CRTSCTS;         // no hardware flow control

    if (tcsetattr(serialFd_, TCSANOW, &options) != 0) {
        std::cerr << "Error setting serial attributes\n";
        close(serialFd_);
        return false;
    }

    // reset Arduino by toggling DTR
    int flags;
    ioctl(serialFd_, TIOCMGET, &flags);
    flags &= ~TIOCM_DTR;
    ioctl(serialFd_, TIOCMSET, &flags);
    usleep(100000);
    flags |= TIOCM_DTR;
    ioctl(serialFd_, TIOCMSET, &flags);
    usleep(1000000);

    return true;
}

void ArduinoComm::closePort() {
    if (serialFd_ != -1) {
        close(serialFd_);
        serialFd_ = -1;
    }
}

void ArduinoComm::pollAnalogReadings() {
    if (serialFd_ == -1) return;

    char buf[256];
    int n = read(serialFd_, buf, sizeof(buf) - 1);
    if (n <= 0) return;

    buf[n] = '\0';
    std::string data(buf);

    // Expected: "A0:512 A1:23.75 A2:678\n"
    std::istringstream iss(data);
    std::string token;

    while (iss >> token) {
        if (token.size() < 4 || token[0] != 'A') continue;

        size_t colon = token.find(':');
        if (colon == std::string::npos) continue;

        int pin = std::stoi(token.substr(1, colon - 1));
        std::string valStr = token.substr(colon + 1);
        // std::cout << "valStr: " << valStr << std::endl;

        try {
            if (valStr == "ERR") {
                analogBuffer_[pin] = -9999.0f; // Invalid reading sentinel
            } else {
                float val = std::stof(valStr);
                analogBuffer_[pin] = val;
            }
        } catch (const std::exception &e) {
            std::cerr << "Parse error for token: " << token << " (" << e.what() << ")" << std::endl;
        }
    }
}

float ArduinoComm::getAnalog(int pin) const {
    auto it = analogBuffer_.find(pin);
    if (it != analogBuffer_.end()) {
        return it->second;
    }
    return -9999.0f; // no data yet
}

void ArduinoComm::setServo(int angle) {
    if (serialFd_ == -1) return;

    std::string cmd = "SET_SERVO " + std::to_string(angle) + "\n";
    write(serialFd_, cmd.c_str(), cmd.size());
    usleep(50000);

    // // Wait for acknowledgment
    // char buf[16];
    // int n = read(serialFd_, buf, sizeof(buf) - 1);
    // if (n > 0) {
    //     buf[n] = '\0';
    //     std::string ack(buf);
    //     if (ack.find("OK") != std::string::npos)
    //         std::cout << "Servo angle set successfully." << std::endl;
    // }
}

#include "uart.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

UARTProtocol::UARTProtocol(const std::string& port, int baudrate) 
    : port_(port), baudrate_(baudrate), fd_(-1) {}

bool UARTProtocol::connect() {
    // Open the serial port
    fd_ = open(port_.c_str(), O_RDWR | O_NOCTTY);
    if (fd_ < 0) {
        std::cerr << "Error opening port " << port_ << ": " << strerror(errno) << std::endl;
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Get current attributes
    if (tcgetattr(fd_, &tty) != 0) {
        std::cerr << "Error getting attributes for " << port_ << ": " << strerror(errno) << std::endl;
        close(fd_);
        return false;
    }

    // Configure for raw mode
    cfsetospeed(&tty, get_baud_rate());
    cfsetispeed(&tty, get_baud_rate());

    tty.c_cflag &= ~PARENB;  // No parity
    tty.c_cflag &= ~CSTOPB;  // 1 stop bit
    tty.c_cflag &= ~CSIZE;   // Clear size bits
    tty.c_cflag |= CS8;      // 8 data bits
    tty.c_cflag &= ~CRTSCTS; // No hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    tty.c_lflag &= ~ICANON;  // Non-canonical mode
    tty.c_lflag &= ~ECHO;    // No echo
    tty.c_lflag &= ~ECHOE;   // No echo erase
    tty.c_lflag &= ~ISIG;    // No signal chars

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // No software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~OPOST;   // No output processing
    tty.c_oflag &= ~ONLCR;   // No newline translation

    tty.c_cc[VMIN] = 0;      // Don't wait for minimum chars
    tty.c_cc[VTIME] = 10;    // Wait for 1 second max

    // Apply settings
    if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting attributes for " << port_ << ": " << strerror(errno) << std::endl;
        close(fd_);
        return false;
    }

    // Flush any existing data
    tcflush(fd_, TCIOFLUSH);

    connected_ = true;
    std::cout << "Connected to " << port_ << " at " << baudrate_ << " baud" << std::endl;
    return true;
}

bool UARTProtocol::disconnect() {
    if (connected_ && fd_ >= 0) {
        close(fd_);
        fd_ = -1;
        connected_ = false;
        std::cout << "Disconnected from " << port_ << std::endl;
    }
    return true;
}

bool UARTProtocol::send_data(const uint8_t* data, size_t length) {
    if (!connected_) {
        std::cerr << "Not connected to " << port_ << std::endl;
        return false;
    }

    ssize_t written = 0;
    size_t total_written = 0;

    while (total_written < length) {
        written = write(fd_, data + total_written, length - total_written);
        if (written < 0) {
            std::cerr << "Error writing to " << port_ << ": " << strerror(errno) << std::endl;
            return false;
        }
        total_written += written;
    }

    tcdrain(fd_); // Wait for transmission to complete
    return true;
}

bool UARTProtocol::receive_data(uint8_t* buffer, size_t max_length, size_t* received) {
    if (!connected_) {
        std::cerr << "Not connected to " << port_ << std::endl;
        return false;
    }

    ssize_t bytes_read = read(fd_, buffer, max_length);
    if (bytes_read < 0) {
        std::cerr << "Error reading from " << port_ << ": " << strerror(errno) << std::endl;
        return false;
    }

    *received = bytes_read;
    return true;
}

speed_t UARTProtocol::get_baud_rate() {
    switch(baudrate_) {
        case 9600: return B9600;
        case 19200: return B19200;
        case 38400: return B38400;
        case 57600: return B57600;
        case 115200: return B115200;
        case 230400: return B230400;
        case 460800: return B460800;
        case 921600: return B921600;
        default:
            std::cerr << "Unsupported baud rate: " << baudrate_ << ", using 115200" << std::endl;
            baudrate_ = 115200;
            return B115200;
    }
}

bool UARTProtocol::sync_connection() {
    // Send synchronization bytes
    uint8_t sync_bytes[] = {0x7E, 0xFF, 0xFF, 0x7E};
    if (!send_data(sync_bytes, sizeof(sync_bytes))) {
        return false;
    }

    // Give device time to respond
    usleep(100000); // 100ms

    // Try to read response
    uint8_t response[8];
    size_t received;
    if (receive_data(response, sizeof(response), &received)) {
        // Look for expected sync response pattern
        for (size_t i = 0; i < received; ++i) {
            if (response[i] == 0x7E) {
                std::cout << "Sync achieved with " << port_ << std::endl;
                return true;
            }
        }
    }

    std::cout << "Sync failed with " << port_ << std::endl;
    return false;
}
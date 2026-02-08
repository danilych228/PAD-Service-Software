#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <string>
#include <cstdint>

class UARTProtocol {
private:
    std::string port_;
    int baudrate_;
    int fd_;
    bool connected_ = false;

public:
    UARTProtocol(const std::string& port, int baudrate);
    
    bool connect();
    bool disconnect();
    bool send_data(const uint8_t* data, size_t length);
    bool receive_data(uint8_t* buffer, size_t max_length, size_t* received);
    bool sync_connection();
    
private:
    speed_t get_baud_rate();
};

#endif // UART_PROTOCOL_H
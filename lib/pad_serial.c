#include "../include/common_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <errno.h>
    #include <sys/ioctl.h>
#endif

typedef struct {
#ifdef _WIN32
    HANDLE handle;
#else
    int fd;
#endif
    int is_open;
} serial_port_t;

// Open serial port
serial_port_t* pad_serial_open(const char* port_name, int baud_rate) {
    serial_port_t* port = (serial_port_t*)malloc(sizeof(serial_port_t));
    if (!port) return NULL;
    
    memset(port, 0, sizeof(serial_port_t));
    
#ifdef _WIN32
    char full_port_name[256];
    snprintf(full_port_name, sizeof(full_port_name), "\\\\.\\\\%s", port_name);
    
    port->handle = CreateFile(
        full_port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (port->handle == INVALID_HANDLE_VALUE) {
        free(port);
        return NULL;
    }
    
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(port->handle, &dcb)) {
        CloseHandle(port->handle);
        free(port);
        return NULL;
    }
    
    dcb.BaudRate = baud_rate;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    
    if (!SetCommState(port->handle, &dcb)) {
        CloseHandle(port->handle);
        free(port);
        return NULL;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(port->handle, &timeouts)) {
        CloseHandle(port->handle);
        free(port);
        return NULL;
    }
    
    port->is_open = 1;
#else
    port->fd = open(port_name, O_RDWR | O_NOCTTY | O_SYNC);
    if (port->fd < 0) {
        free(port);
        return NULL;
    }
    
    struct termios tty;
    if (tcgetattr(port->fd, &tty) != 0) {
        close(port->fd);
        free(port);
        return NULL;
    }
    
    cfsetospeed(&tty, baud_rate);
    cfsetispeed(&tty, baud_rate);
    
    tty.c_cflag &= ~PARENB;  // No parity
    tty.c_cflag &= ~CSTOPB;  // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;      // 8 bits
    tty.c_cflag &= ~CRTSCTS; // No flow control
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // No SW flow control
    tty.c_lflag &= ~ICANON; // Non-canonical mode
    tty.c_lflag &= ~ECHO;   // No echo
    tty.c_lflag &= ~ECHOE;  // No erasure
    tty.c_lflag &= ~ISIG;   // No signal chars
    
    tty.c_oflag &= ~OPOST; // No output processing
    
    tty.c_cc[VMIN] = 0;    // Non-blocking read
    tty.c_cc[VTIME] = 5;   // 0.5 second timeout
    
    if (tcsetattr(port->fd, TCSANOW, &tty) != 0) {
        close(port->fd);
        free(port);
        return NULL;
    }
    
    port->is_open = 1;
#endif

    return port;
}

// Close serial port
int pad_serial_close(serial_port_t* port) {
    if (!port || !port->is_open) {
        return -1;
    }
    
#ifdef _WIN32
    CloseHandle(port->handle);
#else
    close(port->fd);
#endif
    
    port->is_open = 0;
    free(port);
    return 0;
}

// Write data to serial port
int pad_serial_write(serial_port_t* port, const uint8_t* data, size_t length) {
    if (!port || !port->is_open || !data || length == 0) {
        return -1;
    }
    
#ifdef _WIN32
    DWORD bytes_written;
    if (!WriteFile(port->handle, data, length, &bytes_written, NULL)) {
        return -1;
    }
    return (int)bytes_written;
#else
    ssize_t result = write(port->fd, data, length);
    if (result < 0) return -1;
    return (int)result;
#endif
}

// Read data from serial port
int pad_serial_read(serial_port_t* port, uint8_t* buffer, size_t max_length) {
    if (!port || !port->is_open || !buffer || max_length == 0) {
        return -1;
    }
    
#ifdef _WIN32
    DWORD bytes_read;
    if (!ReadFile(port->handle, buffer, max_length, &bytes_read, NULL)) {
        return -1;
    }
    return (int)bytes_read;
#else
    ssize_t result = read(port->fd, buffer, max_length);
    if (result < 0) return -1;
    return (int)result;
#endif
}

// Flush serial port
int pad_serial_flush(serial_port_t* port) {
    if (!port || !port->is_open) {
        return -1;
    }
    
#ifdef _WIN32
    if (!FlushFileBuffers(port->handle)) {
        return -1;
    }
#else
    if (tcflush(port->fd, TCIOFLUSH) != 0) {
        return -1;
    }
#endif
    
    return 0;
}
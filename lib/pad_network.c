#include "../include/common_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <fcntl.h>
#endif

// Structure to represent a network socket
typedef struct {
#ifdef _WIN32
    SOCKET sock;
#else
    int sock;
#endif
    int is_connected;
} network_socket_t;

// Initialize network subsystem (Windows)
int pad_network_init(void) {
#ifdef _WIN32
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
#else
    return 0; // Not needed on Unix-like systems
#endif
}

// Cleanup network subsystem (Windows)
int pad_network_cleanup(void) {
#ifdef _WIN32
    return WSACleanup();
#else
    return 0; // Not needed on Unix-like systems
#endif
}

// Create a TCP socket
network_socket_t* pad_tcp_create_socket(void) {
    network_socket_t* net_sock = (network_socket_t*)malloc(sizeof(network_socket_t));
    if (!net_sock) return NULL;
    
    memset(net_sock, 0, sizeof(network_socket_t));
    
#ifdef _WIN32
    net_sock->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (net_sock->sock == INVALID_SOCKET) {
        free(net_sock);
        return NULL;
    }
#else
    net_sock->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (net_sock->sock < 0) {
        free(net_sock);
        return NULL;
    }
#endif
    
    return net_sock;
}

// Connect to a server
int pad_tcp_connect(network_socket_t* net_sock, const char* host, uint16_t port) {
    if (!net_sock) return -1;
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        // If inet_pton fails, try DNS resolution
        struct hostent* host_entry = gethostbyname(host);
        if (host_entry == NULL) {
#ifdef _WIN32
            closesocket(net_sock->sock);
#else
            close(net_sock->sock);
#endif
            return -1;
        }
        memcpy(&server_addr.sin_addr, host_entry->h_addr_list[0], host_entry->h_length);
    }
    
#ifdef _WIN32
    if (connect(net_sock->sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        closesocket(net_sock->sock);
        return -1;
    }
#else
    if (connect(net_sock->sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(net_sock->sock);
        return -1;
    }
#endif
    
    net_sock->is_connected = 1;
    return 0;
}

// Send data over TCP
int pad_tcp_send(network_socket_t* net_sock, const uint8_t* data, size_t length) {
    if (!net_sock || !net_sock->is_connected || !data || length == 0) {
        return -1;
    }
    
#ifdef _WIN32
    int result = send(net_sock->sock, (const char*)data, length, 0);
    if (result == SOCKET_ERROR) {
        return -1;
    }
#else
    ssize_t result = send(net_sock->sock, data, length, 0);
    if (result < 0) {
        return -1;
    }
#endif
    
    return (int)length;
}

// Receive data over TCP
int pad_tcp_receive(network_socket_t* net_sock, uint8_t* buffer, size_t max_length) {
    if (!net_sock || !net_sock->is_connected || !buffer || max_length == 0) {
        return -1;
    }
    
#ifdef _WIN32
    int result = recv(net_sock->sock, (char*)buffer, max_length, 0);
    if (result == SOCKET_ERROR) {
        return -1;
    }
#else
    ssize_t result = recv(net_sock->sock, buffer, max_length, 0);
    if (result < 0) {
        return -1;
    }
#endif
    
    return result;
}

// Close the network socket
int pad_tcp_close(network_socket_t* net_sock) {
    if (!net_sock) return -1;
    
    if (net_sock->is_connected) {
#ifdef _WIN32
        closesocket(net_sock->sock);
#else
        close(net_sock->sock);
#endif
        net_sock->is_connected = 0;
    }
    
    free(net_sock);
    return 0;
}

// Set socket to non-blocking mode
int pad_set_nonblocking(network_socket_t* net_sock) {
    if (!net_sock) return -1;
    
#ifdef _WIN32
    u_long mode = 1;
    if (ioctlsocket(net_sock->sock, FIONBIO, &mode) != 0) {
        return -1;
    }
#else
    int flags = fcntl(net_sock->sock, F_GETFL, 0);
    if (flags < 0 || fcntl(net_sock->sock, F_SETFL, flags | O_NONBLOCK) < 0) {
        return -1;
    }
#endif
    
    return 0;
}

// Check if socket is ready for reading
int pad_socket_ready_read(network_socket_t* net_sock, int timeout_ms) {
    if (!net_sock) return -1;
    
#ifdef _WIN32
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(net_sock->sock, &read_fds);
    
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    
    int result = select(0, &read_fds, NULL, NULL, &timeout);
    return result > 0 ? 1 : (result == 0 ? 0 : -1);
#else
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(net_sock->sock, &read_fds);
    
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    
    int result = select(net_sock->sock + 1, &read_fds, NULL, NULL, &timeout);
    return result > 0 ? 1 : (result == 0 ? 0 : -1);
#endif
}
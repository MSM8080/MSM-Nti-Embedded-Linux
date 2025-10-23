// ------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include "../include/server.h"
// ------------------------------------------------------------------------------------------------------------------
// with my self
// // Ip adresses
// #define SERVER_IP "127.0.0.1"
// #define CLIENT_IP "192.168.8.53"

// // Port numbers
// #define SERVER_PORT 8080
// #define CLIENT_PORT 9090

// with my another
// Ip adresses
#define SERVER_IP "192.168.8.53"
// #define CLIENT_IP "192.168.8.108"

// Port numbers
#define SERVER_PORT 8080
#define CLIENT_PORT 9090

// ------------------------------------------------------------------------------------------------------------------
int main()
{
     // create server socket
    Server svr;
    if(svr.get_server_socket_fd() == -1) 
    {
        std::cerr << "\033[1;31mCan't create server socket !!\033[0m" << std::endl;
        return 0;
    }
    else 
    {
        std::cout << "\033[1;32mServer socket created successfully.\033[0m" << std::endl;
    }

    // bind & listen to socket
    svr.reserve_socket(SERVER_IP,SERVER_PORT);
    if(svr.is_socket_bind_succeeded() == -1) 
    {
        std::cerr << "\033[1;31mCan't bind server socket !!\033[0m" << std::endl;
        return 0;
    }
    else if(svr.is_socket_bind_succeeded() == 0)
    {
        std::cout << "\033[1;32mServer socket binded successfully.\033[0m" << std::endl;
    }

    if(svr.is_socket_listen_succeeded() == -1) 
    {
        std::cerr << "\033[1;31mServer socket Can't start listening !!\033[0m" << std::endl;
        return 0;
    }
    else 
    {
        std::cout << "\033[1;32mServer socket start listening successfully.\033[0m" << std::endl;
    }

    // accept client socket request
    svr.accept_client_request();
    if(svr.get_server_socket_fd() < 0) 
    {
        std::cerr << "\033[1;31mServer socket Can't accept client socket request !!\033[0m" << std::endl;
        return 0;
    }
    else 
    {
        std::cout << "\033[1;32mServer socket accepted client socket request successfully.\033[0m" << std::endl;
    }

    // start recieveing messages
    bool CLOSE_SOCKET = 0;
    char* msg;
    int msg_len;
    // int msg_len = 0;
    while(!CLOSE_SOCKET)
    {
        msg = svr.recieve_client_msg();
        msg_len = svr.is_socket_recv_succeeded();
        if(msg_len < 0) 
        {
            std::cerr << "\033[1;31mServer socket Can't receive client socket msg !!\033[0m" << std::endl;
        }
        else 
        {
            std::cout << "\033[1;32mServer socket recieve client socket msg successfully.\033[0m" << std::endl;
            std::cout << "\033[1;33mClient socket msg: \033[0m" << std::endl;
            printf("%s",msg);
        }
        
        if(msg[0] == 'q')
            CLOSE_SOCKET = 1;
    }

    // close both sockets
    return 0;
}

/*
*** cout ACII color code refrence ***

* std::cout << "\033[1;31m Red Text \033[0m" << std::endl;    // Red
* std::cout << "\033[1;32m Green Text \033[0m" << std::endl;  // Green
* std::cout << "\033[1;33m Yellow Text \033[0m" << std::endl; // Yellow
* std::cout << "\033[1;34m Blue Text \033[0m" << std::endl;   // Blue
* std::cout << "\033[1;35m Magenta Text \033[0m" << std::endl;// Magenta
* std::cout << "\033[1;36m Cyan Text \033[0m" << std::endl;   // Cyan
* std::cout << "\033[1;37m White Text \033[0m" << std::endl;  // White

*/

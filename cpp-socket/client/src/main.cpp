#include <iostream>
#include <cstring>
#include "../include/client.h"
// ------------------------------------------------------------------------------------------------------------------
int main()
{
    // create client server
    Client clt;
    if(clt.get_client_socket_fd() == -1)
    {
        std::cerr << "\033[1;31mCan't create client socket !!\033[0m" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "\033[1;32mClient socket created successfully.\033[0m" << std::endl;
    }

    // connect to server socket
    clt.connect_to_server(SERVER_IP,SERVER_PORT);
    if(clt.is_connect_server_succeeded() == -1) 
    {
        std::cerr << "\033[1;31mCan't connect to server socket !!\033[0m" << std::endl;
        return 0;
    }
    else if(clt.is_connect_server_succeeded() == 0)
    {
        std::cout << "\033[1;32mClient socket connected successfully to server.\033[0m" << std::endl;
    }

    // start sending messages
    bool CLOSE_SOCKET = 0;
    char msg[MSG_SIZE];
    while(!CLOSE_SOCKET)
    {
        std::cout << "\033[1;33mEnter msg to be send: \033[0m";
        fgets(msg,MSG_SIZE,stdin);
        if(msg[0] == 'q')
        {
            CLOSE_SOCKET = 1;
        }
        clt.set_sending_data(msg);
        clt.send_msg_to_server();
        if(clt.is_socket_send_succeeded() < 0)
        {
            std::cerr << "\033[1;31mClient socket Can't send to server !!\033[0m" << std::endl;
        }
        else
        {
            std::cout << "\033[1;32mClient socket send to server successfully.\033[0m" << std::endl;
        }
    }
    
    // close client socket
    return 0;
}
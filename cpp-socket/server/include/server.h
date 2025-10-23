#pragma once
// important data types & functions for socket
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// general socket function
#include <sys/socket.h>

// general data types & functions
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
// ----------------------------------------------------------------------------------------------------------------
class Server
{
private:
    
    sockaddr_in _server_adress;
    sockaddr_in _client_adress;
    socklen_t _client_socket_size;

    int _server_fd;
    int _client_fd;
    int _bind_status;
    int _listen_status;
    int _recv_status;
    

public:
    char *_recieved_data;
    // create socket
    // -- constructor() --> socket()
    Server();

    // close socket
    // -- deconstructor() --> close()
    ~Server();

    // explicitly reserve that address and port for the server's socket.
    // -- reserve_socket() --> bind()
    void reserve_socket(const char *ip, int port);

    // prepare a socket for accepting incoming client connections
    // -- accept_client_request() --> accept()
    void accept_client_request();

    // receive incoming data on a socket
    // -- recieve_client_msg --> recv();
    char* recieve_client_msg();

    // access private members of class Server
    int get_server_socket_fd();
    int get_client_socket_fd();
    int is_socket_bind_succeeded();
    int is_socket_listen_succeeded();
    int is_socket_recv_succeeded();
    const char& get_recieved_data();
};
// ----------------------------------------------------------------------------------------------------------------

// create socket
// -- constructor() --> socket()

// close socket
// -- deconstructor() --> close()

// explicitly reserve that address and port for the server's socket.
// -- reserve_socket() --> bind()

// prepare a socket for accepting incoming client connections
// -- accept_client_request() --> accept()

// receive incoming data on a socket
// -- recieve_client_msg --> recv();

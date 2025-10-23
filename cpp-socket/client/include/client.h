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
// with my self
// Ip adresses
// #define SERVER_IP "127.0.0.1"
// #define CLIENT_IP "192.168.8.53"

// // Port numbers
// #define SERVER_PORT 8080
// #define CLIENT_PORT 9090

// with another
// Ip adresses
#define SERVER_IP "192.168.8.108"
// #define CLIENT_IP "192.168.8.53"

// Port numbers
#define SERVER_PORT 8080
// #define CLIENT_PORT 9090


// data size
#define MSG_SIZE 1024
// ----------------------------------------------------------------------------------------------------------------

class Client
{
private:
    sockaddr_in _server_adress;
    sockaddr_in _client_adress;

    int _client_fd;
    int _connect_status;
    int _recv_status;
    int _send_status;
    char *_recieved_data;
    char *_sending_data;
public:
    // create socket
    // -- constructor() --> socket()
    Client();

    // close socket
    // -- deconstructor() --> close()
    ~Client();

    // connect to server socket
    // -- connect_to_server --> connect();
    void connect_to_server(const char* , int);

    // send data to server a socket
    // -- send_msg_to_server --> recv();
    void send_msg_to_server();

    // receive incoming data on a socket
    // -- recieve_client_msg --> recv();
    void recieve_server_msg();

    // access private members of class Client
    int get_client_socket_fd();    
    int is_socket_recv_succeeded();
    int is_socket_send_succeeded();
    int is_connect_server_succeeded();
    const char *get_recieved_data();
    void set_sending_data(char*);
};

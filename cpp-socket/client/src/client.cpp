#include "../include/client.h"
// ----------------------------------------------------------------------------------------------------------------
// ------------------------------------- class Client implementations ---------------------------------------------
// ----------------------------------------------------------------------------------------------------------------
// create socket
// -- constructor() --> socket()
Client::Client()
{
    /*
    ***********************************************
    *   socket(AF_INET, SOCK_STREAM, 0)
    ***********************************************
    * Arguments:
    * --> int sockfd declares an integer variable that will store the socket file descriptor.
    * --> AF_INET indicates the socket will use the IPv4 address family.
    * --> SOCK_STREAM specifies that the socket will use TCP (a stream-oriented protocol) and,
    * --> 0 lets the system choose the default protocol for the specified address family and socket
    *     type (which is TCP in this case).
    */
    _client_fd = socket(AF_INET, SOCK_STREAM, 0);
    _recieved_data = new char[MSG_SIZE];
    _recieved_data = {0};
    _sending_data = new char[MSG_SIZE];
    _sending_data = {0};
}
// ----------------------------------------------------------------------------------------------------------------
// close socket
// -- deconstructor() --> close()
Client::~Client()
{
    delete[] _recieved_data;
    delete[] _sending_data;
    close(_client_fd);
}
// ----------------------------------------------------------------------------------------------------------------
// connect to server socket
// -- connect_to_server --> connect();
void Client::connect_to_server(const char* ip, int port)
{
    // entering the ip address and port to of server socket
    _server_adress.sin_family = AF_INET;
    _server_adress.sin_port = htons(port);
    inet_pton(AF_INET,ip,&_server_adress.sin_addr);
    /*
    ***********************************************
    int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

    ***********************************************
    * Description:
    * --> This function is a system call that attempts to establish a
    *     connection to a specified server (for clients) using the socket.
    ***********************************************
    * Arguments:
    * --> sockfd is the file descriptor that represents the socket in your program and is used to perform various socket operations.
    * --> (struct sockaddr*)&serverAddress casts serverAddress to a struct sockaddr* pointer which enables compatibility with functions that require a generic socket address type.
    * --> sizeof(serverAddress) specifies the size of the serverAddress
    */
    _connect_status = connect(_client_fd, (sockaddr *)&_server_adress, sizeof(_server_adress));
}
// ----------------------------------------------------------------------------------------------------------------
// send data to server a socket
// -- send_msg_to_server --> recv();
void Client::send_msg_to_server()
{
    /*
    ***********************************************
    ssize_t send(int sockfd, const void buf[.len], size_t len, int flags);
    ***********************************************
    * Description:
    * --> The send() function is a system call in socket programming which 
    *     sends data to a connected socket.
    ***********************************************
    * Arguments:
    * --> sockfd is the file descriptor that represents the socket in your 
    *     program and is used to perform various socket operations.
    * --> strlen("Hello") function returns the length of the string "Hello" 
    *     (5 bytes), showing how many bytes of data to send.
    * --> 0 lets the system choose the default protocol for the specified 
    *     address family and socket type (which is TCP in this case).
    */
    _send_status = send(_client_fd,_sending_data,MSG_SIZE,0);
}
// ----------------------------------------------------------------------------------------------------------------
// receive incoming data on a socket
// -- recieve_client_msg --> recv();
void Client::recieve_server_msg()
{
    /*
    ***********************************************
    ssize_t recv(int sockfd, void buf[.len], size_t len, int flags);

    ***********************************************
    * Description:
    * --> The recv() function is a system call that is used to receive data from a connected socket
    *     which allows the client or server to read incoming messages.
    ***********************************************
    * Arguments:
    * --> sockfd is the file descriptor that represents the socket in your program and is used to perform various socket operations.
    * --> buffer is a pointer to the memory location where the received data will be stored. This buffer should be large enough to hold the incoming data.
    * --> sizeof(buffer) specifies the maximum number of bytes to read from the socket, which is typically the size of the buffer.
    */
    _recv_status = recv(_client_fd, _recieved_data, sizeof(_recieved_data), 0);
}
// ----------------------------------------------------------------------------------------------------------------
// access private members of class Client
int Client::get_client_socket_fd()
{
    return _client_fd;
}
// ----------------------------------------------------------------------------------------------------------------
const char *Client::get_recieved_data()
{
    return _recieved_data;
}
// ----------------------------------------------------------------------------------------------------------------
void Client::set_sending_data(char * data)
{
    _sending_data = data;
}
// ----------------------------------------------------------------------------------------------------------------
int Client::is_socket_recv_succeeded()
{
    /*
     * n --> N# bytes recieved
     * -1 --> failed
     */
    return _recv_status;
}
// ----------------------------------------------------------------------------------------------------------------
int Client::is_socket_send_succeeded()
{
    /*
     * n --> N# bytes sending
     * -1 --> failed
     */
    return _send_status;
}
// ----------------------------------------------------------------------------------------------------------------
int Client::is_connect_server_succeeded()
{
    /*
     * 0 --> successed
     * -1 --> failed
     */
    return _connect_status;
}

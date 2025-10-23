#include "../include/server.h"
// ----------------------------------------------------------------------------------------------------------------
// ------------------------------------- class Server implementations ---------------------------------------------
// ----------------------------------------------------------------------------------------------------------------
// create socket
// -- constructor() --> socket()
Server::Server() : _recv_status(0)
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
    _server_fd = socket(AF_INET,SOCK_STREAM,0);
    _recieved_data = new char[1024];
    // _recieved_data = {0};
}
// ----------------------------------------------------------------------------------------------------------------
// close socket
// -- deconstructor() --> close()
Server::~Server()
{
    delete[] _recieved_data;
    close(_client_fd);
    close(_server_fd);
}
// ----------------------------------------------------------------------------------------------------------------
// explicitly reserve that address and port for the server's socket.
// -- reserve_socket() --> bind()
void Server::reserve_socket(const char* ip, int port)
{
    // Bind the ip address and port to a socket
    _server_adress.sin_family = AF_INET;
    _server_adress.sin_port = htons(port);
    inet_pton(AF_INET,ip,&_server_adress.sin_addr);
    /*
    ***********************************************    
    int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    ***********************************************    
    * Description:
    * --> The bind() method is associated with a socket, with a specific local address 
          and port number which allows the socket to listen for incoming connection on 
          that address.
    ***********************************************    
    * Arguments:
    * --> sockfd is the file descriptor that represents the socket in your program and is used to perform various 
    *     socket operations
    * --> (struct sockaddr)&address casts the address structure to a generic pointer type
    *     for the bind function.
    * --> sizeof(address) specifies the size of the address structure to inform the system 
    *     how much data to expect.
    */
    _bind_status = bind(_server_fd, (sockaddr *)&_server_adress, sizeof(_server_adress));
    /*
    ***********************************************    
    int listen(int sockfd, int backlog);
    ***********************************************    
    * Description:
    * --> listen()  marks  the  socket referred to by sockfd as a passive socket,
          that is, as a socket that will be used to  accept  incoming  connection
          requests using accept(2).
    ***********************************************    
    * Arguments:
    * --> sockfd is the file descriptor that represents the socket in your program 
    *     and is used to perform various socket operations
    * --> 10 is the backlog parameter, which specifies the maximum number of pending 
    *     connections that can be queued while the server is busy.
    */
    _listen_status = listen(_server_fd,10);
}
// ----------------------------------------------------------------------------------------------------------------
// prepare a socket for accepting incoming client connections
// -- accept_client_request() --> accept()
void Server::accept_client_request()
{
    _client_socket_size = sizeof(_client_adress);
    /*
    ***********************************************    
    int accept(int sockfd, struct sockaddr *_Nullable restrict addr,socklen_t *_Nullable restrict addrlen);
    ***********************************************    
    * Description:
    * --> accept()  The accept() function accepts a new connection from a client 
    *     (for servers). It extracts the first connection request on the queue of 
    *     pending connections and creates a new socket for that connection.
    ***********************************************    
    * Arguments:
    * --> sockfd: It's the socket's file descriptor where it is used to perform various socket operations.
    * --> (struct sockaddr)&address: This is a type cast that converts the pointer type of clientAddress 
    *     to a pointer of type struct sockaddr*.
    * --> &clientLen: It is a pointer to a variable that holds the size of the clientAddress.
    */
   _client_fd =  accept(_server_fd,(sockaddr*)&_client_adress, &_client_socket_size);
}
// ----------------------------------------------------------------------------------------------------------------
// receive incoming data on a socket
// -- recieve_client_msg --> recv();
char* Server::recieve_client_msg()
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
    recv(_client_fd,_recieved_data, 1024,0);
    return _recieved_data;

}
// ----------------------------------------------------------------------------------------------------------------
int Server::get_server_socket_fd()
{
    return _server_fd;
}
// ----------------------------------------------------------------------------------------------------------------
int Server::get_client_socket_fd()
{
    return _client_fd;
}
// ----------------------------------------------------------------------------------------------------------------
int Server::is_socket_bind_succeeded()
{
    return _bind_status;
}
// ----------------------------------------------------------------------------------------------------------------
int Server::is_socket_listen_succeeded()
{
    return _listen_status;
}
// ----------------------------------------------------------------------------------------------------------------
int Server::is_socket_recv_succeeded()
{
    /*
     * n --> N# bytes recieved
     * -1 --> failed
     */
    return _recv_status;
}

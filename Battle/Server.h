#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <utility>
#include <string>

//#pragma comment(lib, "Ws2_32.lib")

//typedef void (*handle_func_cb)(void* data);

//class TcpServer {
//public:

//    TcpServer(const uint16_t port, handle_func_cb func);
//    ~TcpServer();

//    void Start();
//    void Stop();
//    SOCKET HanlingLoop();
//    bool IsAuthorizatedClient(std::pair<std::string, SOCKET>&);

//private:
//    const uint16_t _port;
//    handle_func_cb _func;
//    SOCKET serv_socket = INVALID_SOCKET;
//    WSAData w_data;
//    HANDLE ghSemaphore;
//};

#endif // SERVER_H

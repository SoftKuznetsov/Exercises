#include "Server.h"

#include <stdexcept>
#include <semaphore.h>

#include <QDebug>

//TcpServer::TcpServer(const uint16_t port, handle_func_cb func)
//    : _port(port), _func(func) {

//}

//TcpServer::~TcpServer() {
//    Stop();
//    WSACleanup();
//}

//void TcpServer::Start() {
//    // write version WinSocket
//    int result = WSAStartup(MAKEWORD(2, 2), &w_data);
//    if (result != 0) {
//        throw std::runtime_error("WSAStartup failed");
//    }

//    struct addrinfo* addr = nullptr;
//    struct addrinfo hints;

//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;

//    // Resolve the server address and port
//    result = getaddrinfo(nullptr, std::to_string(_port).c_str(), &hints, &addr);
//    if (result != 0) {
//        WSACleanup();
//        throw std::runtime_error{ "WspiapiGetAddrInfo failed" };
//    }

//    // create socket
//    serv_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
//    if (serv_socket == INVALID_SOCKET) {
//        freeaddrinfo(addr);
//        WSACleanup();
//        throw std::runtime_error{ "Create socket failed" };
//    }

//    // bind socket
//    result = bind(serv_socket, addr->ai_addr, (int)addr->ai_addrlen);
//    if (result == SOCKET_ERROR) {
//        freeaddrinfo(addr);
//        Stop();
//        throw std::runtime_error{ "Bind socket failed" };
//    }

//    // listen socket
//    result = listen(serv_socket, 2);
//    if (result == SOCKET_ERROR) {
//        freeaddrinfo(addr);
//        Stop();
//        throw std::runtime_error{ "Listen socket failed" };
//    }

//    ghSemaphore = CreateSemaphore(
//        NULL,           // default security attributes
//        1,  // initial count
//        1,  // maximum count
//        NULL);          // unnamed semaphore
//}

//void TcpServer::Stop() {
//    closesocket(serv_socket);

//    WSACleanup();
//}

//SOCKET TcpServer::HanlingLoop() {
//    DWORD dwWaitResult = WaitForSingleObject(
//        ghSemaphore,   // handle to semaphore
//        INFINITE);     // zero-second time-out interval

//    SOCKET client_socket = INVALID_SOCKET;

//    client_socket = accept(serv_socket, nullptr, nullptr);
//    if (client_socket == INVALID_SOCKET) {
////        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
//        return SOCKET_ERROR;
//    }

//    ReleaseSemaphore(
//        ghSemaphore,  // handle to semaphore
//        1,            // increase count by one
//        NULL);

//    return client_socket;
//}


//bool TcpServer::IsAuthorizatedClient(std::pair<std::string, SOCKET>& client) {
//    auto dwWaitResult = WaitForSingleObject(
//        ghSemaphore,   // handle to semaphore
//        INFINITE);     // zero-second time-out interval

//    int recv_result = 0;
//    const uint16_t size_buffer = 256;
//    char buffer[size_buffer];

//    recv_result = recv(client.second, buffer, size_buffer, 0);

//    if (recv_result > 0) {
//        std::string message(buffer);
//        client.first = message;
//    }
//    else {
//        std::string error("error authorization!");
//        int send_result = send(client.second, error.c_str(), error.length() + 1, 0);
//    }

//    ReleaseSemaphore(
//        ghSemaphore,  // handle to semaphore
//        1,            // increase count by one
//        NULL);

//    return true;
//}

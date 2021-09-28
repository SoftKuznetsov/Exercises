#include "Client.h"
#include "string"

Client::Client(const uint16_t port) : _port(port) {

}

Client::~Client() {
    Stop();
    WSACleanup();
}

void Client::Start() {
    // write version WinSocket
    int result = WSAStartup(MAKEWORD(2, 2), &w_data);
    if (result != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
    struct addrinfo* ptr = nullptr;
    struct addrinfo* addr = nullptr;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    result = getaddrinfo("localhost", std::to_string(_port).c_str(), &hints, &addr);
    if (result != 0) {
        WSACleanup();
        throw std::runtime_error{ "WspiapiGetAddrInfo failed" };
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = addr; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        client_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (client_socket == INVALID_SOCKET) {
            WSACleanup();
            throw std::runtime_error("Client socket failed");
        }

        // Connect to server.
        result = connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(addr);

    if (client_socket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Unable to connect to server!");
    }
}

void Client::Stop() {
    closesocket(client_socket);
}

void Client::Authorization() {
    std::string nick;
    std::cout << "Enter your nickname: ";
    std::cin >> nick;

    SendData(nick.c_str(), nick.length() + 1);
}

int32_t Client::SendData(const char* data, uint32_t len) {
    // Send an initial buffer
    int result = send(client_socket, data, len, 0);
    if (result == SOCKET_ERROR) {
        Stop();
        WSACleanup();
        return SOCKET_ERROR;
    }

    return result;
}


int32_t Client::ReadData(char* data, uint32_t len) {
    // Send an initial buffer
    int result = recv(client_socket, data, len, 0);
    if (result == SOCKET_ERROR) {
        Stop();
        WSACleanup();
        return SOCKET_ERROR;
    }

    return result;
}
#ifndef _TCP_SERVER
#define _TCP_SERVER

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

constexpr uint8_t MAX_COUNTER_CLIENTS = 2;

typedef void (*handle_func_cb)(void* data);
typedef unsigned short index_t;


class TcpServer {
public:

	TcpServer(const uint16_t port, handle_func_cb func);
	~TcpServer();

	void Start();
	void Stop();
	SOCKET HanlingLoop();
	bool IsAuthorizatedClient(std::pair<std::string, SOCKET>&);

private:
	const uint16_t _port;
	handle_func_cb _func;
	SOCKET serv_socket = INVALID_SOCKET;
	WSAData w_data;
	HANDLE ghSemaphore;
};

#endif // _TCP_SERVER

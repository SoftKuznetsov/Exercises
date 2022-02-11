#ifndef CLIENT
#define CLIENT

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define BUF_SIZE     255

class Client {
public:
	Client(const uint16_t port);
	~Client();

	void Start();
	void Stop();

	int32_t SendData(const char* data, uint32_t len);
	int32_t ReadData(char* data, uint32_t len);

	void Authorization();
private:
	const uint16_t _port;
	SOCKET client_socket = INVALID_SOCKET;
	WSAData w_data;
};



#endif
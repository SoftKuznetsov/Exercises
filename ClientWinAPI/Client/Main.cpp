#include "Client.h"
#include <string>
#include <thread>

#define DEFAULT_PORT 27015

int main() {
	Client myClient(DEFAULT_PORT);
	// create client socket
	myClient.Start();

	// TODO - check is correct authorization
	myClient.Authorization();

	auto func_send = [&myClient]() {
		while (1) {
			// contain your message
			std::string message;
			std::cin >> message;

			// send message to server
			if (myClient.SendData(message.c_str(), message.length() + 1) < 0) {
				break;
			}
		}
	};

	auto func_recv = [&myClient]() {
		while (1) {
			int recv_result = 0;
			char buffer[BUF_SIZE];

			if (recv_result = myClient.ReadData(buffer, BUF_SIZE) > 0) {
				std::string message(buffer);
				std::cout << message << std::endl;
			}
			else {
				break;
			}

		}
	};

	std::thread thread_recv(func_recv);
	thread_recv.detach();

	std::thread thread_send(func_send);
	thread_send.join();

	return 0;
}
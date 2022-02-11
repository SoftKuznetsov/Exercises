
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <mutex>

#include "Server.h"


#define MAX_THREADS  3
#define BUF_SIZE     255
#define DEFAULT_PORT 27015


void HandleFunction(void* data);
void HandleMessage(std::map<std::string, SOCKET>& list, std::pair<const std::string, SOCKET> client);
void SendMessageToOtherClients(std::map<std::string, SOCKET>& list, std::pair<const std::string, SOCKET> author, std::string message);

std::mutex g_mutex;

//#define TEST 

int main() {

	// list of clients with unique nickname
	std::map<std::string, SOCKET> list_of_client;
	std::map<std::string, std::thread> list_of_thread;

	// create server
	TcpServer server(DEFAULT_PORT, HandleFunction);

	server.Start();
	
	
	//---------------------------------------------------------
	// connect new client
	//---------------------------------------------------------
	// authorization new client
	//---------------------------------------------------------
	// add to list of client
	//---------------------------------------------------------
	auto connect_new_client = [&server, &list_of_client]() {
		while (1) {
			std::pair<std::string, SOCKET> client;
			// connect new client
			client.second = server.HanlingLoop();
			if (client.second == SOCKET_ERROR) {
				continue;
			}

			// authorization new client
			if (server.IsAuthorizatedClient(client)) {
				// add client to list
				list_of_client.insert(client);

				// create new thread for current client
				std::thread thread_client(HandleMessage, std::ref(list_of_client), client);
				thread_client.detach();
			}
		}
	};

	// thread 1 - handling connect new client
	std::thread handling_connect(connect_new_client);
	handling_connect.join();
	
	return 0;
}

void HandleFunction(void* data) {
	// some handling connection of client
}

//---------------------------------------------------------
// handle message from client
//---------------------------------------------------------
void HandleMessage(std::map<std::string, SOCKET>& list, std::pair<const std::string, SOCKET> client) {
	while (1) {
		int recv_result = 0;
		char buffer[BUF_SIZE];

		recv_result = recv(client.second, buffer, BUF_SIZE, 0);
		if (recv_result > 0) {
			std::string message(buffer);
			SendMessageToOtherClients(list, client, message);
		}
		else {
			std::map<std::string, SOCKET>::iterator it;
			it = list.find(client.first);
			if (it != list.end()) {
				std::cout << client.first << " left chat" << std::endl;
				list.erase(it);
				std::cout << "clients in this room: " << list.size() << std::endl;
			}
			break;
		}
	}

}

//---------------------------------------------------------
// send message to other clients
//---------------------------------------------------------
void SendMessageToOtherClients(std::map<std::string, SOCKET>& list, std::pair<const std::string, SOCKET> author, std::string message) {
	std::lock_guard<std::mutex> guard(g_mutex);

	std::string packet;
	packet = author.first + "-->" + message;
	std::cout << packet << std::endl;

	// send a message to other clients besides the author
	for (auto iter = list.begin(); iter != list.end(); iter++) {

		if (iter->first != author.first) { // compare key of client
			int send_result;

			send_result = send(iter->second, packet.c_str(), packet.length() + 1, 0);

			if (send_result == SOCKET_ERROR) {
				// handle error
			}
		}
	}
};


#include "ntClient.h"
#include "ntServer.h"
#include <iostream>

using namespace nettools;

void testServer() {

}

void ServerMessageHandler(NT_MESSAGE message, ntConnection *connection) {
	if (message == NT_CONNECT) {
		std::cout << "Conectado";
	}
}


int main(int argc, char *argv[]) {
	//ntClient client;
	//client.connect("localhost", 8080);
	//client.close();
	ntServer server;
	server.listen(32111);
	server.setMessageHandler(ServerMessageHandler);
	
	testServer();
	ntClient client;
	char command[256];
	bool quit;
	do {
		std::cin >> command;
		quit = ::strcmp(command, "q") == 0;
		if (::strcmp(command, "c") == 0) {
			client.connect("127.0.0.1", 32111);
		}
		else if (::strcmp(command, "a") == 0) {
			server.poll();
		}
	} while (quit != true);

	client.close();
	server.close();
	return 0;
}
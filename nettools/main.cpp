
#include "ntClient.h"
#include "ntServer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace nettools;

void testServer() {

}

void ClientMessageHandler(NT_MESSAGE message, ntConnection *connection) {
	if (message == NT_CONNECT) {
		std::cout << "Conectado";
	}
	else if (message == NT_DATARECV) {
		std::cout << "Data";
	}
}

void ServerMessageHandler(NT_MESSAGE message, ntConnection *connection) {
	if (message == NT_CONNECT) {
		std::cout << "Conectado";
	}
	else if (message == NT_DATARECV) {
		std::cout << "Data";
	}
}


int main(int argc, char *argv[]) {

	std::vector<ntServer*> servers;
	std::vector<ntClient*> clients;


	ntClient client;
	char command[256];
	for(;;) {
		std::cin >> command;
		if (::strcmp(command, "q") == 0)
			break;
		else if (::strcmp(command, "ns") == 0) {
			std::cout << "Port: ";
			int port;
			std::cin >> port;
			
			ntServer *newServer = new ntServer();
			newServer->setMessageHandler(ServerMessageHandler);
			NT_ERROR result = newServer->listen(port);
			if (result == NTERR_SUCCESS)
				servers.push_back(newServer);
			else {
				std::cout << "An error has occurred";
				delete newServer;
			}
		}
		else if (::strcmp(command, "nc") == 0) {
			std::string hostname;
			std::cout << "Hostname: ";
			std::cin >> hostname;
			std::cout << "Port: ";
			int port;
			std::cin >> port;

			ntClient *newClient = new ntClient();
			newClient->setMessageHandler(ClientMessageHandler);
			NT_ERROR result = newClient->connect(hostname.c_str(), port);
			clients.push_back(newClient);
		}
		else if (::strcmp(command, "ls") == 0) {
			std::cout << "List of Servers:\n";
			for (std::vector<ntServer*>::iterator it = servers.begin(); it != servers.end(); ++it) {
				std::cout << (*it)->socket();
				std::cout << "\n";
			}

			std::cout << "List of Clients:\n";
			for (std::vector<ntClient*>::iterator it = clients.begin(); it != clients.end(); ++it) {
				std::cout << (*it)->socket();
				std::cout << "\n";
			}

		}
		else if(::strcmp(command, "c") == 0) {
			std::cout << "Socket: ";
			int fd;
			std::cin >> fd;
			std::cout << "Message: ";
			std::string message;
			std::cin >> message;
			ntClient *client = NULL;
			for (std::vector<ntClient*>::iterator it = clients.begin(); it != clients.end(); ++it) {
				if ((*it)->socket() == fd) {
					client = *it;
					break;
				}
			}
			if (client) {
				client->send(message);
			}
		}


		for (std::vector<ntServer*>::iterator it = servers.begin(); it != servers.end(); ++it) {
			NT_ERROR result = (*it)->poll();
		}
		for (std::vector<ntClient*>::iterator it = clients.begin(); it != clients.end(); ++it) {
			NT_ERROR result = (*it)->poll();
		}
	}

	for (std::vector<ntServer*>::iterator it = servers.begin(); it != servers.end(); ++it) {
		(*it)->close();
	}
	return 0;
}
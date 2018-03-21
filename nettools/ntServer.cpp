
#include "ntServer.h"

namespace nettools {

	ntServer::ntServer() {
	}

	NT_ERROR ntServer::listen(u16 port) {
		_socket(&m_socket);
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = ADDR_ANY;
		_bind(m_socket, (sockaddr*)&addr, sizeof(addr));
		_listen(m_socket);
		return 0;
	}

	NT_ERROR ntServer::poll() {
		unsigned int i;

		int result;
		ntConnection *newClient;
		do {
			result = _accept(m_socket,&newClient);
			if (newClient) {
				m_clients.push_back(newClient);
				if (m_messageHandler)
					m_messageHandler(NT_CONNECT, newClient);
			}
		} while (result != 0);


		for (i = 0; i < m_clients.size(); ++i) {
			u8 data[MAX_PACKET_SIZE];
			result = _recv(m_socket, data, MAX_PACKET_SIZE);
		}
		return 0;
	}

	NT_ERROR ntServer::close() {
		ntConnection::close();
		return 0;
	}

}
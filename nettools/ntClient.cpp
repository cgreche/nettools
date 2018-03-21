
#include "ntClient.h"


namespace nettools {

	ntClient::ntClient() {

	}

	NT_ERROR ntClient::connect(const char * hostname, u16 port) {
		_socket(&m_socket);
		m_address.sin_family = AF_INET;
		inet_pton(AF_INET, "127.0.0.1", &m_address.sin_addr);
		m_address.sin_port = ::htons(port);
		return _connect(m_socket, (sockaddr*)&m_address, sizeof(m_address));
	}

	NT_ERROR ntClient::poll() {
		return 0;
	}

	NT_ERROR ntClient::close() {
		return 0;
	}
}
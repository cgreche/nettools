
#include "ntConnection.h"

namespace nettools {

	NT_ERROR ntConnection::_socket(int *socket) {
		int s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		*socket = s;
		return 0;
	}

	NT_ERROR ntConnection::_bind(int socket, sockaddr *address, u32 len) {
		int result = ::bind(socket, address, len);
		return 0;
	}

	NT_ERROR ntConnection::_listen(int socket) {
		int result = ::listen(socket, 10);
		return 0;
	}

	NT_ERROR ntConnection::_accept(int socket, ntConnection **mewClient) {
		sockaddr_in clientAddr;
		int addrLen = sizeof(sockaddr_in);
		int newSocket = ::accept(m_socket, (sockaddr*)&clientAddr, &addrLen);
		*mewClient = new ntConnection(newSocket, (sockaddr*)&clientAddr, sizeof(clientAddr));
		return 0;
	}

	NT_ERROR ntConnection::_connect(int socket, sockaddr *address, u32 len) {
		int res = ::connect(socket, address, len);
		return 0;
	}

	NT_ERROR ntConnection::_send(int socket, const u8 *data, u32 len) {
		int result = ::send(socket, (const char*)data, len, 0);
		return 0;
	}

	NT_ERROR ntConnection::_recv(int socket, u8 *data, u32 len) {
		int result = ::recv(socket, (char*)data, len, 0);
		return 0;
	}

	NT_ERROR ntConnection::_close(int socket) {
		::closesocket(socket);
		return 0;
	}

	ntConnection::ntConnection() {
		WSADATA wsaData;
		int result = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
		m_socket = 0;
		m_param = NULL;
	}

	ntConnection::ntConnection(int sock, sockaddr *address, u32 len) {
		m_socket = sock;
		m_address = *(sockaddr_in*)address;
	}

	ntConnection::~ntConnection() {
		close();
		int result = ::WSACleanup();
	}

	NT_ERROR ntConnection::getOption() {
		return 0;
	}

	NT_ERROR ntConnection::setOption() {
		return 0;
	}

	void ntConnection::setMessageHandler(ntMessageHandler messageHandler) {
		m_messageHandler = messageHandler;
	}

	NT_ERROR ntConnection::poll() {
		return 0;
	}

	NT_ERROR ntConnection::close() {
		::shutdown(m_socket, SD_BOTH);
		_close(m_socket);
		return 0;
	}

}
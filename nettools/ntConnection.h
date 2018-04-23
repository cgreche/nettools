#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Ws2tcpip.h>

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;

namespace nettools {
#define MAX_PACKET_SIZE 8192

	enum NT_ERROR {
		NTERR_SUCCESS,
		NTERR_WOULDBLOCK,
		NTERR_ADDRINUSE,
		NTERR_CONNREFUSED,
		NTERR_OTHER
	};

	enum NT_MESSAGE {
		NT_CONNECT,
		NT_DISCONNECT,
		NT_DATARECV
	};

	class ntConnection;
	typedef void(*ntMessageHandler)(NT_MESSAGE message, ntConnection *connection);

	class ntConnection {

		ntConnection(int socket, sockaddr *addr, u32 length);

	protected:
		int m_socket; //fd/SOCKET
		sockaddr_in m_address;
		ntMessageHandler m_messageHandler;
		void *m_param;

		NT_ERROR _socket(int *socket);
		NT_ERROR _bind(int socket, sockaddr *address, u32 len);
		NT_ERROR _listen(int socket);
		NT_ERROR _accept(int socket, ntConnection **mewClient);
		NT_ERROR _connect(int socket, sockaddr *address, u32 len);
		NT_ERROR _send(int socket, const u8 *data, u32 len);
		NT_ERROR _recv(int socket, u8 *data, u32 maxlen, u32 *recvLen);
		NT_ERROR _close(int socket);

	public:
		ntConnection();
		virtual ~ntConnection();

		NT_ERROR setBlockingMode(bool blocking);
		NT_ERROR setOption();
		NT_ERROR getOption();
		
		NT_ERROR send(int socket, const u8 *data, u32 len);
		NT_ERROR recv(int socket, u8 *data, u32 maxlen, u32 *recvLen);
		virtual NT_ERROR poll();
		virtual NT_ERROR close();

		void setMessageHandler(ntMessageHandler messageHandler);

		int socket() const { return m_socket; }
	};

}
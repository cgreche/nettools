#pragma once

#include "ntConnection.h"
#include <string>

namespace nettools {

	class ntClient : public ntConnection {
	public:
		ntClient();
		NT_ERROR connect(const char *hostname, u16 port);
		NT_ERROR send(std::string message);
		virtual NT_ERROR poll();
		virtual NT_ERROR close();
	};

}
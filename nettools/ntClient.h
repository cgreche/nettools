#pragma once

#include "ntConnection.h"

namespace nettools {

	class ntClient : public ntConnection {
	public:
		ntClient();
		NT_ERROR connect(const char *hostname, u16 port);
		virtual NT_ERROR poll();
		virtual NT_ERROR close();
	};

}
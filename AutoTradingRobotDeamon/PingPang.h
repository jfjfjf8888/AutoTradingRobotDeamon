#pragma once
#include "TcpServer.h"

#define SERVER_MAX_CLIENT 10
#define PORT 13888

class PingPang
{
public:
	PingPang();
	~PingPang();
private:
	TcpServer server;
};


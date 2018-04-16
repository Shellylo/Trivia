#pragma once

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class Communicator
{
public:
	void bindAndListen();
	void handleRequests();

private:
	std::map<SOCKET, IRequestHandler> m_clients;
	RequestHandlerFactory m_handleFactory;
};
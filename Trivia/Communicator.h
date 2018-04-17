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

private:
	std::map<SOCKET, IRequestHandler> m_clients;
	RequestHandlerFactory m_handleFactory;

	void startThreadForNewClient();
	void handleRequests(SOCKET socket, IRequestHandler ssssstate);
};
#pragma once

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <utility>
#include <thread>

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void bindAndListen();

private:
	std::map<SOCKET, IRequestHandler&> m_clients;
	RequestHandlerFactory& m_handleFactory;
	SOCKET _serverSocket;

	void startThreadForNewClient();
	void handleRequests(SOCKET socket, IRequestHandler& state);
};
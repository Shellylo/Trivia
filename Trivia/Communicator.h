#pragma once
#pragma comment(lib, "Ws2_32.lib")
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
	void handleRequests();

private:
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handleFactory;
	SOCKET _serverSocket;

	void startThreadForNewClient();
	void clientHandler(SOCKET socket);
};
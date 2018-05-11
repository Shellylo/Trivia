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
#include <queue>

#define SERVER_PORT 2431
#define INFO_LEN 5

class Communicator
{
public:
	/*
		Creates new communicator
	*/
	Communicator(RequestHandlerFactory& handlerFactory);
	/*
		Closes the server
	*/
	~Communicator();

	/*
		Starts the server and listens for clients
		Input: none
		Output: none
	*/
	void bindAndListen();
	/*
		Handles all the requests
		Input: none
		Output: none
	*/
	void handleRequests();

private:
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handleFactory;
	SOCKET _serverSocket;
	std::queue<std::pair<SOCKET, Request>> rq;

	/*
		Starts a new thread for a client
		Input: none
		Output: none
	*/
	void startThreadForNewClient();
	/*
		Gets requests from one user and adds them to the request queue
		Input: the socked of the user
		Output: none
	*/
	void clientHandler(SOCKET socket);
};
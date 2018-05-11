#pragma once
#include "RequestHandlerFactory.h"
#include "Communicator.h"
#include "SqliteDatabase.h"

class Server
{
public:
	/*
		Creates a server
		Input: database
	*/
	Server(IDatabase& database);
	/*
		Distructs the server
	*/
	~Server();

	/*
		Runs the server
		Input: none
		Output: none
	*/
	void run();

private:
	IDatabase& m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};
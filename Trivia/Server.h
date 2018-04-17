#pragma once
#include "RequestHandlerFactory.h"
#include "Communicator.h"
#include "SqliteDatabase.h"

class Server
{
public:
	Server(IDatabase& database);

	void run();

private:
	IDatabase& m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};
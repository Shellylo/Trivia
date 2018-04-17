#pragma once
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"

class Server
{
public:
	void run();

private:
	IDatabase& m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};
#include "Server.h"

Server::Server(IDatabase & database) : m_database(database), m_handlerFactory(database), m_communicator(m_handlerFactory)
{
}

void Server::run()
{
	m_communicator.bindAndListen();
}

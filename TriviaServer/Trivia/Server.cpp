#include "Server.h"

Server::Server(IDatabase & database) : m_database(database), m_handlerFactory(database), m_communicator(m_handlerFactory)
{
}

Server::~Server()
{
	m_database.close();
}

void Server::run()
{
	m_database.open();
	std::thread requestsListener(&Communicator::handleRequests, &m_communicator);
	requestsListener.detach();
	m_communicator.bindAndListen();
}

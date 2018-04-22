#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory & handlerFactory) : m_handleFactory(handlerFactory)
{
}

Communicator::~Communicator()
{
	try
	{
		::closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(2431); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

										// again stepping out to the global namespace
										// Connects between the socket and the configuration (port and etc..)
	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (::listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");

	while (true)
	{
		startThreadForNewClient();
	}
}

void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	// the function that handle the conversation with the client
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, m_handleFactory.createLoginRequestHandler()));
	std::thread clientHandler(&Communicator::clientHandler, std::ref(*this), client_socket);
	clientHandler.detach();
}

void Communicator::clientHandler(SOCKET socket)
{
	while (true)
	{
		std::vector<char> info(INFO_LEN);
		recv(socket, &info[0], INFO_LEN, 0);
		int size = JsonRequestPacketDeserializer::binaryToInt(&info[1]);
		std::vector<char> data(size);
		recv(socket, &data[0], size, 0);
		Request req = { info[0], size, data };
		std::vector<char> ans = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ "Irrelevant request" });
		if (m_clients[socket]->isRequestRelevant(req))
		{
			RequestResult resp = m_clients[socket]->handleRequest(req);
			if (resp.newHandler)
			{
				delete m_clients[socket];
				m_clients[socket] = resp.newHandler;
			}
			ans = resp.buffer;
		}
		send(socket, &ans[0], ans.size(), 0);
	}
}
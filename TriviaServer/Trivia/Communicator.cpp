#include "Communicator.h"
#include <mutex>

std::mutex m;
std::condition_variable cv;

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

	sa.sin_port = htons(SERVER_PORT); // port that server will listen for
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

void Communicator::handleRequests()
{
	while (true)
	{
		try
		{
			if (rq.empty())
			{
				std::unique_lock<std::mutex> lk(m);
				cv.wait(lk);
			}
			std::pair<SOCKET, Request> sock_req = rq.front();
			rq.pop();
			std::cout << rq.size() << std::endl;
			std::vector<char> ans = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ "Irrelevant request" });
			if (m_clients[sock_req.first]->isRequestRelevant(sock_req.second))
			{
				RequestResult resp = m_clients[sock_req.first]->handleRequest(sock_req.second);
				if (resp.newHandler && resp.newHandler != m_clients[sock_req.first])
				{
					delete m_clients[sock_req.first];
					m_clients[sock_req.first] = resp.newHandler;
				}
				ans = resp.buffer;
			}
			send(sock_req.first, &ans[0], ans.size(), 0);
		}
		catch (std::exception e)
		{

		}
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
		if (recv(socket, &info[0], INFO_LEN, 0) == SOCKET_ERROR)
		{
			m_clients.erase(socket);
			break;
		}
		int size = JsonRequestPacketDeserializer::binaryToInt(&info[1]);
		std::vector<char> data(size);
		if (size)
		{
			recv(socket, &data[0], size, 0);
		}
		Request req = { info[0], size, data };
		rq.push(std::pair<SOCKET, Request>(socket, req));
		cv.notify_one();
	}
}

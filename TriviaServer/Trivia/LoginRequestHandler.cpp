#include "LoginRequestHandler.h"
#include <exception>

LoginRequestHandler::LoginRequestHandler(LoginManager & manager, RequestHandlerFactory & handlerFactory) : m_loginManager(manager), m_handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(Request req)
{
	return req.reqCode == LOGIN_REQ_CODE || req.reqCode == SIGNUP_REQ_CODE;
}

RequestResult LoginRequestHandler::handleRequest(Request req)
{
	return req.reqCode == LOGIN_REQ_CODE ? login(req) : signup(req);
}

void LoginRequestHandler::disconnectUser(std::string user)
{
	m_loginManager.logout(user);
}

RequestResult LoginRequestHandler::login(Request req)
{
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(req.buffer);
	LoginResponse result = { 1 };
	try
	{
		m_loginManager.login(request.username, request.password);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createMenuRequestHandler(LoggedUser(request.username)) } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult LoginRequestHandler::signup(Request req)
{
	SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(req.buffer);
	SignupResponse result = { 1 };
	try
	{
		m_loginManager.signup(request.username, request.password, request.email);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

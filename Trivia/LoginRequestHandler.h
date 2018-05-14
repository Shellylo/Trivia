#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& manager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;
	void disconnectUser(std::string user);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(Request req);
	RequestResult signup(Request req);
};
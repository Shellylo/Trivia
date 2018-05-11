#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define LOGIN_REQ_CODE 1
#define SIGNUP_REQ_CODE 2

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
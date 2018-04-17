#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;

private:
	LoginManager m_loginManager;
	RequestHandlerFactory m_handlerFactory;

	RequestResult loginRequest(Request req);
	RequestResult signUp(Request req);
};
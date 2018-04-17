#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& manager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult loginRequest(Request req);
	RequestResult signUp(Request req);
};
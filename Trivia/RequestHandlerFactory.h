#pragma once
#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "loginManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	LoginRequestHandler createLoginRequestHandler();

private:
	LoginManager m_loginManager;
};

#pragma once
//#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "loginManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	LoginRequestHandler* createLoginRequestHandler();
	IRequestHandler* createMenuRequestHandler() { return nullptr; } // temp - change later the return value

private:
	LoginManager m_loginManager;
};

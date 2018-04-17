#pragma once
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	LoginRequestHandler createLoginRequestHandler();

private:
	LoginManager m_loginManager;
};

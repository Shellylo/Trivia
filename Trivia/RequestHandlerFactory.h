#pragma once
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();

private:
	LoginManager m_loginManager;
};

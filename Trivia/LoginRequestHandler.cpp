#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager & manager, RequestHandlerFactory & handlerFactory) : m_loginManager(manager), m_handlerFactory(handlerFactory)
{
}

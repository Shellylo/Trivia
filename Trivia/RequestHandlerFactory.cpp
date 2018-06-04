#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase & database) : m_loginManager(database), m_highscoreTable(database), m_gameManager(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, *this);
}

MenuRequestHandler * RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(m_roomManager, m_highscoreTable, *this, user);
}

RoomAdminRequestHandler * RequestHandlerFactory::createRoomAdminRequestHandler(Room & room, LoggedUser user)
{
	return new RoomAdminRequestHandler(room, user, m_roomManager, m_gameManager, *this);
}

RoomMemberRequestHandler * RequestHandlerFactory::createRoomMemberRequestHandler(Room & room, LoggedUser user)
{
	return new RoomMemberRequestHandler(room, user, m_roomManager, m_gameManager, *this);
}

GameRequestHandler * RequestHandlerFactory::createGameRequestHandler(Game & game, LoggedUser user)
{
	return new GameRequestHandler(game, user, m_gameManager, *this);
}

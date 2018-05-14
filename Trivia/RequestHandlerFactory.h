#pragma once
//#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "loginManager.h"
#include "RoomManager.h"
#include "HighscoreTable.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);// temp - change later the return value
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room& room, LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room& room, LoggedUser user);

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	HighscoreTable m_highscoreTable;

};

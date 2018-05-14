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
	/*
		Creates a RequestHandlerFactory
	*/
	RequestHandlerFactory(IDatabase& database);

	/*
		Creates a LoginRequestHandler (dynamic allocation)
		Input: none
		Output: the pointer to the object
	*/
	LoginRequestHandler* createLoginRequestHandler();

	/*
		Creates a MenuRequestHandler (dynamic allocation)
		Input: none
		Output: the pointer to the object
	*/
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	
    RoomAdminRequestHandler* createRoomAdminRequestHandler(Room& room, LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room& room, LoggedUser user);


private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	HighscoreTable m_highscoreTable;
};

#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "loginManager.h"
#include "RoomManager.h"
#include "HighscoreTable.h"
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

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
		Input: user
		Output: the pointer to the object
	*/
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	
	/*
		Creates a RoomAdminRequestHandler (dynamic allocation)
		Input: room and user
		Output: the pointer to the object
	*/
    RoomAdminRequestHandler* createRoomAdminRequestHandler(Room& room, LoggedUser user);

	/*
		Creates a RoomMemberRequestHandler (dynamic allocation)
		Input: room and user
		Output: the pointer to the object
	*/
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room& room, LoggedUser user);

	GameRequestHandler* createGameRequestHandler(Game& game, LoggedUser user);

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	HighscoreTable m_highscoreTable;
	GameManager m_gameManager;
};

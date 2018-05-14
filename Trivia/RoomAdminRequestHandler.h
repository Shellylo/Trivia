#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room& room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;

private:
	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult closeRoom(Request req);
	RequestResult startGame(Request req);
	RequestResult getRoomState(Request req);
};
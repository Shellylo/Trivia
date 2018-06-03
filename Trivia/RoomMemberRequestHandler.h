#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;

private:
	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult leaveRoom(Request req);
	RequestResult getRoomState(Request req);
	RequestResult joinGame(Request req);
};
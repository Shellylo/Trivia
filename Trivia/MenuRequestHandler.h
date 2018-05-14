#pragma once

#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "HighscoreTable.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RoomManager& manager,HighscoreTable& highscoreTable, RequestHandlerFactory& handlerFactory, LoggedUser user);

	bool isRequestRelevant(Request req) override;
	RequestResult handleRequest(Request req) override;

private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	HighscoreTable& m_highscoreTable;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(Request req);
	RequestResult getRooms(Request req);
	RequestResult getPlayersInRoom(Request req);
	RequestResult getHighscores(Request req);
	RequestResult joinRoom(Request req);
	RequestResult createRoom(Request req);
};
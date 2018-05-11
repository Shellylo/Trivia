#pragma once

#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "HighscoreTable.h"
#include "RoomManager.h"

#define SIGNOUT_REQ_CODE 3
#define GETROOMS_REQ_CODE 4
#define GETPLAYERSROOM_REQ_CODE 5
#define JOINROOM_REQ_CODE 6
#define CREATEROOM_REQ_CODE 7
#define GETHIGHSCORES_REQ_CODE 8

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
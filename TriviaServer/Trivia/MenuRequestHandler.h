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
	/*
		Creates a MenuRequestHandler
	*/
	MenuRequestHandler(RoomManager& manager,HighscoreTable& highscoreTable, RequestHandlerFactory& handlerFactory, LoggedUser user);

	/*
		Comment in the pure virtual function
	*/
	bool isRequestRelevant(Request req) override;
	/*
		Comment in the pure virtual function
	*/
	RequestResult handleRequest(Request req) override;

private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	HighscoreTable& m_highscoreTable;
	RequestHandlerFactory& m_handlerFactory;

	/*
		Handles the signout request
		Input: the request
		Output: the request result
	*/
	RequestResult signout(Request req);
	/*
		Handles the get rooms request
		Input: the request
		Output: the request result
	*/
	RequestResult getRooms(Request req);
	/*
		Handles the get players in room request
		Input: the request
		Output: the request result
	*/
	RequestResult getPlayersInRoom(Request req);
	/*
		Handles the get highscores request
		Input: the request
		Output: the request result
	*/
	RequestResult getHighscores(Request req);
	/*
		Handles the join room request
		Input: the request
		Output: the request result
	*/
	RequestResult joinRoom(Request req);
	/*
		Handles the create roon request
		Input: the request
		Output: the request result
	*/
	RequestResult createRoom(Request req);
};
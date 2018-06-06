#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "Game.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <string>

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	/*
		Creates a GameRequestHandler
	*/
	GameRequestHandler(Game& game, LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory);

	/*
		Comment in the pure virtual function
	*/
	bool isRequestRelevant(Request req) override;
	/*
		Comment in the pure virtual function
	*/
	RequestResult handleRequest(Request req) override;

private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(Request req);
	RequestResult submitAnswer(Request req);
	RequestResult getGameResults(Request req);
	RequestResult leaveGame(Request req);
};
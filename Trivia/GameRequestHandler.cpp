#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Game & game, LoggedUser user, GameManager & gameManager, RequestHandlerFactory & handlerFactory) : m_game(game), m_user(user), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

bool GameRequestHandler::isRequestRelevant(Request req)
{
	return 	req.reqCode == GETQUESTION_REQ_CODE || req.reqCode == SUBMITANSWER_REQ_CODE || req.reqCode == GETGAMERESULTS_REQ_CODE || req.reqCode == LEAVEGAME_REQ_CODE;
}

RequestResult GameRequestHandler::handleRequest(Request req)
{
	RequestResult reqRes;
	switch (req.reqCode)
	{
	case GETQUESTION_REQ_CODE:
		reqRes = getQuestion(req);
		break;
	case SUBMITANSWER_REQ_CODE:
		reqRes = submitAnswer(req);
		break;
	case GETGAMERESULTS_REQ_CODE:
		reqRes = getGameResults(req);
		break;
	case LEAVEGAME_REQ_CODE:
		reqRes = leaveGame(req);
		break;
	}
	return reqRes;
}

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

RequestResult GameRequestHandler::getQuestion(Request req)
{
	GetQuestionResponse result = { 1 , "", std::vector<std::string>() };
	try
	{
		Question qs = m_game.getQuestionForUser(m_user);
		result.question = qs.getQs();
		std::vector<std::string> answers = qs.getAnss();
		answers.push_back(qs.getCorrectAns());
		int size = answers.size();
		srand(time(NULL));
		int index = rand() % size;
		std::string temp = answers[index];
		answers[index] = answers[size - 1];
		answers[size - 1] = temp;
		result.answers = answers;
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult GameRequestHandler::submitAnswer(Request req)
{
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(req.buffer);
	SubmitAnswerResponse result = { 1 , "", false };
	try
	{
		m_gameManager.submitAnswer(m_user, m_game, request.answer);
		result.hasFinished = m_game.getQuestionForUser(m_user).getQs() == "";
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult GameRequestHandler::getGameResults(Request req)
{
	GetGameResultsResponse result = { 1 , std::vector<PlayerResults>() };
	try
	{
		result.results = m_game.getPlayersResults();
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult GameRequestHandler::leaveGame(Request req)
{
	LeaveGameResponse result = { 1 };
	try
	{
		if (!m_game.removePlayer(m_user))
		{
			m_gameManager.deleteGame(m_game);
		}
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createMenuRequestHandler(m_user) } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

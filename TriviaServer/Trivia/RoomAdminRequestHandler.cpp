#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room & room, LoggedUser user, RoomManager & roomManager, GameManager& gameManager, RequestHandlerFactory & handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(Request req)
{
	return req.reqCode == CLOSEROOM_REQ_CODE || req.reqCode == STARTGAME_REQ_CODE || req.reqCode == GETROOMSTATE_REQ_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(Request req)
{
	RequestResult reqRes;
	switch (req.reqCode)
	{
	case CLOSEROOM_REQ_CODE:
		reqRes = closeRoom(req);
		break;
	case STARTGAME_REQ_CODE:
		reqRes = startGame(req);
		break;
	case GETROOMSTATE_REQ_CODE:
		reqRes = getRoomState(req);
		break;
	}
	return reqRes;
}

RequestResult RoomAdminRequestHandler::closeRoom(Request req)
{
	CloseRoomResponse result = { 1 };
	try
	{
		m_roomManager.closeRoom(m_room, m_user);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createMenuRequestHandler(m_user) } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult RoomAdminRequestHandler::startGame(Request req)
{
	StartGameResponse result = { 1 };
	GameRequestHandler* grh = nullptr;
	try
	{
		grh = m_handlerFactory.createGameRequestHandler(m_gameManager.createGame(m_user, m_room), m_user);
		m_roomManager.leaveRoom(m_user, m_room.getRoomData().id);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), grh } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult RoomAdminRequestHandler::getRoomState(Request req)
{
	GetRoomStateResponse result = { 1, 0, std::vector<std::string>(), 0, 0 };
	try
	{
		RoomData data = m_room.getRoomData();
		result.roomStatus = data.roomState;
		result.players = m_roomManager.getPlayersInRoom(data.id);
		result.questionCount = data.questionCount;
		result.answerTimeout = data.timePerQuestion;
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

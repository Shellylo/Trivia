#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room & room, LoggedUser user, RoomManager & roomManager, GameManager& gameManager, RequestHandlerFactory & handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(Request req)
{
	return req.reqCode == GETROOMSTATE_REQ_CODE || req.reqCode == LEAVEROOM_REQ_CODE || req.reqCode == JOINGAME_REQ_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(Request req)
{
	RequestResult reqRes;
	switch (req.reqCode)
	{
	case LEAVEROOM_REQ_CODE:
		reqRes = leaveRoom(req);
		break;
	case GETROOMSTATE_REQ_CODE:
		reqRes = getRoomState(req);
		break;
	case JOINGAME_REQ_CODE:
		reqRes = joinGame(req);
		break;
	}
	return reqRes;
}

RequestResult RoomMemberRequestHandler::leaveRoom(Request req)
{
	LeaveRoomResponse result = { 1 };
	try
	{
		m_roomManager.leaveRoom(m_user, m_room.getRoomData().id);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createMenuRequestHandler(m_user) } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult RoomMemberRequestHandler::getRoomState(Request req)
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
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createMenuRequestHandler(m_user) } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult RoomMemberRequestHandler::joinGame(Request req)
{
	JoinGameResponse result = { 1 };
	GameRequestHandler* grh = nullptr;
	try
	{
		grh = m_handlerFactory.createGameRequestHandler(m_gameManager.joinGame(m_user, m_room.getRoomData().id), m_user);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), grh } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

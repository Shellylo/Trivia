#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room & room, LoggedUser user, RoomManager & roomManager, RequestHandlerFactory & handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
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
	try
	{
		m_gameManager.createGame(m_room);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createGameRequestHandler() } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

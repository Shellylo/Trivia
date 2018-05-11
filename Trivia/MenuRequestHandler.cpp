#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RoomManager & manager, HighscoreTable & highscoreTable, RequestHandlerFactory & handlerFactory, LoggedUser user) : m_roomManager(manager), m_highscoreTable(highscoreTable), m_handlerFactory(handlerFactory), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(Request req)
{
	return req.reqCode == SIGNOUT_REQ_CODE || req.reqCode == GETROOMS_REQ_CODE || req.reqCode == GETPLAYERSROOM_REQ_CODE ||
		   req.reqCode == JOINROOM_REQ_CODE || req.reqCode == CREATEROOM_REQ_CODE || req.reqCode == GETHIGHSCORES_REQ_CODE;
}

RequestResult MenuRequestHandler::handleRequest(Request req)
{
	RequestResult reqRes;
	switch(req.reqCode)
	{
	case SIGNOUT_REQ_CODE:
		reqRes = signout(req);
		break;
	case GETROOMS_REQ_CODE:
		reqRes = getRooms(req);
		break;
	case GETPLAYERSROOM_REQ_CODE:
		reqRes = getPlayersInRoom(req);
		break;
	case JOINROOM_REQ_CODE:
		reqRes = joinRoom(req);
		break;
	case CREATEROOM_REQ_CODE:
		reqRes = createRoom(req);
		break;
	case GETHIGHSCORES_REQ_CODE:
		reqRes = getHighscores(req);
		break;
	}
	return reqRes;
}

RequestResult MenuRequestHandler::signout(Request req)
{
	LogoutResponse result = { 1 };
	LoginRequestHandler* lrh = m_handlerFactory.createLoginRequestHandler();
	try
	{
		lrh->disconnectUser(m_user.getUsername());
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), lrh } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult MenuRequestHandler::getRooms(Request req)
{
	GetRoomsResponse result = { 1, std::vector<RoomData>() };
	try
	{
		result.rooms = m_roomManager.getRooms();
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request req)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(req.buffer);
	GetPlayersInRoomResponse result = { 1, std::vector<std::string>() };
	try
	{
		result.users = m_roomManager.getPlayersInRoom(request.roomId);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult MenuRequestHandler::getHighscores(Request req)
{
	HighscoreResponse result = { 1 , std::vector<Highscore>()};
	try
	{
		result.highscores = m_highscoreTable.getHighscores();
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), this } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult MenuRequestHandler::joinRoom(Request req)
{
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(req.buffer);
	LoginResponse result = { 1 };
	try
	{
		m_roomManager.joinRoom(m_user, request.roomId);
	}
	catch (...)
	{
		result.status = 0;
	} 
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.RoomMemberRequestHandler() } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}

RequestResult MenuRequestHandler::createRoom(Request req)
{
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(req.buffer);
	LoginResponse result = { 1 };
	try
	{
		m_roomManager.createRoom(m_user, request);
	}
	catch (...)
	{
		result.status = 0;
	}
	return result.status ? RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), m_handlerFactory.createRoomAdminRequestHandler() } : RequestResult{ JsonResponsePacketSerializer::serializeResponse(result), nullptr };
}
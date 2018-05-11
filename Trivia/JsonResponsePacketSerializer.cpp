#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse resp)
{
	json j = { { "message", resp.message } };
	return createBuff(j, ERROR_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse resp)
{
	json j = { { "status", resp.status } };
	return createBuff(j, LOGIN_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse resp)
{
	json j = { { "status", resp.status } };
	return createBuff(j, SIGNUP_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse resp)
{
	json j = { { "status", resp.status } };
	return createBuff(j, LOGOUT_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse resp)
{
	json j = { {"status", resp.status}, {"rooms", createJsonRoomArray(resp.rooms)} };
	return createBuff(j, GETROOM_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse resp)
{
	json j = { { "status", resp.status },{ "users", resp.users } };
	return createBuff(j, GETPLAYERSROOM_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse resp)
{
	json j = { { "status", resp.status } };
	return createBuff(j, JOINROOM_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse resp)
{
	json j = { { "status", resp.status } };
	return createBuff(j, CREATEROOM_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(HighscoreResponse resp)
{
	json j = { { "status", resp.status }, { "highscores", createJsonHighscoresArray(resp.highscores) } };
	return createBuff(j, GETHIGHSCORES_RESP_CODE);
}

std::vector<char> JsonResponsePacketSerializer::intToBinary(unsigned int num)
{
	std::vector<char> ret = { '\0', '\0','\0','\0' };
	for (int i = 0; i < SIZE_LEN && num != 0; i++)
	{
		ret[SIZE_LEN - 1 - i] += num % 256;
		num /= 256;
	}
	return ret;
}

std::vector<char> JsonResponsePacketSerializer::createBuff(json j, unsigned int code)
{
	std::vector<char> buff;
	std::string js = j.dump();
	std::vector<char> dataSize = intToBinary(js.length());
	buff.push_back(code);
	buff.insert(buff.end(), dataSize.begin(), dataSize.end());
	buff.insert(buff.end(), js.begin(), js.end());
	return buff;
}

std::vector<json> JsonResponsePacketSerializer::createJsonRoomArray(std::vector<RoomData> rooms)
{
	std::vector<json> jrooms;
	for(int i = 0; i < rooms.size(); i++)
	{
		jrooms.push_back({ {"id", rooms[i].id}, {"name", rooms[i].name}, {"maxPlayers", rooms[i].maxPlayers}, {"timePerQuestion", rooms[i].timePerQuestion}, {"isActive", rooms[i].isActive} });
	}
	return jrooms;
}

std::vector<json> JsonResponsePacketSerializer::createJsonHighscoresArray(std::vector<Highscore> highscores)
{
	std::vector<json> jhighscores;
	for (int i = 0; i < highscores.size(); i++)
	{
		jhighscores.push_back({ { "username", highscores[i].username },{ "score", highscores[i].score },{ "time", highscores[i].time } });
	}
	return jhighscores;
}

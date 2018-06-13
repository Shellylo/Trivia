#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> req)
{	
	json j = json::parse(req);
	return {j["username"], j["password"]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> req)
{

	json j = json::parse(req);
	return { j["username"], j["password"], j["email"] };
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<char> req)
{
	json j = json::parse(req);
	return {j["roomId"]};
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<char> req)
{
	json j = json::parse(req);
	return { j["roomId"] };
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<char> req)
{
	json j = json::parse(req);
	return { j["name"] , j["maxPlayers"], j["questionCount"], j["answerTimeout"] };
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<char> req)
{
	json j = json::parse(req);
	return { j["answer"] };
}

unsigned int JsonRequestPacketDeserializer::binaryToInt(char * buff)
{
	int ret = 0;
	for (int i = 0; i < SIZE_LEN; i++)
	{
		ret += (buff[SIZE_LEN - i - 1] * pow(2, i * CHAR_SIZE));
	}
	return ret;
}

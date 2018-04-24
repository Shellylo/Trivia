#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"

#define SIZE_LEN 4
#define CHAR_SIZE 8

using json = nlohmann::json;

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string name;
	unsigned int maxPlayers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<char> req);
	static SignupRequest deserializeSignupRequest(std::vector<char> req);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<char> req);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<char> req);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<char> req);
	static unsigned int binaryToInt(char* buff);
};
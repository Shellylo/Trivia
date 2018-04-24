#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include "Room.h"
#include "json.hpp"

#define ERROR_RESP_CODE 0
#define LOGIN_RESP_CODE 1
#define SIGNUP_RESP_CODE 2
#define LOGOUT_RESP_CODE 3
#define GETROOM_RESP_CODE 4
#define GETPLAYERSROOM_RESP_CODE 5
#define JOINROOM_RESP_CODE 6
#define CREATEROOM_RESP_CODE 7
#define SIZE_LEN 4
#define CHAR_SIZE 8

using json = nlohmann::json;

struct ErrorResponse
{
	std::string message;
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<std::string> users;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};

//struct HighscoreResponse
//{
//	unsigned int status;
//	std::vector<HighScore> highscores;
//};

class JsonResponsePacketSerializer
{
public:
	static std::vector<char> serializeResponse(ErrorResponse resp);
	static std::vector<char> serializeResponse(LoginResponse resp);
	static std::vector<char> serializeResponse(SignupResponse resp);
	static std::vector<char> serializeResponse(LogoutResponse resp);
	static std::vector<char> serializeResponse(GetRoomResponse resp);
	static std::vector<char> serializerResponse(GetPlayersInRoomResponse resp);
	static std::vector<char> serializeResponse(JoinRoomResponse resp);
	static std::vector<char> serializeResponse(CreateRoomResponse resp);
//	static std::vector<char> serializeResponse(HighscoreResponse resp);

private:
	static std::vector<char> intToBinary(unsigned int num);
	static std::vector<char> createBuff(json j, unsigned int code);
	static std::vector<json> createJsonRoomArray(std::vector<RoomData> rooms);
};
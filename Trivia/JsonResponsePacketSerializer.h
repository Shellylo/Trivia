#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include "Room.h"
#include "json.hpp"
#include "HighscoreTable.h"

enum respCodes
{
	ERROR_RESP_CODE,
	LOGIN_RESP_CODE,
	SIGNUP_RESP_CODE,
	LOGOUT_RESP_CODE,
	GETROOMS_RESP_CODE,
	GETPLAYERSROOM_RESP_CODE,
	JOINROOM_RESP_CODE,
	CREATEROOM_RESP_CODE,
	GETHIGHSCORES_RESP_CODE,
	CLOSEROOM_RESP_CODE,
	STARTGAME_RESP_CODE,
	GETROOMSTATE_RESP_CODE,
	LEAVEROOM_RESP_CODE
};

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

struct GetRoomsResponse
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

struct HighscoreResponse
{
	unsigned int status;
	std::vector<Highscore> highscores;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	unsigned int gameStatus;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

class JsonResponsePacketSerializer
{
public:
	/*
		Serializes error response
		Input: error response
		Output: buffer
	*/
	static std::vector<char> serializeResponse(ErrorResponse resp);
	/*
    	Serializes login response
    	Input: login response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(LoginResponse resp);
	/*
    	Serializes signup response
    	Input: signup response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(SignupResponse resp);
	/*
    	Serializes logout response
    	Input: logout response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(LogoutResponse resp);
	/*
    	Serializes get rooms response
    	Input: get rooms response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(GetRoomsResponse resp);
	/*
    	Serializes get players in room response
    	Input: get players in room response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(GetPlayersInRoomResponse resp);
	/*
    	Serializes join room response
    	Input: join room response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(JoinRoomResponse resp);
	/*
    	Serializes create room response
    	Input: create room response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(CreateRoomResponse resp);
	/*
    	Serializes get highscores response
    	Input: get highscores response
    	Output: buffer
	*/
	static std::vector<char> serializeResponse(HighscoreResponse resp);
	static std::vector<char> serializeResponse(CloseRoomResponse resp);
	static std::vector<char> serializeResponse(StartGameResponse resp);
	static std::vector<char> serializeResponse(GetRoomStateResponse resp);
	static std::vector<char> serializeResponse(LeaveRoomResponse resp);

private:
	/*
		Converts int to 4 bytes of buffer
		Input: unsigned int
		Output: buffer
	*/
	static std::vector<char> intToBinary(unsigned int num);
	/*
		Creates a buffer response from a json
		Input: the json and the response code
		Output: buffer
	*/
	static std::vector<char> createBuff(json j, unsigned int code);
	/*
		Converts vector of rooms to vector of jsons
		Input: vector of rooms
		Output: vector of jsons
	*/
	static std::vector<json> createJsonRoomArray(std::vector<RoomData> rooms);
	/*
		Converts vector of highscores to vector of jsons
		Input: vector of highscores
		Output: vector of jsons
	*/
	static std::vector<json> createJsonHighscoresArray(std::vector<Highscore> highscores);
};
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

struct SubmitAnswerRequest
{
	std::string answer;
	unsigned int time;
};


class JsonRequestPacketDeserializer
{
public:
	/*
		Desirializes login request
		Input: Buffer
		Output: login request
	*/
	static LoginRequest deserializeLoginRequest(std::vector<char> req);
	/*
		Desirializes signup request
		Input: Buffer
		Output: signup request
	*/
	static SignupRequest deserializeSignupRequest(std::vector<char> req);
	/*
		Desirializes get players in room request
		Input: Buffer
		Output: get players in request
	*/
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<char> req);
	/*
		Desirializes join room request
		Input: Buffer
		Output: join room request
	*/
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<char> req);
	/*
		Desirializes create room request
		Input: Buffer
		Output: create room request
	*/
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<char> req);
	/*
		Desirializes submit answer request
		Input: Buffer
		Output: submit answer request
	*/
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<char> req);
	/*
		Converts a buffer to an unsigned int
		Inputer: Buffer
		Output: unsigned int
	*/
	static unsigned int binaryToInt(char* buff);
};
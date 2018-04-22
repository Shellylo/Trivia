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

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<char> req);
	static SignupRequest deserializeSignupRequest(std::vector<char> req);
	static unsigned int binaryToInt(char* buff);
};
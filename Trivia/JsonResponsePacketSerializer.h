#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include "json.hpp"

#define ERROR_RESP_CODE 0
#define LOGIN_RESP_CODE 1
#define SIGNUP_RESP_CODE 2
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

class JsonResponsePacketSerializer
{
public:
	std::vector<char> serializeResponse(ErrorResponse resp);
	std::vector<char> serializeResponse(LoginResponse resp);
	std::vector<char> serializeResponse(SignupResponse resp);

private:
	std::vector<char> intToBinary(unsigned int num);
};
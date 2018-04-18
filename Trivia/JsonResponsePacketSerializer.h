#pragma once
#include <iostream>
#include <vector>

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
};
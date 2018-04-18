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
	std::string serializeResponse(ErrorResponse resp);
	std::string serializeResponse(LoginResponse resp);
	std::string serializeResponse(SignupResponse resp);
};
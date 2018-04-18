#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

#define ERROR 0
#define SIZE_LEN 4
#define CHAR_SIZE 8

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
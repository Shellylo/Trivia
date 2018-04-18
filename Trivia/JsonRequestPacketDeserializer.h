#pragma once
#include <iostream>
#include <vector>

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
	LoginRequest deserializeLoginRequest(std::string req);
	SignupRequest deserializeSignupRequest(std::string req);
};
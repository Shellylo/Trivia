#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"

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
	LoginRequest deserializeLoginRequest(std::vector<char> req);
	SignupRequest deserializeSignupRequest(std::vector<char> req);
};
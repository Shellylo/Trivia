#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> req)
{
	json j = json::parse(req.begin(), req.end());
	return {j["username"], j["password"]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> req)
{

	json j = json::parse(req.begin(), req.end());
	return { j["username"], j["password"], j["email"] };
}

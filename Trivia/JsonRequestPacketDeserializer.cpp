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

unsigned int JsonRequestPacketDeserializer::binaryToInt(char * buff)
{
	int ret = 0;
	for (int i = 0; i < SIZE_LEN; i++)
	{
		ret += (buff[SIZE_LEN - i - 1] * pow(2, i * CHAR_SIZE));
	}
	return ret;
}

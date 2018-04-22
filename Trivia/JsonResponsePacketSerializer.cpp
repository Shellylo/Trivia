#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse resp)
{
	std::vector<char> buff;
	json j = { { "message", resp.message } };
	std::string js = j.dump();
	std::vector<char> dataSize = intToBinary(js.length());
	buff.push_back(ERROR_RESP_CODE);
	buff.insert(buff.end(), dataSize.begin(), dataSize.end());
	buff.insert(buff.end(), js.begin(), js.end());
	return buff;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse resp)
{
	std::vector<char> buff;
	json j = { { "status", resp.status } };
	std::string js = j.dump();
	std::vector<char> dataSize = intToBinary(js.length());
	buff.push_back(LOGIN_RESP_CODE);
	buff.insert(buff.end(), dataSize.begin(), dataSize.end());
	buff.insert(buff.end(), js.begin(), js.end());
	return buff;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse resp)
{
	std::vector<char> buff;
	json j = { { "status", resp.status } };
	std::string js = j.dump();
	std::vector<char> dataSize = intToBinary(js.length());
	buff.push_back(SIGNUP_RESP_CODE);
	buff.insert(buff.end(), dataSize.begin(), dataSize.end());
	buff.insert(buff.end(), js.begin(), js.end());
	return buff;
}

std::vector<char> JsonResponsePacketSerializer::intToBinary(unsigned int num)
{
	std::vector<char> ret = { '\0', '\0','\0','\0' };
	for (int i = 0; i < SIZE_LEN && num != 0; i++)
	{
		ret[SIZE_LEN - 1 - i] += num % 256;
		num /= 256;
	}
	return ret;
}

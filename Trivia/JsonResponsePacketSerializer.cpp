#include "JsonResponsePacketSerializer.h"

std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse resp)
{
	std::vector<char> buff;
	std::vector<char> dataSize = intToBinary(resp.message.length());
	buff.push_back(ERROR);
	buff.insert(buff.end(), dataSize.begin(), dataSize.end());
	buff.insert(buff.end(), resp.message.begin(), resp.message.end());
	return buff;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse resp)
{
	std::vector<char> ret;
	ret.push_back(resp.status);
	for (int i = 0; i < SIZE_LEN; i++)
	{
		ret.push_back(0);
	}
	return ret;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse resp)
{
	std::vector<char> ret;
	ret.push_back(resp.status);
	for (int i = 0; i < SIZE_LEN; i++)
	{
		ret.push_back(0);
	}
	return ret;
}

std::vector<char> JsonResponsePacketSerializer::intToBinary(unsigned int num)
{
	std::vector<char> ret = { '\0', '\0','\0','\0' };
	for (int i = 0; i < SIZE_LEN && num != 0; i++)
	{
		for (int k = 0; k < CHAR_SIZE && num != 0; k++)
		{
			ret[SIZE_LEN - 1 - i] += num%2 * pow(2, k);
			num /= 2;
		}
	}
	return ret;
}

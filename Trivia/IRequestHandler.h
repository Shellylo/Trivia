#pragma once
#include <ctime>
#include <iostream>
#include <vector>

class IRequestHandler;

struct Request
{
	int id;
	std::time_t receivalTime;
	std::vector<char> buffer;
};

struct RequestResult
{
	std::vector<char> buffer;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request req) = 0;
	virtual RequestResult handleRequest(Request req) = 0;
};
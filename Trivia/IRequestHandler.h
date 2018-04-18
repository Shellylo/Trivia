#pragma once
#include <iostream>
#include <vector>

class IRequestHandler;

struct Request
{
	int reqCode;
	int dataLength;
	std::string buffer;
};

struct RequestResult
{
	std::string buffer;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(Request req) = 0;
	virtual RequestResult handleRequest(Request req) = 0;
};
#pragma once
#include <iostream>
#include <vector>

class IRequestHandler;

struct Request
{
	int reqCode;
	int dataLength;
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
	/*
		Checks if the request relevant (pure virtual function)
		Input: the request
		Output: true if does, false otherwise
	*/
	virtual bool isRequestRelevant(Request req) = 0;
	/*
		Handles the request (pure virtual function)
		Input: the request
		Output: the result
	*/
	virtual RequestResult handleRequest(Request req) = 0;
};
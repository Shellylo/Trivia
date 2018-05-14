#pragma once
#include <iostream>
#include <vector>

enum reqCodes
{
	LOGIN_REQ_CODE = 1,
	SIGNUP_REQ_CODE,
	LOGOUT_REQ_CODE,
	GETROOMS_REQ_CODE,
	GETPLAYERSROOM_REQ_CODE,
	JOINROOM_REQ_CODE,
	CREATEROOM_REQ_CODE,
	GETHIGHSCORES_REQ_CODE,
	CLOSEROOM_REQ_CODE,
	STARTGAME_REQ_CODE,
	GETROOMSTATE_REQ_CODE,
	LEAVEROOM_REQ_CODE
};

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
	virtual bool isRequestRelevant(Request req) = 0;
	virtual RequestResult handleRequest(Request req) = 0;
};
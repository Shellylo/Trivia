#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define LOGIN_REQ_CODE 1
#define SIGNUP_REQ_CODE 2

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	/*
		Creates a LoginRequestHandler
	*/
	LoginRequestHandler(LoginManager& manager, RequestHandlerFactory& handlerFactory);

	/*
		Comment in the pure virtual function
	*/
	bool isRequestRelevant(Request req) override;
	/*
		Comment in the pure virtual function
	*/
	RequestResult handleRequest(Request req) override;
	/*
		Disconnects a user
		Input: username
		Output: none
	*/
	void disconnectUser(std::string user);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	/*
		Handles the login request
		Input: the request
		Output: the request result
	*/
	RequestResult login(Request req);
	/*
		Handles the signup request
		Input: the request
		Output: the request result
	*/
	RequestResult signup(Request req);
};
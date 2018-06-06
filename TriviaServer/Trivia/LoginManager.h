#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "Helper.h"

class LoginManager
{
public:
	/*
		Creates a LogginManager
	*/
	LoginManager(IDatabase& database);

	/*
		Signs up a user
		Input: username, password, email
		Output: none (exception if there is a problem)
	*/
	void signup(std::string name, std::string pass, std::string email);
	/*
		Logs in a user
		Input: username, password
		Output: none (exception if there is a problem)
	*/
	void login(std::string name, std::string pass);
	/*
		Logs out a user
		Input: username
		Output: none (exception if there is a problem)
	*/
	void logout(std::string name); // receive name?

private:
	IDatabase& m_database;
	std::vector<LoggedUser> m_logged_users;

	/*
		Checks if a username is a valid username
		Input: username
		Output: true if valid, false otherwise
	*/
	bool isValidName(std::string name) { return true; }
	/*
		Checks if a password is a valid password
		Input: password
		Output: true if valid, false otherwise
	*/
	bool isValidPass(std::string pass) { return true; }
	/*
		Checks if an email is a valid email
		Input: email
		Output: true if valid, false otherwise
	*/
	bool isValidEmail(std::string email) { return true; }
};
#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "Helper.h"

class LoginManager
{
public:
	LoginManager(IDatabase& database);

	void signup(std::string name, std::string pass, std::string email);
	void login(std::string name, std::string pass);
	void logout(std::string name); // receive name?

private:
	IDatabase& m_database;
	std::vector<LoggedUser> m_logged_users;

	bool isValidName(std::string name) { return true; }
	bool isValidPass(std::string pass) { return true; }
	bool isValidEmail(std::string email) { return true; }
};
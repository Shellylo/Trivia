#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"

class LoginManager
{
public:
	void signup(std::string name, std::string pass, std::string email);
	void login(std::string name, std::string pass);
	void logout();

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_logged_users;
};
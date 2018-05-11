#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	bool operator==(LoggedUser& other);

private:
	std::string m_username;
};
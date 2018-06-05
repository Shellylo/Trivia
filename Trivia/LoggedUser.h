#pragma once
#include <iostream>
#include <string>

class LoggedUser
{
public:
	/*
		Creates a LoggedUser
	*/
	LoggedUser(std::string username);
	/*
		Returns the username
		Input: none
		Output: the username
	*/
	std::string getUsername() const;
	/*
		Compares 2 logged users
		Input: other logged user
		Output: true if same username, false otherwise
	*/
	bool operator==(LoggedUser& other) const;
	bool operator<(const LoggedUser& other) const;
	bool operator>(const LoggedUser& other) const;

private:
	std::string m_username;
};
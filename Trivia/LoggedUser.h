#pragma once
#include <iostream>

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
	std::string getUsername();
	/*
		Compares 2 logged users
		Input: other logged user
		Output: true if same, false otherwise
	*/
	bool operator==(LoggedUser& other);

private:
	std::string m_username;
};
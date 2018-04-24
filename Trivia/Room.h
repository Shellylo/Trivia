#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>
#include <iostream>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers; //was string changed to int
	unsigned int questionCount; //added this
	unsigned int timePerQuestion;
	bool isActive; //was int changed to boolean
};

class Room
{
public:
	void addUser(LoggedUser user);
	void removeUser(std::string user); //string or logged user?
	std::vector<LoggedUser> getAllUsers();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
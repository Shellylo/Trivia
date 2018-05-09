#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "Helper.h"

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
	Room(unsigned int id, CreateRoomRequest roomData, LoggedUser manager);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	
	RoomData getRoomData() const;
	std::vector<LoggedUser> getAllUsers() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
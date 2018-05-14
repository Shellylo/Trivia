#pragma once
#include <string>
#include "LoggedUser.h"
#include <vector>
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "Helper.h"

#define WAITING 1
#define CLOSED 2
#define STARTED 3

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers; //was string changed to int
	unsigned int questionCount; //added this
	unsigned int timePerQuestion;
	unsigned int roomState; // 1 - waiting, 2 - closed, 3 - game started
};

class Room
{
public:
	Room();
	Room(unsigned int id, CreateRoomRequest roomData, LoggedUser manager);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	
	RoomData getRoomData() const;
	std::vector<LoggedUser> getAllUsers() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
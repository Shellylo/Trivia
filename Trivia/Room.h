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
	/*
		Creates a Room
	*/
	Room(unsigned int id, CreateRoomRequest roomData, LoggedUser manager);

	/*
		Adds a user to the room
		Input: the user to add
		Output: none
	*/
	void addUser(LoggedUser user);
	/*
		Removes a user from the room
		Input: the user to remove
		Output: none
	*/
	void removeUser(LoggedUser user);
	/*
		Returns the room data
		Input: none
		Output: the room data
	*/
	RoomData getRoomData() const;
	/*
		Returns all the user in the room
		Input: none
		Output: vector of LoggedUser
	*/
	std::vector<LoggedUser> getAllUsers() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
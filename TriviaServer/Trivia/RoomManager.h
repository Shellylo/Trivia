#pragma once
#include "LoggedUser.h"
#include <vector>
#include "Room.h"
#include <map>
#include "JsonRequestPacketDeserializer.h"
#include <utility>

class RoomManager
{
public:
	/*
		Creates a RoomManager
	*/
	RoomManager();

	/*
		Adds a room to the room map
		Input: user that created the room, room data
		Output: none (exception if there is a problem)	
	*/
	Room& createRoom(LoggedUser user, CreateRoomRequest roomData);
	/*
		Deletes a room from the map of rooms
		Input: room id
		Output: none (exception if there is a problem)
	*/
	void deleteRoom(int ID);
	/*
		Returns the room state
		Input: room id
		Output: the state of the room (exception if there is a problem)
	*/
	int getRoomState(int ID);
	/*
		Adds a user to the room
		Input: user to add, room id
		Output: none (exception if there is a problem)
	*/
	Room& joinRoom(LoggedUser user, int ID);
	/*
		Removes a user from the room
		Input: user to remove, room id
		Output: none (exception if there is a problem)
	*/
	void leaveRoom(LoggedUser user, int ID);
	/*
		Returns all the players in a specific room
		Input: room id
		Output: vector of players username (exception if there is a problem)
	*/
	std::vector<std::string> getPlayersInRoom(int ID);
	/*
		Returns all the rooms
		Input: none
		Output: vector of rooms (exception if there is a problem)
	*/
	std::vector<RoomData> getRooms();
	/*
		Closes the room
		Input: room and user
		Output: none
	*/
	void closeRoom(Room& room, LoggedUser user);

private:
	std::map<int, Room> m_rooms;

	/*
		Gets a room
		Input: room id
		Output: room (exception if there is a problem)
	*/
	Room& getRoom(int ID);
	/*
		Checks if a user exists in a room
		Input: user and room
		Output: true if does, false otherwise
	*/
	bool doesUserExist(const LoggedUser& user, const Room& room);
};
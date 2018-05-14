#include "RoomManager.h"

Room& RoomManager::createRoom(LoggedUser user, CreateRoomRequest roomData)
{
	static int id = 0;
	m_rooms.insert(std::pair<int, Room>(id, Room(id, roomData, user)));
	id++;
	return m_rooms[id - 1];
}

void RoomManager::deleteRoom(int ID)
{
	if (!m_rooms.erase(ID))
	{
		throw;
	}
}

bool RoomManager::getRoomState(int ID)
{
	return getRoom(ID).getRoomData().roomState;
}

Room& RoomManager::joinRoom(LoggedUser user, int ID)
{
	Room& room = getRoom(ID);
	if (room.getRoomData().roomState != WAITING)
	{
		throw std::exception();
	}
	if (doesUserExist(user, room)) // user already exists
	{
		throw;
	}
	room.addUser(user);
	return room;
}

void RoomManager::leaveRoom(LoggedUser user, int ID)
{
	Room& room = getRoom(ID);
	if (!doesUserExist(user, room)) // user doesn't exist
	{
		throw;
	}
	room.removeUser(user);
}

std::vector<std::string> RoomManager::getPlayersInRoom(int ID)
{
	std::vector<LoggedUser> roomUsers = getRoom(ID).getAllUsers();
	std::vector<std::string> ret;
	for (std::vector<LoggedUser>::iterator it = roomUsers.begin(); it != roomUsers.end(); it++)
	{
		ret.push_back(it->getUsername());
	}
	return ret;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> ret;
	for (std::map<int, Room>::iterator it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		ret.push_back((it->second).getRoomData());
	}
	return ret;
}

Room& RoomManager::getRoom(int ID)
{
	std::map<int, Room>::iterator it = m_rooms.find(ID);
	if (it == m_rooms.end()) // room not found
	{
		throw;
	}
	return it->second;
}

bool RoomManager::doesUserExist(const LoggedUser& user,const Room& room)
{
	std::vector<LoggedUser> roomUsers = room.getAllUsers();
	return Helper::find(roomUsers, user) != roomUsers.end();
}

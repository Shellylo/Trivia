#include "RoomManager.h"

RoomManager::RoomManager()
{
}

Room& RoomManager::createRoom(LoggedUser user, CreateRoomRequest roomData)
{
	static int id = 0;
	m_rooms[id] = Room(id, roomData, user);
	//m_rooms.insert(std::pair<int, Room>(id, Room(id, roomData, user)));
	return m_rooms[id++];
}

void RoomManager::deleteRoom(int ID)
{
	if (!m_rooms.erase(ID))
	{
		throw std::exception();
	}
}

int RoomManager::getRoomState(int ID)
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
		throw std::exception();
	}
	room.addUser(user);
	return room;
}

void RoomManager::leaveRoom(LoggedUser user, int ID)
{
	Room& room = getRoom(ID);
	if (!doesUserExist(user, room)) // user doesn't exist
	{
		throw std::exception();
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

void RoomManager::closeRoom(Room & room, LoggedUser user)
{
	if (!doesUserExist(user, room)) // user doesn't exist
	{
		throw std::exception();
	}
	room.removeUser(user);
	room.setState(CLOSED);
	if (room.getAllUsers().empty())
	{
		m_rooms.erase(room.getRoomData().id);
	}
}

Room& RoomManager::getRoom(int ID)
{
	std::map<int, Room>::iterator it = m_rooms.find(ID);
	if (it == m_rooms.end()) // room not found
	{
		throw std::exception();
	}
	return it->second;
}

bool RoomManager::doesUserExist(const LoggedUser& user,const Room& room)
{
	std::vector<LoggedUser> roomUsers = room.getAllUsers();
	return Helper::find(roomUsers, user) != roomUsers.end();
}

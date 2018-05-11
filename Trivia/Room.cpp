#include "Room.h"

Room::Room(unsigned int id, CreateRoomRequest roomData, LoggedUser manager) : m_metadata(RoomData{id, roomData.name, roomData.maxPlayers, roomData.questionCount, roomData.answerTimeout, false})
{
	m_users.push_back(manager);
}

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	m_users.erase(Helper::find(m_users, user));
}

std::vector<LoggedUser> Room::getAllUsers() const
{
	return m_users;
}

RoomData Room::getRoomData() const
{
	return m_metadata;
}
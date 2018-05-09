#pragma once
#include "LoggedUser.h"
#include <vector>
#include "Room.h"
#include <map>
#include "JsonRequestPacketDeserializer.h"
#include "Helper.h"
#include <utility>

class RoomManager
{
public:
	void createRoom(LoggedUser user, CreateRoomRequest roomData);
	void deleteRoom(int ID);
	bool getRoomState(int ID);
	void joinRoom(LoggedUser user, int ID);
	void leaveRoom(LoggedUser user, int ID);
	std::vector<std::string> getPlayersInRoom(int ID);
	std::vector<RoomData> getRooms();
private:
	std::map<int, Room> m_rooms;

	Room getRoom(int ID);
	bool doesUserExist(const LoggedUser& user, const Room& room);
};
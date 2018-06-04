#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "Room.h"
#include "Game.h"

class GameManager
{
public:
	/*
		Creates a LogginManager
	*/
	GameManager(IDatabase& database);

	Game& createGame(LoggedUser user, Room room);
	Game& joinGame(LoggedUser user, int roomId);
	void deleteGame(Game& game);

private:
	IDatabase& m_database;
	std::map<int, Game> m_games;
};
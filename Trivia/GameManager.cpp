#include "GameManager.h"

GameManager::GameManager(IDatabase & database) : m_database(database)
{
}

Game & GameManager::createGame(LoggedUser user, Room room)
{
	int id = m_database.createGame(time(NULL));
	std::vector<Question> questions = m_database.getQuestions(room.getRoomData().questionCount);
	std::map<LoggedUser, GameData> players;
	std::vector<LoggedUser> users = room.getAllUsers();
	for (int i = 0; i < users.size(); i++)
	{
		players[users[i]] = GameData{questions[0], 0, 0, 0, 0};
	}
	m_games[room.getRoomData().id] = Game(id, questions, players);
	return m_games[room.getRoomData().id];
}

Game& GameManager::joinGame(LoggedUser user, int roomId)
{
	std::map<LoggedUser, GameData> players = m_games[roomId].getPlayers();
	if (players.find(user) == players.end())
	{
		throw std::exception();
	}
	return m_games[roomId];
}

void GameManager::deleteGame(Game & game)
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	m_database.finishGame(game.getId(), asctime(localtm));
	for (std::map<int, Game>::iterator it = m_games.begin(); it != m_games.end(); it++)
	{
		if (it->second == game)
		{
			m_games.erase(it);
		}
	}
}

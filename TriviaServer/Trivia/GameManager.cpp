#include "GameManager.h"

GameManager::GameManager(IDatabase & database) : m_database(database)
{
}

Game & GameManager::createGame(LoggedUser user, Room room)
{
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int id = m_database.createGame(asctime(localtm));
	std::vector<Question> questions = m_database.getQuestions(room.getRoomData().questionCount);
	std::map<LoggedUser, GameData> players;
	std::vector<LoggedUser> users = room.getAllUsers();
	for (int i = 0; i < users.size(); i++)
	{
		players.find(users[i])->second = GameData{questions[0], 0, 0, 0, 0};
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

std::string GameManager::submitAnswer(LoggedUser user, Game & game, std::string answer)
{
	std::string currentQs = game.getQuestionForUser(user).getQs();
	std::string correctAnswer =  game.submitAnswer(user, answer);
	time_t now = time(0);
	tm* localtm = localtime(&now);
	m_database.addAnswer(game.getId(), user.getUsername(), answer, answer == correctAnswer, asctime(localtm), currentQs);
	return correctAnswer;
}

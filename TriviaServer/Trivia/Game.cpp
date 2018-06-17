#include "Game.h"

Game::Game(int id, std::vector<Question> questions, std::map<LoggedUser, GameData> players) : id(id), m_questions(questions), m_players(players)
{
}

bool Game::operator==(Game game)
{
	return id == game.id;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	if (m_players.find(user) == m_players.end()) // player doesn't exist in game
	{
		throw std::exception();
	}
	GameData& playerGameData = (m_players.find(user)->second);
	playerGameData.time = time(NULL);
//	m_players[user].time = time(NULL);
	return playerGameData.currentQuestion;
}

std::string Game::submitAnswer(LoggedUser user, std::string answer)
{
	if (m_players.find(user) == m_players.end()) { throw std::exception(); } // player doesn't exist in game
	GameData& playerGameData = (m_players.find(user)->second);
	playerGameData.time = time(NULL) - playerGameData.time;
	std::string correctAns = playerGameData.currentQuestion.getCorrectAns();
	answer == correctAns ? playerGameData.correctAnswerCount++ : playerGameData.wrongAnswerCount++;
	playerGameData.averageAnswerTime = ((playerGameData.averageAnswerTime * (playerGameData.correctAnswerCount + playerGameData.wrongAnswerCount - 1)) + playerGameData.time) / (playerGameData.correctAnswerCount + playerGameData.wrongAnswerCount);
	std::string currentQuestion = playerGameData.currentQuestion.getQs();
	int qsNum = m_questions.size();
	for (int i = 0; i < qsNum; i++)
	{
		if (currentQuestion == m_questions[i].getQs())
		{
			i == qsNum - 1 ? playerGameData.currentQuestion = Question("", "", std::vector<std::string>()) : playerGameData.currentQuestion = m_questions[i + 1];
		}
	}
	return correctAns;
}

bool Game::removePlayer(LoggedUser user)
{
	if (m_players.find(user) == m_players.end()) { throw std::exception(); } // player doesn't exist in game
	m_players.erase(user);
	return m_players.size();
}

std::vector<PlayerResults> Game::getPlayersResults()
{
	std::vector<PlayerResults> results;
	for (std::map<LoggedUser, GameData>::iterator it = m_players.begin(); it != m_players.end(); it++)
	{
		results.push_back(PlayerResults{ (it->first).getUsername(), (it->second).correctAnswerCount, (it->second).wrongAnswerCount, (it->second).averageAnswerTime });
	}
	return results;
}

int Game::getId()
{
	return id;
}

std::map<LoggedUser, GameData> Game::getPlayers()
{
	return m_players;
}

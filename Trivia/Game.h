#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "LoggedUser.h"
#include "Question.h"

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	unsigned int time;
};

class Game
{
public:
	Game(int id, std::vector<Question> questions, std::map<LoggedUser, GameData> players);

	Question getQuestionForUser(LoggedUser user);
	std::string submitAnswer(LoggedUser user, std::string answer); //returns correct answer
	bool removePlayer(LoggedUser user);
	std::vector<PlayerResults> getPlayersResults();
	
	std::map<LoggedUser, GameData> getPlayers();
	int getId();

private:
	int id;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};

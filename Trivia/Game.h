#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "LoggedUser.h"
#include "Question.h"

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

class Game
{
public:
	Question getQuestionForUser(LoggedUser user);
	std::string submitAnswer(std::string answer); //returns correct answer
	void removePlayer(LoggedUser user);

private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};

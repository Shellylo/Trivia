#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "LoggedUser.h"
#include "Question.h"
#include <time.h>
#include <string>

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

	/*
		Compares games ID's
		Input: other game
		Output: true if same id, false otherwise
	*/
	bool operator==(Game game);

	/*
		Gets current question (and saves asked time)
		Input: user
		Output: the current question
	*/
	Question getQuestionForUser(LoggedUser user);
	/*
		Updates game data for user who submitted answer
		Input: the user, the answer
		Output: the correct answer
	*/
	std::string submitAnswer(LoggedUser user, std::string answer); //returns correct answer
	/*
		Removes a player from the game
		Input: user to remove from the game
		Output: true if there are players left, false otherwise
	*/
	bool removePlayer(LoggedUser user);
	/*
		Gets all Game Players results
		Input: none
		Output: players results (for each one: the amount of correct and wrong answers and average answer time)
	*/
	std::vector<PlayerResults> getPlayersResults();

private:
	int id;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};
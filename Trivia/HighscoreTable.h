#pragma once
#include <iostream>
#include <vector>
#include "SqliteDatabase.h"

class HighscoreTable
{
public:
	/*
		Creates a HighscoreTable
	*/
	HighscoreTable(IDatabase& database);
	/*
		Gets the top 5 scores of all users
		Input: none
		Output: vector of the highscores	
	*/
	std::vector<Highscore> getHighscores();
	/*
		Gets the top 5 scores of a specific user
		Input: the user	
		Output: vector of the highscores
	*/
	std::vector<Highscore> getHighscores(std::string username);

private:
	IDatabase& m_database;
};
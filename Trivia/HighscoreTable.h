#pragma once
#include <iostream>
#include <vector>
#include "SqliteDatabase.h"

class HighscoreTable
{
public:
	HighscoreTable(IDatabase& database);
	std::vector<Highscore> getHighscores();
	std::vector<Highscore> getHighscores(std::string username);

private:
	IDatabase& m_database;
};
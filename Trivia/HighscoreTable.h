#pragma once
#include <vector>
#include "SqliteDatabase.h"

struct Highscore
{

};

class HighscoreTable
{
public:
	HighscoreTable(IDatabase& database);
	std::vector<Highscore> getHighscores();
private:
	IDatabase& m_database;
};
#include "HighscoreTable.h"

HighscoreTable::HighscoreTable(IDatabase & database) : m_database(database)
{
}

std::vector<Highscore> HighscoreTable::getHighscores()
{
	return m_database.getHighscores();
}

std::vector<Highscore> HighscoreTable::getHighscores(std::string username)
{
	return m_database.getHighscores(username);
}

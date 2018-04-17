#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase() : IDatabase()
{
}

std::map<LoggedUser, int> SqliteDatabase::getHighscores()
{
	return std::map<LoggedUser, int>();
}

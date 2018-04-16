#pragma once
#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "IDatabase.h"

class SqliteDatabase : IDatabase
{
	std::map<LoggedUser, int> getHighscores() override;
	bool doesUserExist(std::string username) override;
	std::list<Question> getQuestions(int num) override;
};
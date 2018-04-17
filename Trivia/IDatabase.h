#pragma once
#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"

class IDatabase
{
public:
	IDatabase();
	virtual std::map<LoggedUser, int> getHighscores() = 0;
	virtual bool doesUserExist(std::string username) = 0;
	//virtual std::list<Question> getQuestions(int num) = 0;
};
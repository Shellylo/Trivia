#pragma once
#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"

class IDatabase
{
public:
	IDatabase();

	virtual bool open() = 0;
	virtual void close() = 0;

	virtual std::map<LoggedUser, int> getHighscores() = 0;
	virtual bool doesUserExist(std::string username) = 0;
	virtual void addUser(std::string username, std::string pass, std::string email) = 0;
	virtual bool passMatches(std::string username, std::string pass) = 0;
	virtual std::list<Question> getQuestions(int num) = 0;
};
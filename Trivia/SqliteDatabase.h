#pragma once
#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>	

#define DB_NAME "TriviaDB.sqlite"
#define TABLES_NUM 3

class SqliteDatabase : public IDatabase
{ 
public:
	SqliteDatabase();

	bool open() override;
	void close() override;

	std::map<LoggedUser, int> getHighscores() override;
	bool doesUserExist(std::string username) override;
	void addUser(std::string username, std::string pass, std::string email) override;
	bool passMatches(std::string username, std::string pass) override { return true; }
	std::list<Question> getQuestions(int num) override;
private:
	sqlite3* db;

	bool initDB();
	void sendStatement(std::string statement);
	void sendStatement(std::string statement, int(*func)(void *, int, char **, char **), void * ans);

	static int doesExistCallback(void * data, int argc, char ** argv, char ** colName);
};
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

#define HIGHSCORES_NUM "5"

class SqliteDatabase : public IDatabase
{ 
public:
	/*
		Creates a SqliteDatabase
	*/
	SqliteDatabase();

	/*
		Comment in the pure virtual function
	*/
	bool open() override;
	/*
		Comment in the pure virtual function
	*/
	void close() override;

	/*
		Comment in the pure virtual function
	*/
	std::vector<Highscore> getHighscores() override;
	/*
		Comment in the pure virtual function
	*/
	std::vector<Highscore> getHighscores(std::string username) override;
	//std::map<LoggedUser, int> getHighscores() override; // why?
	/*
		Comment in the pure virtual function
	*/
	bool doesUserExist(std::string username) override;
	/*
		Comment in the pure virtual function
	*/
	void addUser(std::string username, std::string pass, std::string email) override;
	/*
		Comment in the pure virtual function
	*/
	bool passMatches(std::string username, std::string pass) override;
	/*
		Comment in the pure virtual function
	*/
	std::vector<Question> getQuestions(int num) override { return std::vector<Question>(); };

private:
	sqlite3* db;

	/*
		Initializes the database
		Input: none
		Output: true if succeeded, false otherwise
	*/
	bool initDB();
	/*
		Sends a sqlite statement
		Input: the statement
		Output: none
	*/
	void sendStatement(std::string statement);
	/*
		Sends a sqlite statement
		Input: the statement, callback function, pointer to a "return" value
		Output: none
	*/
	void sendStatement(std::string statement, int(*func)(void *, int, char **, char **), void * ans);

	/*
		Call back function that checks if something exists
		Input: void* data (must be bool*), argument count, arguments, column names
		Output: int
	*/
	static int doesExistCallback(void * data, int argc, char ** argv, char ** colName);
	/*
		Call back function that handles the highscore request
		Input: void* data (must be vector<Highscore>*), argument count, arguments, column names
		Output: int
	*/
	static int getHighscores(void * data, int argc, char ** argv, char ** colName);
};
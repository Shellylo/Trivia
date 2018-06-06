#pragma once
#include <iostream>
#include <map>
#include <list>
#include "LoggedUser.h"
#include "Question.h"
#include "Highscore.h"

class IDatabase
{
public:
	/*
		Creates an IDatabase
	*/
	IDatabase();

	/*
		Opens a database (pure virtual function)
		Input: none
		Output: true if succeeded, false otherwise
	*/
	virtual bool open() = 0;
	/*
		Closes the database (pure virtual function)
		Input: none	
		Output: none
	*/
	virtual void close() = 0;

	/*
		Checks if a user exists in a database (pure virtual function)
		Input: the usernamse	
		Output: true if does, false otherwise
	*/
	virtual bool doesUserExist(std::string username) = 0;
	/*
		Adds a user to the database (pure virtual function)
		Input: username, password, email	
		Output: none
	*/
	virtual void addUser(std::string username, std::string pass, std::string email) = 0;
	/*
		Checks if a password matches the username password (pure virtual function)
		Input: username, password
		Output: true if does, false otherwise
	*/
	virtual bool passMatches(std::string username, std::string pass) = 0;
	/*
		Gets the questions from the database (pure virtual function)
		Input: none
		Output: a vector of questions
	*/
	virtual std::vector<Question> getQuestions(int num) = 0;
	/*
		Gets the top 5 scores of all users (pure virtual function)
		Input: none
		Output: vector of the highscores
	*/
	virtual std::vector<Highscore> getHighscores() = 0;
	/*
		Gets the top 5 scores of a specific user (pure virtual function)
		Input: the user
		Output: vector of the highscores
	*/
	virtual std::vector<Highscore> getHighscores(std::string username) = 0;
	//virtual std::map<LoggedUser, int> getHighscores() = 0; //why??
	/*
		Adds new game into database
		Input: game start time
		Output: inserted game ID
	*/
	virtual int createGame(std::string startTime) = 0;
	/*
		Adds game end time into database and updates game status
		Input: game ID, game end time
		Output: none
	*/
	virtual void finishGame(int gameId, std::string endTime) = 0; // change status to 0
	/*
		Adds new player answer into database
		Input: game ID, username, the answer, answer is correct or not, time answered (length), the question
		Output: none
	*/
	virtual void addAnswer(int gameId, std::string username, std::string answer, bool isCorrect, std::string time, std::string question) = 0;
};
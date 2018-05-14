#pragma once
#include <string>
#include <vector>

class Question
{
public:
	/*
		Creates a Question
	*/
	Question(std::string qs, std::string correctAns, std::vector<std::string> anss);

	/*
		Returns the question
		Input: none
		Output: the question
	*/
	std::string getQs();
	/*
		Returns the correct answer
		Input: none
		Output: the answer
	*/
	std::string getCorrectAns();
	/*
		Returns the vector of the wrong answers
		Input: none
		Output: the vector of the answers
	*/
	std::vector<std::string> getAnss();
private:
	std::string qs;
	std::string correctAns;
	std::vector<std::string> anss;
};
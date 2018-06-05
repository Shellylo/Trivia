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
		Copies received question (the question and its answers)
		Input: the question to be copied
		Output: question with the copied data in it (reference to the current question object)
	*/
	Question& operator=(Question& q);

	/*
		Returns the question
		Input: none
		Output: the question
	*/
	std::string getQs() const;
	/*
		Returns the correct answer
		Input: none
		Output: the answer
	*/
	std::string getCorrectAns() const;
	/*
		Returns the vector of the wrong answers
		Input: none
		Output: the vector of the answers
	*/
	std::vector<std::string> getAnss() const;
	/*
		Sets the question to be received question
		Input: the question to set
		Output: none
	*/
	void setQs(std::string question);
	/*
		Sets the correct answer
		Input: the correct answer
		Output: none
	*/
	void setCorrectAns(std::string correctAns);
	/*
		Sets wrong answers vector
		Input: the wrong answers vector
		Output: none
	*/
	void setAnswers(std::vector<std::string> answers);

private:
	std::string qs;
	std::string correctAns;
	std::vector<std::string> anss;
};
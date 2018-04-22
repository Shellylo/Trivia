#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(std::string qs, std::string correctAns, std::vector<std::string> anss);

	std::string getQs();
	std::string getCorrectAns();
	std::vector<std::string> getAnss();
private:
	std::string qs;
	std::string correctAns;
	std::vector<std::string> anss;
};
#include "Question.h"

Question::Question(std::string qs, std::string correctAns, std::vector<std::string> anss)
{
	this->qs = qs;
	this->correctAns = correctAns;
	this->anss = anss;
}

std::string Question::getQs()
{
	return qs;
}

std::string Question::getCorrectAns()
{
	return correctAns;
}

std::vector<std::string> Question::getAnss()
{
	return anss;
}

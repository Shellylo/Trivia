#include "Question.h"

Question::Question(std::string qs, std::string correctAns, std::vector<std::string> anss)
{
	this->qs = qs;
	this->correctAns = correctAns;
	this->anss = anss;
}

Question& Question::operator=(Question& q)
{
	this->qs = q.qs;
	this->correctAns = q.correctAns;
	this->anss = q.anss;
	return *this;
}

std::string Question::getQs() const
{
	return qs;
}

std::string Question::getCorrectAns() const
{
	return correctAns;
}

std::vector<std::string> Question::getAnss() const
{
	return anss;
}

void Question::setQs(std::string question)
{
	qs = question;
}

void Question::setCorrectAns(std::string correctAnswer)
{
	correctAns = correctAnswer;
}

void Question::setAnswers(std::vector<std::string> answers)
{
	anss = answers;
}

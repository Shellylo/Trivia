#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : m_username(username)
{
}

std::string LoggedUser::getUsername()
{
	return m_username;
}

bool LoggedUser::operator==(LoggedUser & other)
{
	return m_username == other.m_username;
}

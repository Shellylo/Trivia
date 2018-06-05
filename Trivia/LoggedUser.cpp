#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : m_username(username)
{
}

std::string LoggedUser::getUsername() const
{
	return m_username;
}

bool LoggedUser::operator==(LoggedUser & other) const
{
	return m_username == other.m_username;
}

bool LoggedUser::operator<(const LoggedUser & other) const
{
	return m_username < other.m_username;
}

bool LoggedUser::operator>(const LoggedUser & other) const
{
	return m_username > other.m_username;
}

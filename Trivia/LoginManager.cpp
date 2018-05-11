#include "LoginManager.h"

LoginManager::LoginManager(IDatabase & database) : m_database(database)
{
}

void LoginManager::signup(std::string name, std::string pass, std::string email)
{
	if (m_database.doesUserExist(name))
	{
		throw;
	}
	if (!isValidName(name) || !isValidPass(pass) || !isValidEmail(email))
	{
		throw;
	}
	m_database.addUser(name, pass, email);
	
}

void LoginManager::login(std::string name, std::string pass)
{
	if (!m_database.doesUserExist(name))
	{
		throw std::exception();
	}
	if (!m_database.passMatches(name, pass))
	{
		throw;
	}
	m_logged_users.push_back(LoggedUser(name));
}

void LoginManager::logout(std::string name)
{
	std::vector<LoggedUser>::iterator user = getUser(name);
	if (user == m_logged_users.end())
	{
		throw;
	}
	m_logged_users.erase(user);
}

std::vector<LoggedUser>::iterator LoginManager::getUser(std::string name)
{
	std::vector<LoggedUser>::iterator ret = m_logged_users.end();
	for (std::vector<LoggedUser>::iterator user = m_logged_users.begin(); user != m_logged_users.end() && ret == m_logged_users.end(); user++)
	{
		if (user->getUsername() == name)
		{
			ret = user;
		}
	}
	return ret;
}

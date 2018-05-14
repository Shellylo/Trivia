#include "LoginManager.h"

LoginManager::LoginManager(IDatabase & database) : m_database(database)
{
}

void LoginManager::signup(std::string name, std::string pass, std::string email)
{
	if (m_database.doesUserExist(name))
	{
		throw std::exception();
	}
	if (!isValidName(name) || !isValidPass(pass) || !isValidEmail(email))
	{
		throw std::exception();
	}
	m_database.addUser(name, pass, email);
	
}

void LoginManager::login(std::string name, std::string pass)
{
	LoggedUser user(name);
	if (Helper::find(m_logged_users, user) != m_logged_users.end()) // user doesn't logged
	{
		throw std::exception();
	}
	if (!m_database.doesUserExist(name)) // user doesn't exist
	{
		throw std::exception();
	}
	if (!m_database.passMatches(name, pass)) // password doesn't match
	{
		throw std::exception();
	}
	m_logged_users.push_back(user);
}

void LoginManager::logout(std::string name)
{
	std::vector<LoggedUser>::iterator user = Helper::find(m_logged_users, LoggedUser(name));
	if (user == m_logged_users.end())
	{
		throw std::exception();
	}
	m_logged_users.erase(user);
}
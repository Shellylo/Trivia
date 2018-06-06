#pragma once
#include <vector>
#include <iostream>
#include "LoggedUser.h"

namespace Helper
{
	/*
		Finds a logged user in a vector of logged users
		Input: vector of logged users and a user
		Output: the iterator to the logged user or the iterator end if not found	
	*/
	std::vector<LoggedUser>::iterator find(std::vector<LoggedUser>& vec, LoggedUser value);
}
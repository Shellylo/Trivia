#include "Helper.h"

std::vector<LoggedUser>::iterator Helper::find(std::vector<LoggedUser>& vec, LoggedUser value)
{
	std::vector<LoggedUser>::iterator ret = vec.end();
	for (std::vector<LoggedUser>::iterator it = vec.begin(); it != vec.end() && ret == vec.end(); it++)
	{
		if (*it == value)
		{
			ret = it;
		}
	}
	return ret;
}


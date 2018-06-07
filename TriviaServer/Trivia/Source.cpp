#include <iostream>
#include "Server.h"
#include <exception>
#include "WSAInitializer.h"

int main()
{
	try
	{
		SqliteDatabase database;
		WSAInitializer wsaInit;
		Server s(database);
		s.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	
	system("pause");
	return 1;
}
#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase() : IDatabase()
{
}

bool SqliteDatabase::open()
{
	bool ans = true;
	std::string dbFileName = DB_NAME;
	int fileExists = _access(dbFileName.c_str(), 0);
	if (sqlite3_open(dbFileName.c_str(), &db) != SQLITE_OK)
	{
	db = nullptr;
	std::cout << "Failed to open DB" << std::endl;
	ans = false;
	}
	else if (fileExists == -1) // inits new db
	{
		ans = initDB();
	}
	return ans;
}

void SqliteDatabase::close()
{
	sqlite3_close(db);
	db = nullptr;
}

std::vector<Highscore> SqliteDatabase::getHighscores()
{
	std::vector<Highscore> ret;
	sendStatement("SELECT USERNAME, COUNT(IS_CORRECT), END_TIME FROM ANSWERS INNER JOIN GAMES ON ANSWERS.GAME_ID = GAMES.GAME_ID WHERE IS_CORRECT = 1 GROUP BY ANSWERS.GAME_ID ORDER BY COUNT(IS_CORRECT) DESC LIMIT "
				  + std::string(HIGHSCORES_NUM) + ";", getHighscores, &ret); // std::string(HIGHSCORES_NUM)
	return ret;
}

std::vector<Highscore> SqliteDatabase::getHighscores(std::string username)
{
	std::vector<Highscore> ret;
	sendStatement("SELECT USERNAME, COUNT(IS_CORRECT), END_TIME FROM ANSWERS INNER JOIN GAMES ON ANSWERS.GAME_ID = GAMES.GAME_ID WHERE USERNAME = \"" +
				  username + "\" AND IS_CORRECT = 1 GROUP BY ANSWERS.GAME_ID ORDER BY COUNT(IS_CORRECT) DESC LIMIT " + HIGHSCORES_NUM + ";", getHighscores, &ret);
	return ret;
}

bool SqliteDatabase::doesUserExist(std::string username)
{
	bool exist = false;
	sendStatement("SELECT USERNAME FROM USERS WHERE USERNAME = \"" + username + "\";", doesExistCallback, &exist);
	return exist;
}

void SqliteDatabase::addUser(std::string username, std::string pass, std::string email)
{
	sendStatement("INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES(\"" + username + "\",\"" + pass + "\",\"" + email + "\");");
}

bool SqliteDatabase::passMatches(std::string username, std::string pass)
{
	bool match = false;
	sendStatement("SELECT * FROM USERS WHERE USERNAME = \"" + username + "\" AND PASSWORD = \"" + pass + "\";", doesExistCallback, &match);
	return match;
}

bool SqliteDatabase::initDB()
{
	bool ret = true;
	char *errMessage = nullptr;
	//check DATETIME?
	char* statements[] = { "CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);",
						   "CREATE TABLE QUESTIONS (QUESTION_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, CORRECT_ANS TEXT NOT NULL, ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL, ANS4 TEXT NOT NULL);",
						   "CREATE TABLE GAMES (GAME_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, STATUS INTEGER NOT NULL , START_TIME TEXT NOT NULL, END_TIME TEXT NOT NULL);",
						   "CREATE TABLE ANSWERS (ANSWER_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, GAME_ID INTEGER NOT NULL, USERNAME TEXT NOT NULL, QUESTION_ID INTEGER NOT NULL, PLAYER_ANSWER TEXT NOT NULL, IS_CORRECT INTEGER NOT NULL, ANSWER_TIME INTEGER NOT NULL, FOREIGN_KEY(GAME_ID));" };
	for (int i = 0; i < TABLES_NUM && ret; i++)
	{
		ret = sqlite3_exec(db, statements[i], nullptr, nullptr, &errMessage) == SQLITE_OK;
	}
	return ret;
}

void SqliteDatabase::sendStatement(std::string statement)
{
	sendStatement(statement, nullptr, nullptr);
}

void SqliteDatabase::sendStatement(std::string statement, int(*func)(void *, int, char **, char **), void * ans)
{
	char* errMsg = nullptr; // saves error message
	if (sqlite3_exec(db, statement.c_str(), func, ans, &errMsg) != SQLITE_OK)
	{
		std::cout << errMsg << std::endl;
	}
}

int SqliteDatabase::doesExistCallback(void * data, int argc, char ** argv, char ** colName)
{
	*((bool*)data) = true;
	return 0;
}

int SqliteDatabase::getHighscores(void * data, int argc, char ** argv, char ** colName)
{
	Highscore highscore;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(colName[i]) == "USERNAME")
		{
			highscore.username = argv[i];
		}
		else if (std::string(colName[i]) == "COUNT(IS_CORRECT)")
		{
			highscore.score = std::stoi(argv[i]);
		}
		else if (std::string(colName[i]) == "END_TIME")
		{
			highscore.time = argv[i];
		}
	}
	((std::vector<Highscore>*)data)->push_back(highscore);
	return 0;
}

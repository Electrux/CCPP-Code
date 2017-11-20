int res;
class UserDB
{
	std::string dbname;
	sqlite3 *db;
public:
	UserDB()
	{
		dbname = defaultdbdir + "Users.db";
	}
	char *GetDBName()
	{
		return (char*)dbname.c_str();
	}
	int Open()
	{
		int temp;
		temp = sqlite3_open(dbname.c_str(), &db);
		return temp;
	}
	int Close()
	{
		int temp;
		temp = sqlite3_close(db);
		return temp;
	}
	int CheckDB()
	{
		sqlite3_stmt *state;
		std::string str;
		str = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(50), Password VARCHAR(50), IP VARCHAR(20), Logged INT(2))";
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		sqlite3_finalize(state);
		return 0;
	}
	int CheckIfExists(std::string &uname, std::string &pass, std::string ip)
	{
		sqlite3_stmt *state;
		std::string str;
		str = "SELECT * FROM Users WHERE Name = \'";
		str += uname.c_str();
		str += "\' AND Password = \'";
		str += pass.c_str();
		str += "\'";
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		int res = sqlite3_step(state);
		sqlite3_finalize(state);
		if (res == SQLITE_ROW)
		{
			str = "SELECT * FROM Users WHERE Name = \'";
			str += uname.c_str();
			str += "\' AND Password = \'";
			str += pass.c_str();
			str += "\' AND Logged = 1";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			res = sqlite3_step(state);
			sqlite3_finalize(state);
			if (res == SQLITE_ROW)
			{
				return Auth::AlreadyLogged;
			}
			str = "UPDATE Users SET Logged = 1,IP =\'";
			str += ip.c_str();
			str += "\' WHERE Name = \'";
			str += uname.c_str();
			str += "\' AND Password = \'";
			str += pass.c_str();
			str += "\'";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			return Auth::Authenticated;
		}
		else
		{
			str = "SELECT * FROM Users WHERE Name = \'";
			str += uname.c_str();
			str += "\'";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			res = sqlite3_step(state);
			if (res == SQLITE_ROW)
				return Auth::WrongPass;

			str = "INSERT INTO Users(Name,Password,IP,Logged) VALUES(\'";
			str += uname.c_str();
			str += "\',\'";
			str += pass.c_str();
			str += "\',\'";
			str += ip.c_str();
			str += "\',1)";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			return Auth::Registered;
		}
	}

	int UpdateDB(std::string whom, std::string to, int what)
	{
		sqlite3_stmt *state;
		std::string str;
		char temp[5];
		_itoa_s(what, temp, 2, 10);
		if (to.compare("Logged") == 0)
		{
			str = "UPDATE Users SET Logged = ";
			str += temp;
			str += " WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		sqlite3_finalize(state);
		return 0;
	}

	int UpdateDB(std::string whom, std::string to, std::string what)
	{
		sqlite3_stmt *state;
		std::string str;
		if (to.compare("Name") == 0)
		{
			str = "UPDATE Users SET Name = \'";
			str += what;
			str += "\' WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		else if (to.compare("Password") == 0)
		{
			str = "UPDATE Users SET Password = \'";
			str += what;
			str += "\' WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		else if (to.compare("IP") == 0)
		{
			str = "UPDATE Users SET IP = \'";
			str += what;
			str += "\' WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		sqlite3_finalize(state);
		return 0;
	}

	int GetIntFromDB(std::string whom, std::string what)
	{
		int ret;
		sqlite3_stmt *state;
		std::string str;
		if (what.compare("Logged") == 0)
		{
			str = "SELECT Logged FROM Users WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		ret = sqlite3_column_int(state, 0);
		sqlite3_finalize(state);
		return ret;
	}

	char *GetCharFromDB(std::string whom, std::string what)
	{
		char *ret;
		sqlite3_stmt *state;
		std::string str;
		if (what.compare("Password") == 0)
		{
			str = "SELECT Password FROM Users WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		else if (what.compare("IP") == 0)
		{
			str = "SELECT IP FROM Users WHERE Name = \'";
			str += whom.c_str();
			str += "\'";
		}
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		ret = (char *)sqlite3_column_text(state, 0);
		sqlite3_finalize(state);
		return ret;
	}
};
UserDB udb;

class GroupDB
{

public:
	
	bool CreateGroupDBIfNotExists(std::string grp, std::string &owner)
	{
		grp = GetDBName(grp);

		if (!CheckGroupFileExists(grp))
		{
			sqlite3 *db;
			sqlite3_stmt *state;
			sqlite3_open(grp.c_str(), &db);
			std::string str;
			str = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(50), IsActive INT(3), AdminLevel INT(3))";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			str = "INSERT INTO Users(Name, IsActive, AdminLevel) VALUES(\'";
			str += owner;
			str += "\',1,1)";
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			sqlite3_close(db);
			return true;
		}
		grp.clear();
		return false;
	}
	
	bool AddGroupMember(std::string grp, std::string &uname)
	{
		sqlite3_stmt *state;
		std::string str;
		
		grp = GetDBName(grp);

		if (!CheckIfExistsInGrp(grp, uname))
		{
			sqlite3 *db;
			str = "INSERT INTO Users(Name, IsActive, AdminLevel) VALUES(\'";
			str += uname;
			str += "\',1,0)";
			sqlite3_open(grp.c_str(), &db);
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			sqlite3_close(db);
			return true;
		}
		return false;
	}
	
	std::vector<std::string> GetOnlineMembers(std::string grp)
	{
		sqlite3_stmt *state;

		grp = GetDBName(grp);

		std::string str, names;
		std::vector<std::string> tempnames;
		str = "SELECT * FROM Users";
		int count = 0, active;
		sqlite3 *db;
		sqlite3_open(grp.c_str(), &db);
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		res = sqlite3_step(state);
		while (res == SQLITE_ROW)
		{
			names = (char*)sqlite3_column_text(state, 1);
			active = sqlite3_column_int(state, 2);
			if (active == 1)
			{
				if (udb.GetIntFromDB(names, "Logged") == 1)
				{
					tempnames.push_back(names);
					count++;
				}
			}
			res = sqlite3_step(state);
		}
		sqlite3_finalize(state);
		sqlite3_close(db);
		if (count == 0)
			tempnames.clear();
		return tempnames;
	}
	
	bool DeleteDB(std::string file)
	{
		file = GetDBName(file);

		if (!std::remove(file.c_str()))
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}
	
	bool CheckIfExistsInGrp(std::string grp, std::string &uname)
	{
		int isactive = GetUserIntFromDB(grp, uname, std::string("IsActive"));

		return isactive;
	}
	
	bool RemoveFromGrp(std::string grp, std::string &uname)
	{
		sqlite3_stmt *state;
		std::string str;

		if (CheckIfExistsInGrp(grp, uname))
		{
			str = "UPDATE Users SET IsActive = 0, AdminLevel = 0 WHERE Name = \'";
			str += uname;
			str += "\'";
			sqlite3 *db;
			grp = GetDBName(grp);
			sqlite3_open(grp.c_str(), &db);
			sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
			sqlite3_step(state);
			sqlite3_finalize(state);
			sqlite3_close(db);
			return true;
		}
		return false;
	}

	int UpdateDB(std::string grp, std::string &uname, std::string &what, int val)
	{
		sqlite3_stmt *state;
		std::string str;
		char temp[5];
		_itoa_s(val, temp, 10);
		
		grp = GetDBName(grp);

		if (what.compare("IsActive") == 0)
		{
			str = "UPDATE Users SET IsActive = \'";
			str += temp;
			str += "\' WHERE Name = \'";
			str += uname;
			str += "\'";
		}
		else if (what.compare("AdminLevel") == 0)
		{
			str = "UPDATE Users SET AdminLevel = \'";
			str += temp;
			str += "\' WHERE Name = \'";
			str += uname;
			str += "\'";
		}
		sqlite3 *db;
		sqlite3_open(grp.c_str(), &db);
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		sqlite3_step(state);
		sqlite3_finalize(state);
		sqlite3_close(db);
		return 0;
	}

	int GetUserIntFromDB(std::string grp, std::string &uname, std::string &what)
	{
		int ret = 0;

		sqlite3_stmt *state;
		std::string str;

		int res;

		grp = GetDBName(grp);

		int col;

		if (what.compare("IsActive") == 0)
		{
			str = "SELECT * FROM Users WHERE Name = \'";
			str += uname;
			str += "\'";
			
			col = 2;
		}
		if (what.compare("AdminLevel") == 0)
		{
			str = "SELECT * FROM Users WHERE Name = \'";
			str += uname;
			str += "\'";
			
			col = 3;
		}
		sqlite3 *db;
		sqlite3_open(grp.c_str(), &db);
		sqlite3_prepare_v2(db, str.c_str(), strlen(str.c_str()), &state, NULL);
		
		res = sqlite3_step(state);
		
		if (res == SQLITE_ROW)
		{
			ret = sqlite3_column_int(state, col);
		}

		sqlite3_finalize(state);
		sqlite3_close(db);
		return ret;
	}

	bool CheckGroupFileExists(std::string &file)
	{
		if (std::ifstream(file))
		{
			return true;
		}
		else
			return false;
	}
	
	std::string GetDBName(std::string &grp)
	{
		std::string dbn;
		dbn = defaultdbdir + "Groups/" + grp + ".db";
		return dbn;
	}
};

GroupDB gdb;
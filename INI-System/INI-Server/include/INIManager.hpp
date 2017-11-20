#pragma once


class INIManager
{
	std::map<std::string, Electrux::INI_Parser*> inifiles;


public:

	//Load a file in the INI Parser.
	bool LoadFile(std::string file)
	{
		//First check if the file is already loaded in the map.
		if (IsFileLoaded(file)) return false;

		//Create a new instance of INI Parser.
		Electrux::INI_Parser *parser = new Electrux::INI_Parser;
		
		//Check if the parser can actually open the file.
		if (!parser->ParseFile(DEFAULT_DB_DIR + file + EXTENSION)) return false;
		
		//Map the file in the Files hashtable.
		inifiles[file] = parser;

		Logger::Log(MsgCode::INIMGR, "INI file: " + file + " loaded successfully.");
		
		//All good bro!
		return true;
	}

	//Update data with newval (insert if does not exist) as float with key at section from file.
	bool UpdateDataString(std::string file, std::string section, std::string key, std::string newval)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Update/Insert the new data in the file.
		inifiles[file]->SetData(section, key, newval);

		return true;
	}

	//Update data with newval (insert if does not exist) as float with key at section from file.
	bool UpdateDataInt(std::string file, std::string section, std::string key, int newval)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Update/Insert the new data in the file.
		inifiles[file]->SetData(section, key, newval);

		return true;
	}

	//Update data with newval (insert if does not exist) as float with key at section from file.
	bool UpdateDataFloat(std::string file, std::string section, std::string key, float newval)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Update/Insert the new data in the file.
		inifiles[file]->SetData(section, key, newval);

		return true;
	}

	//Delete the given key at section from file.
	bool DeleteData(std::string file, std::string section, std::string key)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Delete the data and return true if it was successful. Else return false.
		return inifiles[file]->DeleteData(section, key);
	}

	//Get the date as string as defined in parameters from the file at section with key.
	std::string GetDataString(std::string file, std::string section, std::string key)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Fetch the data from the file.
		return inifiles[file]->GetDataString(section, key);
	}

	//Get the date as int as defined in parameters from the file at section with key.
	int GetDataInt(std::string file, std::string section, std::string key)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Fetch the data from the file.
		return inifiles[file]->GetDataInt(section, key);
	}

	//Get the date as float as defined in parameters from the file at section with key.
	float GetDataFloat(std::string file, std::string section, std::string key)
	{
		if (!IsFileLoaded(file)) this->LoadFile(file);

		//Fetch the data from the file.
		return inifiles[file]->GetDataFloat(section, key);
	}

	//Saves the file given in parameter.
	int SaveFile(std::string file)
	{
		if (!IsFileLoaded(file)) return -1;

		//Save the file in default location and filename. Returns true if file was saved, false if there was no content to save or file could not be opened.
		return inifiles[file]->SaveFile(DEFAULT_DB_DIR + file + EXTENSION);
	}

	//Closes the open file given in parameter and deallocates the respective pointer. Does NOT save it!!!
	bool CloseFile(std::string file)
	{
		if (file.empty()) return false;

		if (!IsFileLoaded(file)) return false;

		//Deallocate the pointer.
		delete inifiles[file];
		
		//Find the location iterator of the file in the map and erase it.
		inifiles.erase(inifiles.find(file));

		Logger::Log(MsgCode::INIMGR, "File: " + file + " closed.");

		return true;
	}

	//Checks in the map if the file name already exists (therefore, already loaded).
	bool IsFileLoaded(std::string file)
	{
		for (auto files : inifiles)
		{
			if (files.first == file)
			{
				return true;
			}
		}

		return false;
	}

	//Clears everything. Similar to the destructor except this can be called at will.
	void CloseAll()
	{
		for (auto files : inifiles)
		{
			//Deallocate the pointer and free the memory.
			delete inifiles[files.first];
		}

		//Clear the map.
		inifiles.clear();
	}

	//Saves everything in every file.
	void SaveAll()
	{
		Logger::Log(MsgCode::INIMGR, "Saving all files...");

		//Count how many files are saved.
		int count = 0;

		for (auto files : inifiles)
		{
			//Save the file in default location and filename.
			files.second->SaveFile(DEFAULT_DB_DIR + files.first + EXTENSION);

			count++;
		}

		Logger::Log(MsgCode::INIMGR, "Saved " + std::to_string(count) + " files.");
	}

	//Destructor for INI Manager. Clears all the pointers and deallocates memory.
	~INIManager()
	{
		Logger::Log(MsgCode::INIMGR, "Closing all databases and clearing the memory...");

		this->CloseAll();

		Logger::Log(MsgCode::INIMGR, "Closed all databases and cleared the memory.");
	}

};
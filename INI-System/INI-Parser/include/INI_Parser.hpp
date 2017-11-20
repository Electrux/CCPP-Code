#pragma once

#include "DataManager.hpp"

//Uses DataManager for memory data mapping. Adds to that a file read and write mechanism to work with the files.
namespace Electrux
{
	class INI_Parser
	{
		std::fstream file;
		DataManager datamgr;

		std::string FetchStringBetween(std::string::iterator &it_start, std::string::iterator &it_end)
		{
			std::string temp;

			for (auto it = it_start + 1; it != it_end; ++it)
			{
				temp += *it;
			}

			return temp;
		}

		std::string GetSectionFromLine(std::string &line)
		{
			std::string temp;

			if (*line.begin() == '[' && *(line.end() - 1) == ']')
			{
				temp = this->FetchStringBetween(line.begin(), line.end() - 1);
			}
			else return temp; // This line is not a section!!

			if (temp.empty()) temp = "NOSECTION"; //This section has no name!!

			return temp;
		}

		bool ParseKeyValFromLine(std::string &line, std::string &key, std::string &val)
		{
			if (line.find('=') == std::string::npos) return false;

			key.clear();
			val.clear();

			bool equalfound = false;

			for (auto it = line.begin(); it != line.end(); ++it)
			{
				if (*it == '=')
				{
					equalfound = true;
					continue;
				}

				if (equalfound == false)
					key += *it;
				else
					val += *it;
			}

			return true;
		}

	public:

		bool ParseFile(std::string file)
		{
			this->file.open(file, std::ios::in);

			if (!this->file.is_open()) return false;

			std::string line, tempsection, section, key, val;

			bool sec_found = false, no_sec = true;

			while (std::getline(this->file, line))
			{
				if (line.empty()) continue;

				tempsection = this->GetSectionFromLine(line);

				if (!tempsection.empty())
				{
					if (tempsection == "NOSECTION")
					{
						no_sec = true;
					}
					else
					{
						no_sec = false;
						section = tempsection;
					}

					sec_found = true;
				}

				if (sec_found == true && no_sec == false)
				{
					if (this->ParseKeyValFromLine(line, key, val))
					{
						datamgr.AddData(section, key, val);
					}
				}

			}

			this->file.close();

			return true;
		}

		void SetData(std::string sec, std::string key, std::string val)
		{
			this->datamgr.AddData(sec, key, val);
		}

		void SetData(std::string sec, std::string key, int val)
		{
			this->datamgr.AddData(sec, key, val);
		}

		void SetData(std::string sec, std::string key, float val)
		{
			this->datamgr.AddData(sec, key, val);
		}

		std::string GetDataString(std::string sec, std::string key)
		{
			this->datamgr.GetDataString(sec, key);
		}

		int GetDataInt(std::string sec, std::string key)
		{
			this->datamgr.GetDataInt(sec, key);
		}

		float GetDataFloat(std::string sec, std::string key)
		{
			this->datamgr.GetDataFloat(sec, key);
		}

		bool DeleteSection(std::string sec)
		{
			return this->datamgr.DeleteSection(sec);
		}

		bool DeleteData(std::string sec, std::string key)
		{
			return this->datamgr.DeleteData(sec, key);
		}

		bool SaveFile(std::string file)
		{
			this->file.open(file, std::ios::out);

			if (!this->file.is_open()) return false;

			auto sections = datamgr.GetStart();

			if (sections == nullptr)
			{
				this->file.close();
				return false;
			}

			std::string line;

			while (sections != nullptr)
			{
				this->file << "[" << sections->GetSection() << "]\n\n";

				auto data = sections->GetAllData();

				for (auto it = data.begin(); it != data.end(); ++it)
				{
					this->file << it->first << "=" << it->second << "\n";
				}

				this->file << "\n\n";

				sections = sections->GetNext();
			}

			this->file.close();

			return true;
		}

		bool DisplayAll()
		{
			auto sections = datamgr.GetStart();

			if (sections == nullptr) return false;

			while (sections != nullptr)
			{
				std::cout << "[" << sections->GetSection() << "]\n\n";

				auto data = sections->GetAllData();

				for (auto it = data.begin(); it != data.end(); ++it)
				{
					std::cout << "\t" << it->first << "=" << it->second << "\n";
				}

				std::cout << "\n\n";

				sections = sections->GetNext();
			}
			return true;

		}

	};
}
#pragma once

//Manages each section and holds its data. (Next and Previous pointers used to point to next and previous sections.
namespace Electrux
{
	class SectionData
{
	std::string section;
	std::map<std::string, std::string> data;

	SectionData *prev, *next;

public:

	SectionData()
	{
		this->prev = this->next = nullptr;
	}

	~SectionData()
	{
		this->section.clear();
		this->data.clear();
	}

	void SetSection(std::string sec)
	{
		this->section = sec;
	}

	std::string GetSection()
	{
		return this->section;
	}

	void InsertData(std::string key, std::string val)
	{
		data[key] = val;
	}

	bool DeleteData(std::string key)
	{
		if (data.find(key) == data.end()) return false;

		data.erase(key);

		return true;
	}

	std::string GetData(std::string key)
	{
		std::string temp;

		if (data.find(key) == data.end()) return temp;

		return data[key];
	}

	void Clear()
	{
		section.clear();
		data.clear();
	}

	void SetNext(SectionData *dat)
	{
		if (dat != nullptr)
		{
			dat->prev = this;
		}

		this->next = dat;
	}

	void SetPrev(SectionData *dat)
	{
		if (dat != nullptr)
		{
			dat->next = this;
		}

		this->prev = dat;
	}

	std::map<std::string, std::string> &GetAllData()
	{
		return data;
	}

	SectionData *GetPrev()
	{
		return prev;
	}

	SectionData *GetNext()
	{
		return next;
	}

};
}
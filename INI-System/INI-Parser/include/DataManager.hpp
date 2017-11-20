#pragma once

#include "SectionData.hpp"

//Manages the lists of Sections and their data. Controls the Insertion/Modification/Deletion from all the Sections.
namespace Electrux
{
	class DataManager
	{
		SectionData *start, *end;
		int seccount;

	public:

		DataManager()
		{
			this->start = this->end = nullptr;
			this->seccount = 0;
		}

		~DataManager()
		{
			SectionData *it = this->start;

			while (it->GetNext() != nullptr)
			{
				SectionData *temp = it;

				it = it->GetNext();

				delete temp;
			}

			if (this->end != nullptr)
				delete this->end;

			this->start = this->end = nullptr;
		}

		SectionData* AddSection(std::string sec) //Returns a new section if it does not exist... else returns the already existing one with same name.
		{
			if (this->start == nullptr)
			{
				this->start = this->end = new SectionData;

				this->end->SetSection(sec);

				this->seccount++;
			}
			else
			{
				auto it = this->GetSection(sec);

				if (it != nullptr) return it;

				this->end->SetNext(new SectionData); //RValue
				this->end->GetNext()->SetPrev(this->end);
				this->end = this->end->GetNext();

				this->end->SetSection(sec);

				this->seccount++;

			}
			return this->end;
		}

		SectionData *GetSection(std::string sec)
		{
			auto it = start;

			while (it != nullptr)
			{
				if (it->GetSection() == sec) //Section exists!
					return it;

				it = it->GetNext();
			}

			return nullptr;
		}

		bool DeleteSection(std::string sec)
		{
			if (this->start == nullptr) return false;

			bool found = false;

			if (this->start->GetSection() == sec)
			{
				auto deleter = this->start;

				this->start = this->start->GetNext();
				this->start->SetPrev(nullptr);

				delete deleter;

				this->seccount--;

				found = true;
			}
			else if (this->end->GetSection() == sec)
			{
				auto deleter = this->end;

				this->end = this->end->GetPrev();
				this->end->SetNext(nullptr);

				delete deleter;

				this->seccount--;

				found = true;
			}
			else
			{
				auto it = this->start;
				while (it != nullptr)
				{
					if (it->GetSection() == sec)
					{
						it->GetPrev()->SetNext(it->GetNext());
						it->GetNext()->SetPrev(it->GetPrev());

						delete it;

						this->seccount--;

						found = true;

						break;
					}

					it = it->GetNext();
				}
			}
			return found;
		}

		void AddData(std::string sec, std::string key, std::string val)
		{
			auto section = this->AddSection(sec);

			section->InsertData(key, val);
		}

		void AddData(std::string sec, std::string key, int val)
		{
			auto section = this->AddSection(sec);

			section->InsertData(key, std::to_string(val));
		}

		void AddData(std::string sec, std::string key, float val)
		{
			auto section = this->AddSection(sec);

			section->InsertData(key, std::to_string(val));
		}

		bool DeleteData(std::string sec, std::string key)
		{
			auto section = this->GetSection(sec);

			if (section == nullptr) return false;

			return section->DeleteData(key);
		}

		std::string GetDataString(std::string sec, std::string key)
		{
			std::string temp;

			auto section = this->GetSection(sec);

			if (section == nullptr) return temp;

			return section->GetData(key);
		}

		int GetDataInt(std::string sec, std::string key)
		{
			std::string temp;

			auto section = this->GetSection(sec);

			if (section == nullptr) return INT_MIN;

			temp = section->GetData(key);

			if (temp.empty()) return INT_MIN;

			return std::stoi(temp);
		}

		float GetDataFloat(std::string sec, std::string key)
		{
			std::string temp;

			auto section = this->GetSection(sec);

			if (section == nullptr) return FLT_MIN;

			temp = section->GetData(key);

			if (temp.empty()) return FLT_MIN;

			return std::stof(temp);
		}

		void Clear()
		{
			SectionData *it = this->start;

			while (it->GetNext() != nullptr)
			{
				SectionData *temp = it;

				it = it->GetNext();

				delete temp;
			}

			if (this->end != nullptr)
				delete this->end;

			this->start = this->end = nullptr;
		}

		SectionData *GetStart()
		{
			return this->start;
		}

		SectionData *GenerateNewSectionData()
		{
			SectionData *temp = new SectionData;
			return temp;
		}

		int GetSectionCount()
		{
			return seccount;
		}

	};
}
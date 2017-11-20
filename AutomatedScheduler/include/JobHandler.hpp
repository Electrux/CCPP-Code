#ifdef _WIN32

#ifndef JOB_HANDLER_HPP
#define JOB_HANDLER_HPP

#include <vector>
#include <string>
#include <Windows.h>

#include "Data.hpp"
#include "ExecProcess.hpp"

class JobHandler
{
	std::vector<Job> jobs;
	std::vector<std::vector<Job>::iterator> toremove;

public:

	JobHandler()
	{
		jobs.clear();
	}

	void Enter(std::string _name, std::string _file, int _time)
	{
		Job temp;
		temp.taskname = _name;
		temp.file = _file;
		temp.exec_time.setTime(_time);
		jobs.push_back(temp);
	}

	std::vector<std::string> Display()
	{
		std::vector<std::string> tosend;
		std::string temp;
		if (!jobs.empty())
		{
			for (auto it = jobs.begin(); it != jobs.end(); ++it)
			{
				temp = it->taskname + "					" + it->file + "				" + it->exec_time.getFormattedDT();
				tosend.push_back(temp);
			}
		}
		else jobs.clear();
		return tosend;
	}

	std::string GetCount()
	{
		int i = 0;
		char temp[5];
		for (auto it = jobs.begin(); it != jobs.end(); ++it)
		{
			i++;
		}
		_itoa_s(i, temp, 10);
		return std::string(temp);
	}

	std::vector<std::string> Execute(Electrux::SlicedTime &time)
	{
		std::vector<std::string> temp;
		temp.clear();
		if (!jobs.empty())
		{
			for (auto it = jobs.begin(); it != jobs.end(); ++it)
			{
				if (it->exec_time.getDateTime(Electrux::SlicedTime::Data::HOURS) == time.getDateTime(Electrux::SlicedTime::Data::HOURS)
				    && it->exec_time.getDateTime(Electrux::SlicedTime::Data::MINUTES) == time.getDateTime(Electrux::SlicedTime::Data::MINUTES))
				{
					temp.push_back("Executing: " + it->taskname);
					ExecuteProcess(it->file);
					toremove.push_back(it);
				}
			}
		}
		RemoveFromList();
		return temp;
	}
	
	void RemoveFromList()
	{
		if (!toremove.empty())
		{
			for (auto it = toremove.rbegin(); it != toremove.rend(); ++it) //From rear becoz if front, the first one gets removed and all others get shifted forward thereby deprecating the
			{							       //iterator index from before
				jobs.erase(*it);
			}
		}
		toremove.clear();
	}
};

#endif // JOB_HANDLER_HPP

#endif // _WIN32

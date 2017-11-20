#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "TextHandler.hpp"
#include "JobHandler.hpp"
#include "SlicedTime.hpp"

class AutoSchedulerEngine
{
	sf::RenderWindow window;
	TextHandler alltext;
	sf::Event event;
	std::vector<std::string> poll_temp_all_text;
	JobHandler jobpool;
	Electrux::SlicedTime currtime, prevtime;
	enum CMDTYPE
	{
		NEW,
		SHOW
	};
public:
	void Initialize(sf::VideoMode vm, std::string name)
	{
		window.create(vm, name);
		currtime.setTime(Electrux::SlicedTime::getCurrentRawTime());
		prevtime.setTime(Electrux::SlicedTime::getCurrentRawTime());
		poll_temp_all_text.clear();
	}
	
	void SetFrameRate(int fr)
	{
		window.setFramerateLimit(fr);
	}
	
	void PollEvent();

	bool isRunning()
	{
		return window.isOpen();
	}

	void Clear()
	{
		window.clear();
	}

	void UpdateTimeAndExecute()
	{
		currtime.setTime(Electrux::SlicedTime::getCurrentRawTime());
		alltext.UpdateTime(currtime.getFormattedDT());
		if (currtime.getDateTime(Electrux::SlicedTime::Data::MINUTES) > prevtime.getDateTime(Electrux::SlicedTime::Data::MINUTES)
		    || currtime.getDateTime(Electrux::SlicedTime::Data::MINUTES) == 0)
		{
			std::vector<std::string> exec;
			exec = jobpool.Execute(currtime);
			if (!exec.empty())
			{
				for (auto it = exec.begin(); it != exec.end(); ++it)
					alltext.AddText(*it);
			}
			currtime.setTime(Electrux::SlicedTime::getCurrentRawTime());
			prevtime.setTime(Electrux::SlicedTime::getCurrentRawTime());
		}
	}
	
	void Close()
	{
		window.close();
	}

	void Draw()
	{
		window.draw(alltext);
	}

	void EnterText(std::string &text)
	{
		alltext.AddText(text);
	}

	void Display()
	{
		window.display();
	}

	void HandleJobInput(int type)
	{
		std::string temp;
		if (type == CMDTYPE::NEW)
		{
			int time;
			time = atoi(poll_temp_all_text[3].c_str());
			if (!fexists(poll_temp_all_text[2]))
			{
				alltext.AddText(std::string("ERROR: Entered file does not exist! Please verify the integrity of the file!"));
			}
			else if (time > 2459 || time < 0)
			{
				alltext.AddText(std::string("ERROR: Invalid time specified! Use a time between 0 to 2459 (HHMM)!"));
			}
			else
			{
				alltext.AddText(std::string("Gotcha!"));
				jobpool.Enter(poll_temp_all_text[1], poll_temp_all_text[2], time);
			}
			poll_temp_all_text.clear();
		}
		else if (type == CMDTYPE::SHOW)
		{
			std::vector<std::string> rows;
			if ((rows = jobpool.Display()).empty())
			{
				alltext.AddText(std::string("ERROR: No job is given!"));
			}
			else
			{
				alltext.AddText(std::string("----------------------JOBS----------------------"));
				alltext.AddText(std::string("Name of Program				File Location				Time of Execution"));
				for (auto it = rows.begin(); it != rows.end(); ++it)
				{
					alltext.AddText(*it);
				}
			}
		}
	}

	void UpdateCount()
	{
		alltext.UpdateCount(jobpool.GetCount());
	}
};

#endif // ENGINE_HPP

#ifndef POLL_EVENT_HPP
#define POLL_EVENT_HPP

#include "Engine.hpp"

void AutoSchedulerEngine::PollEvent()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Return)
			{
				if (!alltext.GetTyped().empty())
				{
					poll_temp_all_text.clear();
					if (alltext.GetTyped().find("new") != std::string::npos)
					{
						if (alltext.getDelimitedStrings(alltext.GetTyped(), &poll_temp_all_text, 4))
						{
							HandleJobInput(CMDTYPE::NEW);
						}
						else
						{
							alltext.AddText(std::string("ERROR: Syntax: new <taskname> <task location> <task execution time>"));
						}
					}
					else if (alltext.GetTyped().find("show") != std::string::npos)
					{
						HandleJobInput(CMDTYPE::SHOW);
					}
					alltext.ClearTyped();
				}
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128 && (static_cast<char>(event.text.unicode) != '\r') && (static_cast<char>(event.text.unicode) != '/') && (event.text.unicode != 27)/*BackSpace*/)
			{
				alltext.UpdateTypeWhat(static_cast<char>(event.text.unicode));
			}
		}
	}
}

#endif // POLL_EVENT_HPP

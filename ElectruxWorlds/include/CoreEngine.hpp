#pragma once

class Engine
{
	sf::RenderWindow window;
	sf::Event event;
	tgui::Gui gui;

	MapEngine maps;

public:

	sf::RenderWindow * getwindow()
	{
		return &window;
	}

	sf::Event * getevent()
	{
		return &event;
	}

	tgui::Gui * getgui()
	{
		return &gui;
	}
	
	MapEngine * getmap()
	{
		return &maps;
	}

	//Connect SFML and TGUI
	void connectsfmltgui()
	{
		gui.setWindow(window);
	}

	//Widgets of main menu to be shown.
	bool initmainmenudata()
	{
		try
		{
			//Load main menu.
			Menus::loadmainui(gui);
		}
		catch (const tgui::Exception &e)
		{
			window.close();
			std::cerr << "Could not generate main menu: " << e.what() << "!\n";
			std::system("pause");
			return false;
		}

		return true;
	}

	//Widgets of in game to be shown.
	bool initingamedata()
	{
		try
		{
			//Load main menu.
			Menus::loadgameui(gui);
		}
		catch (const tgui::Exception &e)
		{
			window.close();
			std::cerr << "Could not generate game ui: " << e.what() << "!\n";
			std::system("pause");
			return false;
		}

		return true;
	}

	//Widgets of settings menu to be shown.
	bool initsettingsmenudata()
	{
		try
		{
			//Load main menu.
			Menus::loadsettingsui(gui);
		}
		catch (const tgui::Exception &e)
		{
			window.close();
			std::cerr << "Could not generate settings menu: " << e.what() << "!\n";
			std::system("pause");
			return false;
		}

		return true;
	}

	//The main menu which is shown.
	void runmainmenuloop()
	{
		this->pollevent();
		window.clear();
		gui.draw();
		window.display();
		
	}

	//The settings menu which is shown.
	void runsettingsmenuloop()
	{
		this->pollevent();
		window.clear();
		gui.draw();
		window.display();

	}
	
	//The actual game which is shown.
	void rungameloop(Player &player)
	{
		this->pollevent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.move(0, -SKIP);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player.move(-SKIP, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.move(0, +SKIP);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.move(SKIP, 0);

		player.setlookingangle(this->getmousecoords());

		window.clear();
		window.draw(maps);
		window.draw(player);
		gui.draw();
		window.display();
	}

	//Handle all the inputs and events.
	void pollevent()
	{
		while (window.pollEvent(event))
		{
			//Close the window if event received is of close.
			if (event.type == sf::Event::Closed) window.close();

			//If any key release is encountered, handle it.
			if (event.type == sf::Event::KeyReleased)
			{
				//Handle escape key to close the window.
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (loggedin)
					{
						if (settingsmenu)
							settingsmenu = false;
						else
						{
							loggedin = false;
							mainmenu = true;
						}
					}
					else
						window.close();
				}
			}

			//Handle key presses.
			/*if (event.type == sf::Event::KeyPressed)
			{
			}*/
			gui.handleEvent(event);
		}
	}

	//Get converted pixel mouse coordinates from window.
	sf::Vector2f getmousecoords()
	{
		return window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

};
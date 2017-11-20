#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "../../INI_Parser/include/INI_Parser.hpp"

//Includes Window.hpp
#include <SFML/Graphics.hpp>

//Includes System.hpp
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>


//Custom Includes
#include "../include/Data.hpp"
#include "../include/Tileset.hpp"
#include "../include/Layer.hpp"
#include "../include/MapEngine.hpp"
#include "../include/AnimatedEntity.hpp"
#include "../include/Actor.hpp"
#include "../include/Player.hpp"
#include "../include/Functions.hpp"
#include "../include/Menus.hpp"
#include "../include/CoreEngine.hpp"

//Load the SFML & TGUI libraries.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "tgui-d.lib")

int main()
{
	Engine engine;
	
	//Set the core font(s).
	initdefaults();
	
	//Initialize the window.
	engine.getwindow()->create(sf::VideoMode(width, height), "Electrux Worlds");
	engine.getwindow()->setFramerateLimit(MAXFRAMERATE);

	//Connect TGUI and SFML.
	engine.connectsfmltgui();

	//Initialize the TGUI main menu items.
	if (!engine.initmainmenudata()) return 1;

	//Create a player.
	Player *player;

	//Done with the main menu. Now lets get in the game!
	while (engine.getwindow()->isOpen())
	{
		if (mainmenu)
		{
			if (!loadedmainmenu)
			{
				engine.initmainmenudata();
				loadedmainmenu = true;
			}
			engine.runmainmenuloop();
		}
		if (!mainmenu && loadedmainmenu)
		{
			engine.getgui()->removeAllWidgets();
			loadedmainmenu = false;
		}

		if (loggedin)
		{
			if (!loadedloggedin)
			{
				engine.initingamedata();
				
				engine.getmap()->loadmap("Assets/Maps/Level1/Level1.tmx");

				player = new Player;
				player->setname(uname);
				player->setpos(width / 2, height / 2);
				
				loadedloggedin = true;
			}
			engine.rungameloop(*player);
		}
		if (!loggedin && loadedloggedin)
		{
			engine.getgui()->removeAllWidgets();
			delete player;

			loadedloggedin = false;
		}

		if (settingsmenu)
		{
			if (!loadedsettingsmenu)
			{
				engine.initsettingsmenudata();
				loadedsettingsmenu = true;
			}
			engine.runsettingsmenuloop();
		}
		if (!settingsmenu && loadedsettingsmenu)
		{
			engine.getgui()->removeAllWidgets();
			loadedsettingsmenu = false;
		}
	}

	return 0;
}

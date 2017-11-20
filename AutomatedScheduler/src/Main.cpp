#include <iostream>
#include <cstdlib>

#ifdef _WIN32

#include <Windows.h>
#include <tchar.h>

#endif // _WIN32

#include <ctime>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "../include/ExecProcess.hpp"
#include "../include/SlicedTime.hpp"
#include "../include/Data.hpp"
#include "../include/JobHandler.hpp"
#include "../include/TextHandler.hpp"
#include "../include/Engine.hpp"
#include "../include/PollEvent.hpp"

//Since I'm not using multibyte in execprocess string to wstring, it will fail if i put a multibyte char string for process

int main()
{
	system("cls");
	font.loadFromFile("arial.ttf");
	AutoSchedulerEngine Engine;
	Engine.Initialize(sf::VideoMode(800, 600), std::string("AutoScheduler"));
	Engine.SetFrameRate(60);
	int frame = 0;
	while (Engine.isRunning())
	{
		Engine.PollEvent();
		Engine.Clear();
		Engine.UpdateCount();
		if (frame == 60)
		{
			Engine.UpdateTimeAndExecute();
			frame = 0;

		}
		Engine.Draw();
		Engine.Display();
		++frame;
	}
	return 0;
}

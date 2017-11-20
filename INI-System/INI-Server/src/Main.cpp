#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <queue>
#include <map>
#include <mutex>
#include <INI_Parser.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Enums.hpp"
#include "Data.hpp"
#include "Logger.hpp"
#include "User.hpp"
#include "Funktions.hpp"
#include "INIManager.hpp"
#include "Networker.hpp"

//Load the SFML network and system libraries.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-network-d.lib")


int main()
{

	//The manager of all threads... All hail the thread pool!!
	std::vector<std::thread> threads;

	//The manager of all the databases... All hail INI Manager!!
	INIManager inimgr;

	//Store the input code received from HandleConsoleInput
	ConsoleInputCodes inputcode;

	Logger::Log(MsgCode::SERVER, "Starting the network manager...");

	//Let the network begin! Requires address to threads for its own selfish self.
	NetworkManager network(&threads, &inimgr);

	Logger::Log(MsgCode::SERVER, "Started the network manager.");

	//Start the console input function and therefore thread.
	threads.push_back(std::thread(ConsoleInput));

	Logger::Log(MsgCode::SERVER, "Initialization completed.");
	Logger::Log(MsgCode::SERVER, "Ready to accept connections!\n");

	//The server will run forever!! Mwahahahhaha!!!!!
	while (true)
	{
		//Check for console inputs.
		inputcode = HandleConsoleInput();
		//If the input is to exit, break this loop.
		if (inputcode == ConsoleInputCodes::EXIT)
		{
			Logger::Log(MsgCode::SERVER, "Exit code received. Now exiting...");
			break;
		}
		else if (inputcode == ConsoleInputCodes::SAVEALL)
		{
			Logger::Log(MsgCode::SERVER, "Received console input for save all. Saving everything...");
			inimgr.SaveAll();
		}

		//Execute the network core function.
		network.Execute();

	}

	//Stop all threads by joining them to main thread.
	StopAllThreads(threads);

	//See you again bro! Buh-Bye.
	return 0;
}
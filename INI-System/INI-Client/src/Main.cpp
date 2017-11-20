#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "INI_Connector.hpp"


//Load the SFML network and system libraries.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-network-d.lib")

int main()
{

	sf::TcpSocket socket;

	INI_Connector inidb;

	std::cout << "Enter username and filename:\n";

	std::string username, db;

	std::cin >> username >> db;

	if (!inidb.InitNetwork(username))
	{
		std::system("pause");
		return 0;
	}

	if (!inidb.ConnectDB(db))
	{
		std::system("pause");
		return 0;
	}

	std::cout << inidb.FetchInt("Display", "FullscreenHeight") << "\n";

	inidb.InsertString("Display", "test", "test2");

	inidb.FinalizeDatabase();

	inidb.DeleteData("Display", "test");

	inidb.FinalizeDatabase();

	inidb.FetchString("Display", "test");

	std::system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <list>
#include <functional>
#include <sqlite3.h>
#include <fstream>
#include <thread>
#include <mutex>

#include "../include/Enums.hpp"
#include "../include/Data.hpp"
#include "../include/Users.hpp"
#include "../include/Database.hpp"
#include "../include/Functions.hpp"
#include "../include/Remover.hpp"

//Load the SFML network and system libraries and the SQLite library.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "SQLite3.lib")

int main()
{
	res = udb.Open();
	if (res != SQLITE_OK)
	{
		std::cout << "ERROR! " << std::endl;
		std::cout << "Could not open DataBase! Exiting!!";
		udb.Close();
		return 0;
	}

	udb.CheckDB();
	udb.SetAllOffline();
	
	sf::TcpListener listener;
	listener.setBlocking(false);
	listener.listen(8080);
	
	sf::Packet packet;
	RemoveHandler remover;

	std::vector<std::thread> threads;

	std::cout << "\nAuthentication server ready to accept connections.";

	while (true)
	{
			
		Users* client = new Users;
		if (listener.accept(*client) == sf::Socket::Done)
		{
			packet.clear();
			threads.push_back(std::thread(AddClientToList, client));
		}
		else
		{
			delete client;
		}

		for (std::list<Users*>::iterator receivefrom = clients.begin(); receivefrom != clients.end(); ++receivefrom)
		{
			Users& client = **receivefrom;
			packet.clear();
			if (client.receive(packet) == sf::Socket::Disconnected)
			{
				remover.AddToRemove(&client);
				continue;
			}
		}
		remover.UpdateList();
	}
	for (auto it = threads.begin(); it != threads.end(); ++it)
	{
		it->join();
	}
	return 0;
}

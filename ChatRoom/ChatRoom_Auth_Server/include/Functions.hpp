#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <list>
#include <SFML/Network.hpp>

#include "Users.hpp"
#include "Functions.hpp"
#include "Database.hpp"

std::list<Users *> clients;

int NameExists(std::string name)
{
	for (std::list<Users*>::iterator tocheck = clients.begin(); tocheck != clients.end(); ++tocheck)
	{
		Users& client = **tocheck;
		if (client.GetName() == name)
			return 1;
	}
	return 0;
}

void SendNameOk(Users *sock)
{
	sf::Packet pack;
	int res;
	pack << 1;
	do
	{
		res = sock->send(pack);
	} while (res != sf::Socket::Done);
	std::cout << "Done!\n";
}

void SendNameNotOk(Users *sock)
{
	sf::Packet pack;
	int res;
	pack << 0;
	do
	{
		res = sock->send(pack);
	} while (res != sf::Socket::Done);
	std::cout << "Done!\n";
}

void AddClientToList(Users *sock)
{
	sf::Packet pack;
	std::string name, pass, ip;
	int res;
	pack.clear();
	do
	{
		res = sock->receive(pack);
	} while (res != sf::Socket::Done);
	pack >> name >> pass >> ip;
	std::cout << "\nClient connected with name: " << name << " Pass: " << pass << " IP: " << ip << "!!";
	pack.clear();
	int sres = udb.CheckIfExists(name, pass, ip);
	pack << sres;
	do
	{
		res = sock->send(pack);
	} while (res != sf::Socket::Done);
	pack.clear();
	sock->setBlocking(false);
	while (true)
	{
		if (clientslock.try_lock())
			break;
	}
	if (sres != 2)
	{
		sock->Enter(name);
		clients.push_back(sock);
	}
	clientslock.unlock();
}

void SendRecvData(sf::Packet pack)
{
	for (std::list<Users*>::iterator receivefrom2 = clients.begin(); receivefrom2 != clients.end(); ++receivefrom2)
	{
		Users& client2 = **receivefrom2;
		client2.send(pack);
	}
	pack.clear();
}

void SendRecvDataToUser(Users *sock, sf::Packet pack)
{
	sock->send(pack);
	pack.clear();
}

#endif // FUNCTIONS_HPP

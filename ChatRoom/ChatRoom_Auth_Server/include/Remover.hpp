#ifndef REMOVER_HPP
#define REMOVER_HPP

#include <iostream>
#include <list>

#include "Users.hpp"
#include "Data.hpp"
#include "Functions.hpp"

class RemoveHandler
{
	std::list<Users *> torem;
	
public:

	void AddToRemove(Users *client)
	{
		torem.push_back(client);
	}
	
	void UpdateList()
	{
		while (true) {
			if (clientslock.try_lock())
				break;
		}

		for (std::list<Users*>::iterator rem = torem.begin(); rem != torem.end(); ++rem) {
			Users& client = **rem;
			std::cout << "\nRemoved: " << client.GetName();
			clients.remove(&client);
		}

		clientslock.unlock();
		torem.clear();
	}
};

#endif // REMOVER_HPP

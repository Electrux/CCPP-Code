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
		while (true)
		{
			if (clientslock.try_lock())
				break;
		}
		for (std::list<Users*>::iterator rem = torem.begin(); rem != torem.end(); ++rem)
		{
			Users& client = **rem;
			udb.UpdateDB(client.GetName(), "Logged", 0);
			std::cout << "\nRemoved: " << client.GetName();
			clients.remove(&client);
		}
		clientslock.unlock();
		torem.clear();
	}
};
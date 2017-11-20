std::list<Users *> clients;


bool SendMsgToUser(std::string &name, sf::Packet pack)
{
	int count = 0;
	for (auto it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetName() == name)
		{
			while (true)
			{
				if ((*it)->send(pack) == sf::Socket::Done)
				{
					break;
				}
				else if (count > 1000)
				{
					return false;
				}
				count++;
			}
			return true;
		}
	}
	return false;
}

bool countalive = true;
void CountUsers()
{
	while (countalive)
	{
		int count = 0;
		Sleep(5000);
		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			count++;
		}
		sf::Packet pack;
		pack << MSG_TYPE::Count << count;
		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			(*it)->send(pack);
		}
	}
}

void SendMsgToAll(sf::Packet pack)
{
	for (auto receivefrom2 = clients.begin(); receivefrom2 != clients.end(); ++receivefrom2)
	{
		Users& client2 = **receivefrom2;
		SendMsgToUser(client2.GetName(), pack);
	}
	pack.clear();
}

Users *GetSocketFromName(std::string &name)
{
	for (auto it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetName() == name)
		{
			return *it;
		}
	}
	return NULL;
}

void SendMsgToGroup(std::string gname, sf::Packet &packet)
{
	std::vector<std::string> grpmembs;
	grpmembs = gdb.GetOnlineMembers(gname);
	if (!grpmembs.empty())
	{
		for (auto it = grpmembs.begin(); it != grpmembs.end(); ++it)
		{
			SendMsgToUser(*it, packet);
		}
	}
}

void CLI()
{
	char tempstr[100];
	std::cout << "\nCommand > ";
	while (countalive)
	{
		fgets(tempstr, sizeof(tempstr), stdin);
	}
}

void SendDeleteMsgToGroup(std::string &gname, std::string &uname)
{
	std::vector<std::string> grpmembs;
	grpmembs = gdb.GetOnlineMembers(gname);
	std::string fmsg;
	sf::Packet packet;
	if (!gdb.DeleteDB(gname))
	{
		fmsg = "[SERVER]: Group " + gname + " could not be deleted.";
		packet << MSG_TYPE::System << fmsg;
		for (auto it = grpmembs.begin(); it != grpmembs.end(); ++it)
		{
			if ((*it) == uname)
			{
				SendMsgToUser(*it, packet);
			}
		}
	}
	else
	{
		fmsg = "[SERVER]: Group " + gname + " is now deleted by " + uname + ".";
		packet << MSG_TYPE::System << fmsg;
		std::cout << "\nHere.";
		if (!grpmembs.empty())
		{
			for (auto it = grpmembs.begin(); it != grpmembs.end(); ++it)
			{
				SendMsgToUser(*it, packet);
			}
		}
	}
}


void AddClientToList(Users *sock)
{
	sf::Packet pack;
	std::string name;
	int res, type;
	pack.clear();
	do
	{
		res = sock->receive(pack);
	} while (res != sf::Socket::Done);
	pack >> type >> name;
	pack.clear();
	udb.UpdateDB(name, "Logged", 1);
	sock->Enter(name);
	sock->setBlocking(false);
	while (true)
	{
		if (clientslock.try_lock())
			break;
	}
	clients.push_back(sock);
	clientslock.unlock();
	std::cout << "Client connected with name: " << name << "!!\n";
}

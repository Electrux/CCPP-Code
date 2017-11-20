#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <list>
#include <functional>
#include <sqlite3.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include "Enums.hpp"
#include "Data.hpp"
#include "Users.hpp"
#include "Database.hpp"
#include "Functions.hpp"
#include "Remover.hpp"

//Load the SFML network and system libraries and the SQLite library.
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "SQLite3.lib")


int main()
{
	std::vector<std::thread> threads;
	res = udb.Open();
	if (res != SQLITE_OK)
	{
		std::cout << "ERROR! " << std::endl;
		std::cout << "Could not open DataBase! Exiting!!";
		udb.Close();
		return 0;
	}
	udb.CheckDB();
	sf::TcpListener listener;
	listener.setBlocking(false);
	listener.listen(8081);
	sf::Packet packet;
	RemoveHandler remover;
	threads.push_back(std::thread(CountUsers));
	std::cout << "\nWorld server ready to accept connections.\n";
	while (true)
	{
		Users* client = new Users;
		if (listener.accept(*client) == sf::Socket::Done)
		{
			packet.clear();
			AddClientToList(client);
		}
		else
		{
			delete client;
		}

		for (std::list<Users*>::iterator receivefrom = clients.begin(); receivefrom != clients.end(); receivefrom++)
		{
			Users& client = **receivefrom;
			packet.clear();
						
			if (client.receive(packet) == sf::Socket::Done)
			{
				int msgtype;
				std::string msg, fmsg;
				packet >> msgtype;
				if (msgtype == MSG_TYPE::Text)
				{
					packet >> msg;
					packet.clear();
					fmsg = "[GLOBAL]: " + msg;
					packet << MSG_TYPE::Text << fmsg;
					threads.push_back(std::thread(SendMsgToAll, packet));
				}
				else if (msgtype == MSG_TYPE::Command)
				{
					int type2;
					packet >> type2;
					if (type2 == CMD_TYPE::gcreate)
					{
						std::string gname;
						packet >> gname;
						packet.clear();
						if (gdb.CreateGroupDBIfNotExists(gname, client.GetName()))
						{
							std::string temp;
							temp = "[SERVER]: Group " + gname + " created successfully. You are the owner of the group.";
							packet << MSG_TYPE::System << temp;
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
						else
						{
							std::string temp;
							temp = "[SERVER]: Group " + gname + " already exists.";
							packet << MSG_TYPE::System << temp;
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
					}
					else if (type2 == CMD_TYPE::gadd)
					{
						std::string gname, who;
						packet >> gname >> who;
						packet.clear();
						if (!gdb.CheckGroupFileExists(gdb.GetDBName(gname)))
						{
							packet << MSG_TYPE::System << "[SERVER]: Group does not exist. It could have been disbanded.";
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
						else
						{
							if (!gdb.CheckIfExistsInGrp(gname, client.GetName()))
							{
								std::string temp;
								temp = "[SERVER]: You are not a member of the group " + gname + ".";
								packet << MSG_TYPE::System << temp;
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
							}
							else if (gdb.GetUserIntFromDB(gname, client.GetName(), std::string("AdminLevel")) < 1)
							{
								packet << MSG_TYPE::System << "[SERVER]: You are not the group admin.";
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
							}
							else
							{
								if (gdb.AddGroupMember(gname, who))
								{
									std::string temp;
									temp = "[SERVER]: Added " + who + " to group " + gname + ". Welcome the new member people.";
									packet << MSG_TYPE::System << temp;
									threads.push_back(std::thread(SendMsgToGroup, gname, packet));
								}
								else
								{
									std::string temp;
									temp = "[SERVER]: Error. Could not add " + who + " to the group";
									packet << MSG_TYPE::System << temp;
									threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
								}
							}
						}
					}
					else if (type2 == CMD_TYPE::gmsg)
					{
						std::string gname, msg;
						packet >> gname >> msg;
						packet.clear();
						if (!gdb.CheckGroupFileExists(gdb.GetDBName(gname)))
						{
							packet << MSG_TYPE::System << "[SERVER]: Group does not exist. It could have been disbanded.";
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
						else
						{
							if (!gdb.CheckIfExistsInGrp(gname, client.GetName()))
							{
								std::string temp;
								temp = "[SERVER]: You are not a member of the group " + gname + ".";
								packet << MSG_TYPE::System << temp;
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
							}
							else
							{
								std::string fmsg;
								fmsg = "[" + gname + "][" + client.GetName() + "]: " + msg;
								packet << MSG_TYPE::Group << fmsg;
								threads.push_back(std::thread(SendMsgToGroup, gname, packet));
							}
						}
					}
					else if (type2 == CMD_TYPE::gdisband)
					{
						std::string gname, fmsg, getint = "AdminLevel";
						packet >> gname;
						packet.clear();
						if (!gdb.CheckGroupFileExists(gdb.GetDBName(gname)))
						{
							packet << MSG_TYPE::System << "[SERVER]: Group does not exist. It could have been disbanded.";
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
						else
						{
							if (!gdb.CheckIfExistsInGrp(gname, client.GetName()))
							{
								std::string temp;
								temp = "[SERVER]: You are not a member of the group " + gname + ".";
								packet << MSG_TYPE::System << temp;
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
							}
							else
							{
								if (gdb.GetUserIntFromDB(gname, client.GetName(), getint) == 1)
								{
									threads.push_back(std::thread(SendDeleteMsgToGroup, gname, client.GetName()));
								}
								else
								{
									packet << MSG_TYPE::System << "[SERVER]: You are not the group admin.";
									threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
								}
							}
						}
					}
					else if (type2 == CMD_TYPE::gexit)
					{
						std::string gname, fmsg, active = "IsActive";
						packet >> gname;
						packet.clear();
						if (gdb.CheckGroupFileExists(gdb.GetDBName(gname)))
						{
							if (gdb.CheckIfExistsInGrp(gname, client.GetName()))
							{
								gdb.RemoveFromGrp(gname, client.GetName());
								fmsg = "[SERVER]: You are successfully removed from group " + gname + ".";
								packet << MSG_TYPE::System << fmsg;
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
								fmsg = "[SERVER]: User " + client.GetName() + " exited from group " + gname + ".";
								packet << MSG_TYPE::System << fmsg;
								threads.push_back(std::thread(SendMsgToGroup, gname, packet));
							}
							else
							{
								std::string temp;
								temp = "[SERVER]: You are not a member of the group " + gname + ".";
								packet << MSG_TYPE::System << temp;
								threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
							}
						}
						else
						{
							packet << MSG_TYPE::System << "[SERVER]: Group does not exist. It could have been disbanded.";
							threads.push_back(std::thread(SendMsgToUser, client.GetName(), packet));
						}
					}
				}

			}
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
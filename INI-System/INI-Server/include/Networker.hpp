#pragma once


class NetworkManager
{
	//Listener for the server.
	sf::TcpListener listener;

	//Packet for network work.
	sf::Packet packet;

	//User list to manage the users.
	std::vector<User *> users;

	//Pointer to the central thread to enable manage by own.
	std::vector<std::thread> *threads;

	//Pointer to the INI Manager.
	INIManager *inimgr;

	//User remover vector which removes all the users which have disconnected.
	std::vector<int> remover;

	//User counter
	int count;

public:

	//Constructor for the network.
	NetworkManager(std::vector<std::thread> *threads, INIManager *inimgr)
	{

		if (threads == nullptr)
			Logger::Log(MsgCode::NETWORK, "ERROR: Threads is a null pointer. Please fix the issue in code!!");

		if (inimgr == nullptr)
			Logger::Log(MsgCode::NETWORK, "ERROR: INI Manager is a null pointer. Please fix the issue in code!!");

		//Set the blocking mode to false or it will wait indefinitely for a connection to establish, thereby stopping the thread till one establishes.
		listener.setBlocking(false);

		//Start listening on port SERVER_PORT.
		listener.listen(SERVER_PORT);
		
		//Clear the packet... Why not!
		packet.clear();

		//Utilize the threads for self without making threads a global variable.
		this->threads = threads;

		//Utilize the INI Manager for self without making global variable.
		this->inimgr = inimgr;

		Logger::Log(MsgCode::NETWORK, "Network initialized successfully.");

	}

	//Must run in the server while loop. Handles the entire network core.
	void Execute()
	{
		//Create a new user.
		User *user = new User;

		//Yaay! a new user connected! Let's add it :D
		if (listener.accept(*user) == sf::Socket::Done)
		{
			std::cout << "\n";
			Logger::Log(MsgCode::NETWORK, "A user connected successfully. Finalizing the connection...");

			//Add client on a separate thread.
			threads->push_back(std::thread(AddClient, &users, user));
		}
		//Delete the user if unaccepted.
		else delete user;

		count = 0;

		//Iterate through all the users.
		for (auto userit = users.begin(); userit != users.end();)
		{
			User &user = **userit;

			//Clear the packet first.
			packet.clear();

			//Receive the packet from the socket.
			if (user.receive(packet) == sf::Socket::Done)
			{
				Logger::Log(MsgCode::NETWORK, "Received packet from user. Handling it now.");
				//Handle the packet in a separate thread please :P
				threads->push_back(std::thread(&NetworkManager::HandlePacket, this, &user, packet));
			}

			//Clear the packet.
			packet.clear();
				
			//Remove the user if he disconnects.
			if (user.receive(packet) == sf::Socket::Disconnected)
			{
				//Close the DB file being used by the user.
				inimgr->CloseFile(user.GetDBConnected());

				Logger::Log(MsgCode::NETWORK, "Removed - disconnected: " + user.GetName() + ".");

				//Delete this user and get the iterator to the next user.
				userit = users.erase(userit);
			}
			else
				++userit;

			count++;
		}

	}

	//Handles the packets received by the server from clients.
	bool HandlePacket(User *user, sf::Packet packet)
	{
		PacketType type;
		int temp;

		//Fetch the packet type.
		packet >> temp;

		//Get Packet type in terms of enumeration.
		type = this->GetPacketType(temp);

		if (type == PacketType::INIACCESS)
		{
			INIAccessType accesstype;

			//Fetch the Access Request type.
			packet >> temp;

			accesstype = GetINIAccessType(temp);


			if (accesstype != INIAccessType::LOAD && !user->IsDBConnected())
			{
				packet.clear();

				packet << PacketType::INIACCESS << INIAccessType::UNDEFINED;

				Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " tried to perform some action on a databse but is not connected to any database!!");

				SendPacket(user, packet);

				return false;
			}
			
			else if ((accesstype == INIAccessType::DELETE || accesstype == INIAccessType::FETCH) && user->IsDBNew())
			{
				Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested to delete/fetch from a nonexisting database!");

				packet.clear();

				packet << PacketType::INIACCESS << INIAccessType::NEWINI;

				SendPacket(user, packet);
			}
			
			else
			{
				if (accesstype == INIAccessType::LOAD)
				{
					std::string file;

					packet >> file;

					Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested action [load] on file: " + file);

					packet.clear();

					if (user->IsDBConnected())
					{
						Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested to change DB from " + user->GetDBConnected() + " to " + file);

						inimgr->CloseFile(user->GetDBConnected());
					}

					if (!inimgr->LoadFile(file))
					{
						packet << PacketType::INIACCESS << INIAccessType::NEWINI;
						user->SetNewDB(true);
					}
					else
					{
						packet << PacketType::INIACCESS << INIAccessType::LOADPASSED;
						user->SetNewDB(false);
					}

					user->SetDBConnected(file);
					SendPacket(user, packet);
				}

				else if (accesstype == INIAccessType::FETCH)
				{
					std::string section, key;

					int datatype;

					packet >> section >> key >> datatype;

					Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested action [fetch] at section: " + section + " on key: " + key);

					packet.clear();

					packet << PacketType::INIACCESS;

					if (datatype == DataType::STRING)
					{
						std::string data = inimgr->GetDataString(user->GetDBConnected(), section, key);

						if (data.empty())
							packet << DataType::FAILEDDATA;
						else
							packet << DataType::SUCCESSDATA << data;
					}
					
					else if (datatype == DataType::INT)
					{
						int data = inimgr->GetDataInt(user->GetDBConnected(), section, key);

						if (data == INT_MIN)
							packet << DataType::FAILEDDATA;
						else
							packet << DataType::SUCCESSDATA << data;

					}
					
					else if (datatype == DataType::FLOAT)
					{
						float data = inimgr->GetDataFloat(user->GetDBConnected(), section, key);

						if (data == FLT_MIN)
							packet << DataType::FAILEDDATA;
						else
							packet << DataType::SUCCESSDATA << data;
					}
					
					else packet << DataType::INVALIDDATA;

					SendPacket(user, packet);
				}

				else if (accesstype == INIAccessType::DELETE)
				{
					std::string section, key;

					packet >> section >> key;

					Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested action [delete] at section: " + section + " on key: " + key);

					packet.clear();

					packet << PacketType::INIACCESS;

					bool done = inimgr->DeleteData(user->GetDBConnected(), section, key);
					
					if (done)
						packet << DataType::SUCCESSDATA;
					else
						packet << DataType::FAILEDDATA;

					SendPacket(user, packet);
				}

				else if (accesstype == INIAccessType::FINALIZE)
				{
					packet.clear();

					packet << PacketType::INIACCESS;

					Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested action [finalize] on database: " + user->GetDBConnected());

					int ret = inimgr->SaveFile(user->GetDBConnected());

					//All good
					if ((bool)ret == true)
					{
						packet << INIAccessType::FINALIZE;
						user->SetNewDB(false);
					}
					//There is nothing to save! (Empty file contents.)
					else if((bool)ret == false)
					{
						packet << INIAccessType::FINALIZEFAILEDNODATA;
						user->SetNewDB(true);
					}
					//The file is not open
					else if (ret == -1)
					{
						packet << INIAccessType::FINALIZEFAILED;
						user->SetNewDB(true);
					}

					SendPacket(user, packet);
				}

				else if (accesstype == INIAccessType::INSERT)
				{
					std::string section, key;

					int datatype;

					packet >> section >> key >> datatype;

					Logger::Log(MsgCode::INIDB, "User: " + user->GetName() + " requested action [insert] at section: " + section + " on key: " + key);

					if (datatype == DataType::STRING)
					{
						std::string val;
						packet >> val;

						packet.clear();

						packet << PacketType::INIACCESS;

						bool done = inimgr->UpdateDataString(user->GetDBConnected(), section, key, val);

						if (done)
							packet << DataType::SUCCESSDATA;
						else
							packet << DataType::FAILEDDATA;
					}
					
					else if (datatype == DataType::INT)
					{
						int val;
						packet >> val;

						packet.clear();

						packet << PacketType::INIACCESS;
						
						bool done = inimgr->UpdateDataInt(user->GetDBConnected(), section, key, val);

						if (done)
							packet << DataType::SUCCESSDATA;
						else
							packet << DataType::FAILEDDATA;
					}
					
					else if (datatype == DataType::FLOAT)
					{
						float val;
						packet >> val;

						packet.clear();

						packet << PacketType::INIACCESS;

						bool done = inimgr->UpdateDataFloat(user->GetDBConnected(), section, key, val);

						if (done)
							packet << DataType::SUCCESSDATA;
						else
							packet << DataType::FAILEDDATA;
					}
					
					else
					{
						packet.clear();
						packet << PacketType::INIACCESS << DataType::INVALIDDATA;
					}

					SendPacket(user, packet);
				}
			}
		}
		
		else
		{
			packet.clear();
			packet << PacketType::INVALID;

			SendPacket(user, packet);
		}

		return true;
	}

	//Convert the integer to INIAccessType.
	INIAccessType GetINIAccessType(int type)
	{
		if (type == 0) return INIAccessType::FETCH;
		else if (type == 1) return INIAccessType::INSERT;
		else if (type == 2) return INIAccessType::DELETE;
		else if (type == 3) return INIAccessType::FINALIZE;
		else if (type == 4) return INIAccessType::FINALIZEFAILED;
		else if (type == 5) return INIAccessType::FINALIZEFAILEDNODATA;
		else if (type == 6) return INIAccessType::LOAD;
		else if (type == 7) return INIAccessType::LOADFAILED;
		else if (type == 8) return INIAccessType::LOADPASSED;
		else if (type == 9) return INIAccessType::NEWINI;
		else return INIAccessType::UNDEFINED;
	}

	//Convert the integer to PacketType.
	PacketType GetPacketType(int pack)
	{
		if (pack == 0) return PacketType::SUCCESS;
		else if (pack == 1) return PacketType::CONNECT;
		else if (pack == 2) return PacketType::ALREADYCONNECTED;
		else if (pack == 3) return PacketType::INIACCESS;
		else if (pack == 4) return PacketType::FAILED;
		else return PacketType::INVALID;
	}
};
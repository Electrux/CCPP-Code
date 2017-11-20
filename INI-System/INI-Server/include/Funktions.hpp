#pragma once


//This function will work always on a separate thread. All input on console is handled by this.
void ConsoleInput()
{
	char input;
	std::string TempConsoleInputStr;

	while (true)
	{
		//Get the input character from user.
		input = getchar();

		if (input == 8) //Backspace
		{
			if (!TempConsoleInputStr.empty())
			{
				//Delete a character from the string.
				TempConsoleInputStr.pop_back();
				
				//Backspace a character on console
				std::cout << "\b" << " " << "\b";
			}
		}
		else if (input == '\n') //Carriage Return
		{
			//If the temporary string is empty, do nothing.
			if (!TempConsoleInputStr.empty())
			{
				//Wait till mutex gets locked.
				while (true)
				{
					//Try to lock the mutex! You can do it!!
					if (ConsoleInputMutex.try_lock())
					{
						break;
					}
				}
				
				//Move the Temporary input to global var.
				ConsoleInputStr = TempConsoleInputStr;

				//Clear the temporary var.
				TempConsoleInputStr.clear();

				//Let the poor mutex be free.
				ConsoleInputMutex.unlock();

				//If the ConsoleInputStr is exit, end this thread.
				if (ConsoleInputStr == "exit")
					break;
			}
			//We pressed Enter... We deserve a newline!!
			//std::cout << "\n"; On second thoughts, it already gets done when we press the Enter button.
		}
		//Oh well... jst push the input in string.
		else TempConsoleInputStr.push_back(input); //Push the input character in the TempInputString.
	}
}

//This function will handle the input received.
ConsoleInputCodes HandleConsoleInput()
{
	//Try to lock the ConsoleInputMutex.
	if (ConsoleInputMutex.try_lock())
	{
		//Check if the global ConsoleInputString is empty.
		if (!ConsoleInputStr.empty())
		{
			//Display the input string.
			Logger::Log(MsgCode::CONSOLEINPUT, "Input received: " + ConsoleInputStr);
			
			//If the input string is exit, clear the mess, and exit the server.
			if (ConsoleInputStr == "exit")
			{

				ConsoleInputStr.clear();
				ConsoleInputMutex.unlock();
				
				return ConsoleInputCodes::EXIT;
			}
			else if (ConsoleInputStr == "saveall")
			{
				ConsoleInputStr.clear();
				ConsoleInputMutex.unlock();

				return ConsoleInputCodes::SAVEALL;
			}
			//Once the input has been dealt with, clear the input.
			ConsoleInputStr.clear();
		}
		//Unlock this poor mutex. It has more jobs to fulfill.
		ConsoleInputMutex.unlock();
	}
	//Done with Console Input thank you very much!
	return ConsoleInputCodes::ALLGOOD;
}

//Stop all the threads. This function is called when the main loop exits and the server is about to exit.
void StopAllThreads(std::vector<std::thread> &threads)
{
	//Dont let any thread go haywire. The main thread shall only exit when all others do so.
	for (auto &thread : threads)
	{
		thread.join();
	}
}

//Checks if a user is already existing in the user list.
bool IsUserConnected(std::vector<User *> *users, std::string name)
{
	for (auto user : *users)
	{
		if (user->GetName() == name)
		{
			return true;
		}
	}

	return false;
}

//Send packet to the user. Try max MAX_PACKET_TRIES times.
bool SendPacket(User *user, sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
{
	if (user == nullptr) return false;

	int count = 0;

	while (count < max_tries)
	{
		if (user->send(packet) == sf::Socket::Done)
		{
			return true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(2));

		++count;
	}

	return false;
}

//Receive packet from the user. Try max MAX_PACKET_TRIES times.
bool ReceivePacket(User *user, sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
{
	packet.clear();

	if (user == nullptr) return false;

	int count = 0;

	while (count < max_tries)
	{
		if (user->receive(packet) == sf::Socket::Done)
		{
			return true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(2));

		++count;
	}

	return false;
}

//Disconnect and delete the user.
void DisconnectUser(User *user)
{
	if (user != nullptr)
	{
		//Disconnect the user.
		user->disconnect();

		//Deallocate user.
		delete user;
	}
}

//Adds the user to server and gives the user confirmation.
bool AddClient(std::vector<User *> *users, User *user)
{
	sf::Packet packet;
	
	std::string name;

	int type;

	//Fetches the first packet from the user.
	if (!ReceivePacket(user, packet))
	{
		//Disconnect and delete user.
		DisconnectUser(user);
		
		//Log the problem.
		Logger::Log(MsgCode::NETWORK, "Could not accept a client. No data received after attemping to connet.");
		
		//Return the function as false.
		return false;
	}

	//Unleashes the packet and fetches the name of the client/user.
	packet >> type >> name;

	//Packet is done for now.
	packet.clear();
	
	//Check if the user is already connected.
	if (IsUserConnected(users, name))
	{
		//Set the message to be already connected.
		packet << PacketType::ALREADYCONNECTED;

		//Send the packet to the user.
		if (!SendPacket(user, packet))
		{
			//Disconnect and delete the client.
			DisconnectUser(user);

			//Log the problem.
			Logger::Log(MsgCode::NETWORK, "A user with name " + name + " is already connected. And it is not receiving packet.");
		}
		else
		{
			//Disconnect and delete the client.
			DisconnectUser(user);

			//Log the problem.
			Logger::Log(MsgCode::NETWORK, "A user with name " + name + " is already connected. Disconnected it successfully.");
		}
	}
	
	else
	{
		//Well, the user is not connected. So connection is successful.
		packet << PacketType::SUCCESS;

		//Send the packet to the user.
		if (!SendPacket(user, packet))
		{
			//Disconnect and delete the client.
			DisconnectUser(user);

			//Log the problem.
			Logger::Log(MsgCode::NETWORK, "A user with name " + name + " tried to connect but is not receiving any packets. Disconnected it successfully.");
		}
		else
		{
			//Set the blocking mode to false.
			user->setBlocking(false);

			//Set its name in the user object.
			user->SetName(name);

			//Add the user to user vector.
			users->push_back(user);
			
			//Clear the packet.
			packet.clear();

			//Log the information.
			Logger::Log(MsgCode::NETWORK, "A user with name " + name + " connected successfully.");

			//Yaay all went well!!!
			return true;
		}
	}

	//Clear the packet.
	packet.clear();

	//Well... All went well I guess.
	return true;
}


#pragma once


bool InitNetwork(sf::TcpSocket &socket)
{
	socket.setBlocking(false);

	std::cout << "Enter username and filename:\n";

	std::cin >> username >> db;

	int count = 0;
	bool connected = false;

	sf::Packet packet;
	
	std::cout << "Trying to connect to the server...\n";

	while (count < MAX_PACKET_TRIES)
	{
		if (socket.connect(sf::IpAddress::getLocalAddress(), SERVER_PORT) == sf::Socket::Done)
		{
			connected = true;
			break;
		}

		count++;
	}
	
	if (!connected) return false;

	std::cout << "Connection succeeded. Ready to send and receive data :D\n";

	packet << PacketType::CONNECT << username;

	if (!SendPacket(socket, packet))
	{
		std::cout << "Error sending packet. Please check network!\n";
		return false;
	}

	packet.clear();

	if (!ReceivePacket(socket, packet))
	{
		std::cout << "Error receiving packet. Please check network!\n";
		return false;
	}

	int status;

	packet >> status;

	if (status == PacketType::SUCCESS)
	{
		std::cout << "Network successfully established and accepted!\n";
	}
	else if (status == PacketType::ALREADYCONNECTED)
	{
		std::cout << "Network failed! User with this name is already connected!\n";
		return false;
	}

	packet.clear();

	packet << PacketType::INIACCESS << INIAccessType::LOAD << db;

	if (!SendPacket(socket, packet))
	{
		std::cout << "Error sending packet. Please check network!\n";
		return false;
	}

	packet.clear();

	if (!ReceivePacket(socket, packet))
	{
		std::cout << "Error receiving packet. Please check network!\n";
		return false;
	}

	int iniaccess, load;

	packet >> iniaccess >> load;

	if (load == INIAccessType::LOADFAILED)
		std::cout << "Failed loading the file (File does not exist)\n";
	else
		std::cout << "File loaded successfully\n";

	return true;
}
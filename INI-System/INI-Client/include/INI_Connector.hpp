#pragma once


#include "Enums.hpp"
#include "Data.hpp"

class INI_Connector
{
	sf::TcpSocket socket;

	bool connected;

	std::string username, db;

	//Send packet to the user. Try max MAX_PACKET_TRIES times.
	bool SendPacket(sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
	{
		int count = 0;

		if (!connected) return false;

		while (count < max_tries)
		{
			if (socket.send(packet) == sf::Socket::Done)
				return true;

			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			++count;
		}

		return false;
	}

	//Receive packet from the user. Try max MAX_PACKET_TRIES times.
	bool ReceivePacket(sf::Packet &packet, int max_tries = MAX_PACKET_TRIES)
	{
		packet.clear();

		int count = 0;

		if (!connected) return false;

		while (count < max_tries)
		{
			if (socket.receive(packet) == sf::Socket::Done)
				return true;

			std::this_thread::sleep_for(std::chrono::milliseconds(2));

			++count;
		}

		return false;
	}

public:

	//Initializes the network with username and database.
	bool InitNetwork(std::string username)
	{

		this->username = username;
		this->db = db;

		socket.setBlocking(false);

		int count = 0;
		connected = false;

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

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		packet.clear();

		if (!ReceivePacket(packet))
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

		connected = true;

		return true;
	}

	//Connect to a Database.
	bool ConnectDB(std::string db)
	{
		sf::Packet packet;
		packet << PacketType::INIACCESS << INIAccessType::LOAD << db;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet at db. Please check network!\n";
			return false;
		}

		int status, load;

		packet >> status >> load;

		if (load == INIAccessType::NEWINI)
			std::cout << "Created new INI (File did not exist previously)\n";
		else if (load == INIAccessType::LOADPASSED)
			std::cout << "File loaded successfully\n";

		return true;
	}

	std::string FetchString(std::string section, std::string key)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::FETCH << section << key << DataType::STRING;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return "NODATA";
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return "NODATA";
		}

		int accesstype, type;
		std::string str;

		packet >> accesstype >> type;

		if (type == INIAccessType::NEWINI)
		{
			std::cout << "There is nothing in the database to fetch!\n";
		}
		else if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "This data does not exist!\n";
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
		}
		else if(type == DataType::SUCCESSDATA)
		{
			packet >> str;
		}

		return str;
	}

	int FetchInt(std::string section, std::string key)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::FETCH << section << key << DataType::INT;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type, data = -1;

		packet >> accesstype >> type;

		if (type == INIAccessType::NEWINI)
		{
			std::cout << "There is nothing in the database to fetch!\n";
		}
		else if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "This data does not exist!\n";
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
		}
		else if(type == DataType::SUCCESSDATA)
		{
			packet >> data;
		}

		return data;
	}

	float FetchFloat(std::string section, std::string key)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::FETCH << section << key << DataType::FLOAT;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;
		float data;

		packet >> accesstype >> type;

		if (type == INIAccessType::NEWINI)
		{
			std::cout << "There is nothing in the database to fetch!\n";
		}
		else if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "This data does not exist!\n";
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
		}
		else if(DataType::SUCCESSDATA)
		{
			packet >> data;
		}

		return data;
	}

	bool InsertString(std::string section, std::string key, std::string val)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::INSERT << section << key << DataType::STRING << val;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;
		packet >> accesstype >> type;


		if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
			return false;
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "Could not insert data. File might not be open on the server. Please reconnect!\n";
			return false;
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
			return false;
		}
		else if (type == DataType::SUCCESSDATA)
		{
			std::cout << "Successfully inserted data. To finalize it, call the finalize function!\n";
		}

		return true;
	}

	bool InsertInt(std::string section, std::string key, int val)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::INSERT << section << key << DataType::INT << val;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;
		packet >> accesstype >> type;


		if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
			return false;
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "Could not insert data. File might not be open on the server. Please reconnect!\n";
			return false;
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
			return false;
		}
		else if (type == DataType::SUCCESSDATA)
		{
			std::cout << "Successfully inserted data. To finalize it, call the finalize function!\n";
		}

		return true;
	}

	bool InsertFloat(std::string section, std::string key, float val)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::INSERT << section << key << DataType::STRING << val;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;
		packet >> accesstype >> type;


		if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
			return false;
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "Could not insert data. File might not be open on the server. Please reconnect!\n";
			return false;
		}
		else if (type == DataType::INVALIDDATA)
		{
			std::cout << "This is not a valid datatype!\n";
			return false;
		}
		else if (type == DataType::SUCCESSDATA)
		{
			std::cout << "Successfully inserted data. To finalize it, call the finalize function!\n";
		}

		return true;
	}

	bool DeleteData(std::string section, std::string key)
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::DELETE << section << key;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;
		packet >> accesstype >> type;


		if (type == INIAccessType::NEWINI)
		{
			std::cout << "There is nothing in the database to fetch!\n";
		}
		else if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
			return false;
		}
		else if (type == DataType::FAILEDDATA)
		{
			std::cout << "Could not delete data. File might not be open on the server or the key may not exist. Please reconnect!\n";
			return false;
		}
		else if (type == DataType::SUCCESSDATA)
		{
			std::cout << "Successfully deleted data. To finalize it, call the finalize function!\n";
		}

		return true;
	}

	bool FinalizeDatabase()
	{
		sf::Packet packet;

		packet << PacketType::INIACCESS << INIAccessType::FINALIZE;

		if (!SendPacket(packet))
		{
			std::cout << "Error sending packet. Please check network!\n";
			return false;
		}

		if (!ReceivePacket(packet))
		{
			std::cout << "Error receiving packet. Please check network!\n";
			return false;
		}

		int accesstype, type;

		packet >> accesstype >> type;

		if (type == INIAccessType::UNDEFINED)
		{
			std::cout << "You are not connected to any Database!\n";
			return false;
		}
		else if (type == INIAccessType::FINALIZEFAILED)
		{
			std::cout << "Failed to save the data!\n";
			return false;
		}
		else if (type == INIAccessType::FINALIZEFAILEDNODATA)
		{
			std::cout << "Failed to save data because there is nothing to save!\n";
			return false;
		}
		else if (type == INIAccessType::FINALIZE)
		{
			std::cout << "Saved the data successfully!\n";
		}

		return true;
	}
};
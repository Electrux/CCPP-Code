#ifdef _WIN32

#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <iostream>
#include <Windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Data.hpp"
#include "Enums.hpp"

class Network
{
	sf::TcpSocket socket;
	sf::Packet packet;
	std::string finalmsg, recvmsg;
	bool auth;

	public:

		bool Init(sf::IpAddress &ip, int &port)
		{
			packet.clear();
			
			auth = false;
			
			int count = 0;
			
			while (true)
			{
				if (socket.connect(ip, port) == sf::Socket::Done)
					break;

				if (count > 1000)
				{
					return false;
				}
				count++;
			}
			
			return true;
		}
		void SendMessage(std::string &msg, int type = MSG_TYPE::Text)
		{
			packet.clear();
			if (type == MSG_TYPE::Text)
				finalmsg = myname + ": " + msg;
			else
				finalmsg = msg;
			packet << type << finalmsg;
			if (!SendPacket(packet))
				std::cout << "\nCould not send message!";
			packet.clear();
		}
		int Authenticate(std::string &name, std::string &pass)
		{
			packet.clear();
			packet << name << pass << sf::IpAddress().getPublicAddress().toString();
			int count = 0;
			if (!SendPacket(packet))
				return false;
			packet.clear();
			count = 0;
			while (true)
			{
				if (socket.receive(packet) == sf::Socket::Done)
				{
					break;
				}
				if (count > 1000)
				{
					return false;
				}
				count++;
			}
			int isauth;
			packet >> isauth;
			packet.clear();
			Disconnect();
			if (isauth == Auth::Registered)
			{
				auth = true;
				return Auth::Registered;
			}
			else if (isauth == Auth::Authenticated)
			{
				auth = true;
				return Auth::Authenticated;
			}
			else if (isauth == Auth::WrongPass)
			{
				return Auth::WrongPass;
			}
			else if (isauth == Auth::AlreadyLogged)
			{
				return Auth::AlreadyLogged;
			}
			return false;
		}
		bool Disconnect()
		{
			socket.disconnect();
			return true;
		}
		bool WorldServerConnect()
		{
			packet.clear();
			packet << MSG_TYPE::Connected << myname;
			if (!SendPacket(packet))
				return false;
			packet.clear();
			socket.setBlocking(false);
			return true;
		}

		bool IsAuthenticated()
		{
			return auth;
		}

		bool SendPacket(sf::Packet &pkt)
		{
			int count = 0;
			while (true)
			{
				if (socket.send(pkt) == sf::Socket::Done)
					break;
				if (count > 1000)
				{
					return false;
				}
				count++;
			}
			return true;
		}

		int GetMsg(std::string &recvmsg)
		{
			packet.clear();
			recvmsg.clear();
			int msgtype;
			msgtype = -1;
			if (socket.receive(packet) == sf::Socket::Done)
			{
				packet >> msgtype;
				if (msgtype == MSG_TYPE::Authenticate
				    || msgtype == MSG_TYPE::Command
				    || msgtype == MSG_TYPE::Connected
				    || msgtype == MSG_TYPE::Count
				    || msgtype == MSG_TYPE::Group
				    || msgtype == MSG_TYPE::System
				    || msgtype == MSG_TYPE::Text)
				{
					if (msgtype == MSG_TYPE::Count)
					{
						int msg;
						char tempbuf[5];
						packet >> msg;
						_itoa_s(msg, tempbuf, 10);
						recvmsg = tempbuf;
						packet.clear();
						return MSG_TYPE::Count;
					}
					else
						packet >> recvmsg;
					packet.clear();
					return 1;
				}
				else return -1;
			}
			else
			{
				return -1;
			}
		}
};

#endif // CONNECTOR_HPP

#endif // _WIN32

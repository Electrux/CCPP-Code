#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "TextHandler.hpp"
#include "Connector.hpp"

class ChatEngine
{
	sf::RenderWindow window;
	sf::Event event;
	TextHandler alltext;
	Network connection;
	bool iscmd, connected;
	std::string recvtext;
	int count;
	public:
		ChatEngine()
		{
			iscmd = false;
			recvtext.clear();
			if (!InitNetwork())
			{
				connected = false;
				std::cout << "\nNetwork Failed!\n";
			}
			else connected = true;
		}

		void PollEvent();
		bool InitNetwork(sf::IpAddress &ip = sf::IpAddress("127.0.0.1"));

		bool Init(sf::VideoMode &mode, std::string &name)
		{
			window.create(mode, name);
			return true;
		}
		bool IsConnected()
		{
			return connected;
		}
		bool IsOpen()
		{
			return window.isOpen();
		}
		void Draw()
		{
			window.draw(alltext);
		}
		void Clear()
		{
			window.clear();
		}
		void EnterText(std::string &text)
		{
			alltext.AddText(text);
		}
		void Display()
		{
			window.display();
		}
		void Update()
		{
			int msg = connection.GetMsg(recvtext);

			if (msg != -1)
			{
				//std::cout << "\nReceived: " << recvtext;
				if (msg == MSG_TYPE::Count)
				{
					alltext.UpdateCount(recvtext);
				}
				else
				{
					EnterText(recvtext);
				}
				recvtext.clear();
			}
		}
		bool GenerateCommand(std::string &msg, sf::Packet &pack)
		{
			if (msg.find("/gadd") != std::string::npos)
			{
				std::vector<std::string> dest;
				if (!alltext.getDelimitedStrings(msg, &dest))
				{
					EnterText(std::string("[SYSTEM]: Incorrect Syntax. Syntax: /gadd <Group Name (No spaces allowed)> <name of user>"));
					return false;
				}
				else
				{
					pack.clear();
					pack << MSG_TYPE::Command << CMD_TYPE::gadd << dest[1] << dest[2];
					return true;
				}
			}
			else if (msg.find("/gmsg") != std::string::npos)
			{
				std::vector<std::string> dest;
				if (!alltext.getDelimitedStrings(msg, &dest))
				{
					EnterText(std::string("[SYSTEM]: Incorrect Syntax. Syntax: /gmsg <Group Name (No spaces allowed)> <message>"));
					return false;
				}
				else
				{
					pack.clear();
					pack << MSG_TYPE::Command << CMD_TYPE::gmsg << dest[1] << dest[2];
					return true;
				}
			}
			else if (msg.find("/gcreate") != std::string::npos)
			{
				std::vector<std::string> dest;
				if (!alltext.getDelimitedStrings(msg, &dest, 2))
				{
					EnterText(std::string("[SYSTEM]: Incorrect Syntax. Syntax: /gcreate <Group Name (No spaces allowed)>"));
					return false;
				}
				else
				{
					pack.clear();
					pack << MSG_TYPE::Command << CMD_TYPE::gcreate << dest[1];
					return true;
				}
			}
			else if (msg.find("/gdisband") != std::string::npos)
			{
				std::vector<std::string> dest;
				if (!alltext.getDelimitedStrings(msg, &dest, 2))
				{
					EnterText(std::string("[SYSTEM]: Incorrect Syntax. Syntax: /gdisband <Group Name (No spaces allowed)>"));
					return false;
				}
				else
				{
					pack.clear();
					pack << MSG_TYPE::Command << CMD_TYPE::gdisband << dest[1];
					return true;
				}
			}
			else if (msg.find("/gexit") != std::string::npos)
			{
				std::vector<std::string> dest;
				if (!alltext.getDelimitedStrings(msg, &dest, 2))
				{
					EnterText(std::string("[SYSTEM]: Incorrect Syntax. Syntax: /gexit <Group Name (No spaces allowed)>"));
					return false;
				}
				else
				{
					pack.clear();
					pack << MSG_TYPE::Command << CMD_TYPE::gexit << dest[1];
					return true;
				}
			}
			else if (msg.find("/help") != std::string::npos)
			{
				EnterText(std::string("--------------------------COMMANDS------------------------"));
				EnterText(std::string("/gcreate <Group Name (No spaces allowed)>  ->  Create a group."));
				EnterText(std::string("/gdisband <Group Name (No spaces allowed)>  ->  Destroy the given group."));
				EnterText(std::string("/gadd <Group Name (No spaces allowed)> <Username of the person to add (Must be online)>  ->  To add someone to the given group."));
				EnterText(std::string("/gexit <Group Name (No spaces allowed)>  ->  To exit from a given group."));
				EnterText(std::string("/gmsg <Group Name (No spaces allowed)> <Message>  ->  To send message to the given group."));
				EnterText(std::string("/help  ->  To display this message."));
				return false;
			}
			else
			{
				EnterText(std::string("[SYSTEM]: Invalid Command/Syntax. Please use /help to see the commands and their syntax."));
				return false;
			}
		}
		void Close()
		{
			window.close();
		}
};

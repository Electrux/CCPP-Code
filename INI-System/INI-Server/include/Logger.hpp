#pragma once


class Logger
{

public:

	static void Log(MsgCode msgtype, std::string msg)
	{
		std::cout << "[" << MSGS[msgtype] << "] : " << msg << "\n";
	}

};
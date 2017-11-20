#ifndef ENUMS_HPP
#define ENUMS_HPP

enum MSG_TYPE
{
	Authenticate,
	Connected,
	Text,
	Command,
	System,
	Group,
	Count
};

enum CMD_TYPE
{
	gcreate, //Create Group
	gdisband, // Disband Group
	gexit, // Exit Group
	gadd, // Invite someone to Group
	gmsg, // Send message to Group
};

enum Auth
{
	Registered,
	Authenticated,
	WrongPass,
	AlreadyLogged
};

#endif // ENUMS_HPP

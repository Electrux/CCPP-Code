#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <string>

extern std::unordered_map< int, std::string > COMMANDS_STRING;

enum COMMANDS
{
	PRINT,
	SCAN,
	VAR,
	FOR,
};

#endif // COMMANDS_HPP

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <string>

extern std::unordered_map< int, std::string > COMMANDS_STRING;

enum COMMANDS
{
	OK,
	ERR,

	PRINT,
	SCAN,
	VAR,
	IF,
	ELSE,
	ELSEIF,
	ENDIF,
	FOR,
	ENDFOR,

	BREAK,
	CONTINUE,

	STATEMENT,
};

#endif // COMMANDS_HPP

#include <unordered_map>
#include <string>

#include "../include/Commands.hpp"

std::unordered_map< int, std::string > COMMANDS_STRING = {
	{ 0, "ok" },
	{ 1, "err" },

	{ 2, "print" },
	{ 3, "scan" },
	{ 4, "var" },
	{ 5, "if" },
	{ 6, "else" },
	{ 7, "elseif" },
	{ 8, "fi" },
	{ 9, "for" },
	{ 10, "rof" },

	{ 11, "break" },
	{ 12, "continue" },

	{ 13, "statement" },
};

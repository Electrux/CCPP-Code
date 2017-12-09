#include <unordered_map>
#include <string>

#include "../include/Commands.hpp"

std::unordered_map< int, std::string > COMMANDS_STRING = {
	{ 0, "print" },
	{ 1, "scan" },
	{ 2, "var" },
	{ 3, "for" },
};

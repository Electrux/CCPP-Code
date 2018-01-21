#ifndef COLORS_HPP
#define COLORS_HPP

#include <string>
#include <map>

static std::map< std::string, std::string > COLORS = {
	{ "O", "\033[0m" },

	{ "R",  "\033[0;31m" },
	{ "G",  "\033[0;32m" },
	{ "Y",  "\033[0;33m" },
	{ "B",  "\033[0;34m" },
	{ "M",  "\033[0;35m" },
	{ "C",  "\033[0;36m" },
	{ "W",  "\033[0;37m" },
	{ "BR", "\033[1;31m" },
	{ "BG", "\033[1;32m" },
	{ "BY", "\033[1;33m" },
	{ "BB", "\033[1;34m" },
	{ "BM", "\033[1;35m" },
	{ "BC", "\033[1;36m" },
	{ "BW", "\033[1;37m" },

	{ "FC",  "\033[0;33m" },
	{ "SC",  "\033[0;36m" },
	{ "TC",  "\033[0;35m" },
	{ "EC",  "\033[0;34m" },
};

int SubstituteColors( std::string & str );

#endif // COLORS_HPP
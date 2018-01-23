#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>
#include <vector>

struct Error
{
	int line;
	ErrorTypes errtype;
};

enum ErrorTypes
{
	BRACKET_MISMATCH,

	LAST
};

const std::string ErrorStrings[ LAST + 1 ] = {
	"BRACKET_MISMATCH",

	"UNKNOWN"
};

std::string ErrorToStr( ErrorTypes errtype )
{
	if( errtype < 0 || errtype >= LAST )
		return ErrorStrings[ LAST ];

	return ErrorStrings[ errtype ];
}

#endif // ERRORS_HPP
#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

enum ErrorTypes
{
	SUCCESS,
	SYNTAX_ERROR,
	BRACKET_MISMATCH,
	DOUBLE_DECLARATION,

	LAST
};

const std::string ErrorStrings[ LAST + 1 ] = {
	"SUCCESS",
	"SYNTAX_ERROR",
	"BRACKET_MISMATCH",
	"DOUBLE_DECLARATION",

	"UNKNOWN"
};

std::string ErrorToStr( ErrorTypes errtype );

#endif // ERRORS_HPP
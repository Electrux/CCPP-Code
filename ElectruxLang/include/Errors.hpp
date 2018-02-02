#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

enum ErrorTypes
{
	SUCCESS,
	SYNTAX_ERROR,
	ENTITY_NOT_FOUND,
	BRACKET_MISMATCH,
	DOUBLE_DECLARATION,
	INVALID_EXPRESSION,

	LAST
};

const std::string ErrorStrings[ LAST + 1 ] = {
	"SUCCESS",
	"SYNTAX_ERROR",
	"ENTITY_NOT_FOUND",
	"BRACKET_MISMATCH",
	"DOUBLE_DECLARATION",
	"INVALID_EXPRESSION",

	"UNKNOWN"
};

std::string ErrorToStr( ErrorTypes errtype );

#endif // ERRORS_HPP
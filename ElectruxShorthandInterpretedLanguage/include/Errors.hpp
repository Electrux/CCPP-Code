#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

enum ErrorTypes
{
	SUCCESS,
	SYNTAX_ERROR,
	INPUT_FAILURE,
	ENTITY_NOT_FOUND,
	BRACKET_MISMATCH,
	DOUBLE_DECLARATION,
	INVALID_EXPRESSION,
	SYSTEM_FAILURE,

	LAST
};

const std::string ErrorStrings[ LAST + 1 ] = {
	"SUCCESS",
	"SYNTAX_ERROR",
	"INPUT_FAILURE",
	"ENTITY_NOT_FOUND",
	"BRACKET_MISMATCH",
	"DOUBLE_DECLARATION",
	"INVALID_EXPRESSION",
	"SYSTEM_FAILURE",

	"UNKNOWN"
};

std::string ErrorToStr( ErrorTypes errtype );

#endif // ERRORS_HPP
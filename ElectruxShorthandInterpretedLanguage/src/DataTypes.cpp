#include <vector>
#include <string>

#include "../include/DataTypes.hpp"

namespace DataType
{
	std::vector< std::string > SYMBOL_STR = {

		"num",
		"float",
		"string",

		"operator",
		"logical",
		"separator",

		"literal",
		"keyword",
		"identifier",

		"invalid",
	};

	std::vector< std::string > KEYWORDS_STR = {

		"var",
		"vecvar",

		"fn",

		"if",
		"elseif",
		"else",
		"fi",

		"for",
		"to",
		"in",
		"break",
		"continue",
		"rof",

		"print",
		"scan",

		"ret",

		"#",
	};

	std::vector< std::string > OPERATORS_STR = {

		"=",
		"+",
		"-",
		"*",
		"/",
		"%",
	};

	std::vector< std::string > LOGICAL_OPERATORS_STR = {

		"==",
		">",
		"<",
		">=",
		"<=",

		"&&",
		"||",
		"!",
	};

	std::vector< std::string > SEPARATORS_STR = {

		" ",
		"\n",
		"\t",

		".",
		"->",
		":",
		",",

		"(",
		")",

		"{",
		"}",

		"[",
		"]",
	};

	std::vector< std::vector< SymbolType > > BASE_POSSBILE_TYPES = {
//                 NUM    FLOAT    STRING    OPERATOR  LOGICAL  SEPARATOR LITERAL
//                 KEYWORD  IDENTIFIER INVALID
/* NUM */	{  NUM,   FLOAT,   INVALID,  INVALID,  INVALID, INVALID, INVALID,
		   INVALID, INVALID,   INVALID },
/* FLOAT */	{ FLOAT,  INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* STRING */	{ STRING, INVALID, STRING,   INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* OPERATOR */	{ INVALID,INVALID, INVALID,  LOGICAL,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* LOGICAL */	{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* SEPARATOR */	{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* LITERAL */	{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* KEYWORD */	{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* IDENTIFIER */{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
/* INVALID */	{ INVALID,INVALID, INVALID,  INVALID,  INVALID, INVALID, INVALID,
		  INVALID, INVALID,   INVALID },
	};

	SymbolType GetLetterType( const char ch )
	{
		if( std::isalpha( ch ) )
			return SymbolType::STRING;

		if( ch == '.' )
			return SymbolType::FLOAT;

		if( std::isdigit( ch ) )
			return SymbolType::NUM;

		if( std::ispunct( ch ) )
			return SymbolType::OPERATOR;

		return SymbolType::INVALID;
	}

	SymbolType GetDataType( const std::string & str )
	{
		SymbolType type = SymbolType::INVALID;

		if( str.empty() )
			return type;

		if( * str.begin() == '\'' ) {

			if( * ( str.end() - 1 ) == '\'' )
				type = SymbolType::LITERAL;

			return type;
		}

		if( * str.begin() == '\"' ) {

			if( * ( str.end() - 1 ) == '\"' ) 
				type = SymbolType::LITERAL;

			return type;
		}

		if( str == ".." )
			return SymbolType::STRING;

		// Return the type of character if the string comprises of a single character.
		if( str.size() < 2 )
			return GetLetterType( * str.begin() );

		SymbolType prevtype = GetLetterType( * str.begin() );

		for( auto ch = str.begin() + 1; ch != str.end(); ++ch ) {

			type = GetLetterType( * ch );

			if( BASE_POSSBILE_TYPES[ prevtype ][ type ] == INVALID ) {
				type = INVALID;
				break;
			}

			type = BASE_POSSBILE_TYPES[ prevtype ][ type ];

			prevtype = type;
		}

		return type;
	}

}

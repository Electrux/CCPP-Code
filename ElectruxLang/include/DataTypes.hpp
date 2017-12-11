#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <vector>
#include <string>

namespace DataType
{
	enum SymbolType
	{
		NUM,
		FLOAT,
		STRING,

		OPERATOR,
		LOGICAL,
		SEPARATOR,

		LITERAL,
		KEYWORD,
		IDENTIFIER,

		INVALID,
	};

	enum Keywords
	{
		VAR,

		IF,
		ELSEIF,
		ELSE,
		FI,

		FOR,
		DOUBLEDOT,
		IN,
		BREAK,
		CONTINUE,
		ENDFOR,

		PRINT,
		SCAN,

		RETURN,

		LINECOMMENT,
	};

	enum Operators
	{
		ASSIGN,
		ADD,
		SUB,
		MULT,
		DIV,
		MOD,
	};

	enum Logical_Operators
	{
		EQUAL,
		GREATER,
		LESS,
		GREATEREQ,
		LESSEQ,

		AND,
		OR,
		NOT,
	};

	enum Separators
	{
		SPACE,
		NEWLINE,
		DOT,
		BLOCKBEGIN,
		PARENTHESISOPEN,
		PARENTHESISCLOSE,
		CURLYBRACESOPEN,
		CURLYBRACESCLOSE,
		BRACKETSOPEN,
		BRACKETSCLOSE,
	};

	struct Data
	{
		SymbolType type;
		std::string word;
	};

	extern std::vector< std::string > SYMBOL_STR;

	extern std::vector< std::string > KEYWORDS_STR;
	extern std::vector< std::string > OPERATORS_STR;
	extern std::vector< std::string > LOGICAL_OPERATORS_STR;	
	extern std::vector< std::string > SEPARATORS_STR;

	extern std::vector< std::vector< SymbolType > > BASE_POSSBILE_TYPES;

	SymbolType GetLetterType( const char ch );

	SymbolType GetDataType( const std::string & str );
}

#endif // DATATYPES_HPP

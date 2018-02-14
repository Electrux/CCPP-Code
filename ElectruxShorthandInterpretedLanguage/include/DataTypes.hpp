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
		STRING,    // COMPLEX

		OPERATOR,  // COMPLEX
		LOGICAL,   // COMPLEX
		SEPARATOR,

		LITERAL,
		KEYWORD,
		IDENTIFIER,

		INVALID,
	};

	enum Keywords
	{
		VAR,

		FN,
		LOAD,

		IF,
		ELSEIF,
		ELSE,

		FOR,
		DOUBLEDOT,
		IN,
		BREAK,
		CONTINUE,

		PRINT,
		SCAN,

		// World commands - Interacting with environment.
		SETENV,
		GETENV,
		SYSEXEC,

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
		TAB,
		DOT,
		ARROW,
		BLOCKBEGIN,
		COMMA,
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
		int detailtype;
		std::string word;

		// Exclusively for indent.
		int indent;

		// Line number corresponding to file.
		int fileline;
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

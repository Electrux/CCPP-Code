/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <cctype>
#include <vector>
#include <string>
#include <algorithm>
#include <optional>
#include <variant>

#include "../../include/Errors.hpp"
#include "../../include/Core.hpp"

#include "../../include/Lexer/Lexer.hpp"

const std::vector< std::string > Lex::SymTypeStrs = {
	"NUM",
	"STR",
	"OPER",
	"SEPAR",

	"FSMLAST",

	// NOT FOR FSM

	// NUM
	"INT",
	"FLT",

	// STR
	"KEYW",
	"IDEN",

	// OPER
	"ARITH",
	"LOGIC",
};

const std::vector< std::string > Lex::KeywStrs = {
	"let",

	"if",
	"elif",
	"else",

	"for",
	"<-",
	"continue",
	"break",

	"fn",
	"ret",
	"->",
};

const std::vector< std::string > Lex::ArithStrs = {
	"+",
	"-",
	"*",
	"/",
	"%",
	"^",

	"=",
};

const std::vector< std::string > Lex::LogicStrs = {
	"&&",
	"||",
	"!",

	"==",
	"<",
	">",
	"<=",
	">=",
	"!=",
};

const std::vector< char > Lex::SeparChars = {
	' ',
	'\t',
	'\n',
	',',
	':',
	';',

	'(',
	')',
	'{',
	'}',
	'[',
	']',

	'#',

	'\'',
	'\"',
};

using namespace Lex;

static const int FSM[ FSMLAST ][ FSMLAST ] = {
//		  NUM	STR	OPER	SEPAR
/* NUM */	{ NUM,	STR,	OPER,	SEPAR },
/* STR */	{ STR,	STR,	OPER,	SEPAR },
/* OPER */	{ NUM,	STR,	OPER,	SEPAR },
/* SEPAR */	{ NUM,	STR,	OPER,	SEPAR },
};
static std::variant< int, std::string > GetQuotedString( const std::string & data,
							std::string::const_iterator & it,
							const int line, const int col );
static int GetCharType( const char ch, const char prev_ch, const int line, const int col );
static inline bool issepar( const char ch );
static int GetDataType( const std::string & data, const int approx_type, const int line, const int col );
static int GetDetailType( const std::string & data, const int type, const int line, const int col );

std::variant< int, Syms > Lex::Tokenize( const std::string & data )
{
	if( data.empty() ) return -1;

	int line = 1;
	std::string::const_iterator line_begin = data.begin();
	int col = 1;
	Syms syms;
	std::string buffer;

	int prev_state = GetCharType( data[ 0 ], -1, 1, 1 ), next_state = -1;
	for( auto it = data.begin(); it != data.end(); ++it ) {
		if( * it == SeparChars[ COMMENT ] ) {
			while( it != data.end() && * it != SeparChars[ NEWL ] ) ++it;
		}

		char prev_ch = ( it == data.begin() ) ? -1 : ( * ( it - 1 ) );
		char ch = * it;

		next_state = GetCharType( ch, prev_ch, line, col );
		if( next_state < 0 ) return next_state;

		if( !buffer.empty() && ( FSM[ prev_state ][ next_state ] != prev_state || next_state == SEPAR ) ) {
			int type = prev_state, detail_type = -1;
			if( prev_state == OPER || prev_state == STR || prev_state == NUM ) {
				type = GetDataType( buffer, prev_state, line, col );
				if( type < 0 ) return type;
			}
			if( prev_state == OPER || prev_state == STR || prev_state == SEPAR ) {
				detail_type = GetDetailType( buffer, type, line, col );
			}
			syms.push_back( new Sym( ( SymType )type, detail_type, buffer, line, col ) );
			buffer.clear();
		}

		if( ch == SeparChars[ NEWL ] ) {
			++line;
			line_begin = it + 1;
		}

		if( FSM[ prev_state ][ next_state ] != prev_state || next_state == SEPAR ) {
			col = std::distance( line_begin, it ) + 1;
		}

		prev_state = FSM[ prev_state ][ next_state ];

		if( ch == SeparChars[ SINGQUOTE ] || ch == SeparChars[ DOUBQUOTE ] ) {
			auto quote_str_var = GetQuotedString( data, it, line, col );
			if( std::holds_alternative< int >( quote_str_var ) ) return std::get< int >( quote_str_var );
			syms.push_back( new Sym( STR, -1, std::get< std::string >( quote_str_var ), line, col ) );
			// continue to avoid adding quote to buffer
			continue;
		}

		if( next_state != SEPAR || ( ch != SeparChars[ TAB ] &&
						ch != SeparChars[ NEWL ] &&
						ch != SeparChars[ SPC ]// &&
						//ch != SeparChars[ SINGQUOTE ] &&
						//ch != SeparChars[ DOUBQUOTE ]
						) ) {
			buffer += ch;
		}
	}
	if( !buffer.empty() ) {
		int type = prev_state, detail_type = -1;
		if( prev_state == OPER || prev_state == STR || prev_state == NUM ) { 
			type = GetDataType( buffer, prev_state, line, col );
			if( type < 0 ) return type;
		}
		if( prev_state == OPER || prev_state == STR || prev_state == SEPAR ) {
			detail_type = GetDetailType( buffer, type, line, col );
		}
		syms.push_back( new Sym( ( SymType )type, detail_type, buffer, line, col ) );
		buffer.clear();
	}

	return syms;
}

static std::variant< int, std::string > GetQuotedString( const std::string & data,
							std::string::const_iterator & it,
							const int line, const int col )
{
	std::string res;
	// Add the starting quote to string
	res += * it;
	char quote = * it;
	++it;
	while( it != data.end() && * it != SeparChars[ Separ::NEWL ] && * it != quote ) {
		res += * it++;
	}
	if( * it != quote ) {
		return ret_err( "The quote started here never closed", -1, line, col );
	}

	// Add the ending quote to string
	res += * it;
	return res;
}

static int GetCharType( const char ch, const char prev_ch, const int line, const int col )
{
	if( ch == '.' ) {
		if( prev_ch >= 0 && std::isdigit( prev_ch ) ) return NUM;
		return OPER;
	}
	if( ch == '_' ) {
		if( prev_ch >= 0 && std::isalnum( prev_ch ) ) return STR;
		return OPER;
	}

	if( std::isalpha( ch ) ) return STR;
	if( std::isdigit( ch ) ) return NUM;
	if( std::isspace( ch ) || issepar( ch ) ) return SEPAR;
	if( std::ispunct( ch ) ) return OPER;

	return ret_err( "Unknown char type for: ->" + std::string( 1, ch ) + "<- id[" + std::to_string( ch ) + "]", -1, line, col );
}

static inline bool issepar( const char ch )
{
	return Core::LocInVec( SeparChars, ch ) >= 0;
}

static int GetDataType( const std::string & data, const int approx_type, const int line, const int col )
{
	int loc = -1;
	if( approx_type == NUM ) {
		int dot_count = std::count( data.begin(), data.end(), '.' );
		if( dot_count > 0 ) {
			if( dot_count > 1 ) return ret_err( "Too many decimals in " + data, -1, line, col );
			return FLT;
		}
		return INT;
	}
	if( approx_type == OPER ) {
		loc = Core::LocInVec( LogicStrs, data );
		if( loc >= 0 ) return LOGIC;
		loc = Core::LocInVec( ArithStrs, data );
		if( loc >= 0 ) return ARITH;
	}
	loc = Core::LocInVec( KeywStrs, data );
	if( loc >= 0 ) return KEYW;
	if( approx_type == OPER ) return ret_err( "Unknown operator: " + data, -1, line, col );
	// Since only string is left, return IDEN
	return IDEN;
}

static int GetDetailType( const std::string & data, const int type, const int line, const int col )
{
	if( type == LOGIC ) {
		return Core::LocInVec( LogicStrs, data );
	}
	if( type == ARITH ) {
		return Core::LocInVec( ArithStrs, data );
	}
	if( type == SEPAR ) {
		return Core::LocInVec( SeparChars, data[ 0 ] );
	}
	if( type == KEYW ) {
		return Core::LocInVec( KeywStrs, data );
	}
	return -1;
}

// Sym class

Lex::Sym::Sym( const SymType type, const int detail_type, const std::string & data, const int line, const int col ) :
	m_type( type ), m_data( data ), m_detail_type( detail_type ), m_line( line ), m_col( col )
{}

SymType Lex::Sym::GetType() const
{
	return m_type;
}

const std::string & Lex::Sym::GetData() const
{
	return m_data;
}

int Lex::Sym::GetDetailType() const
{
	return m_detail_type;
}

int Lex::Sym::GetLine() const
{
	return m_line;
}

int Lex::Sym::GetCol() const
{
	return m_col;
}

// Syms class

Lex::Syms::Syms() {}

Lex::Syms::Syms( Syms && original ) : Syms()
{
	swap( * this, original );
}

Lex::Syms::Syms( Syms & original ) : m_syms( original.m_syms )
{
	for( auto & sym : original.m_syms ) sym = nullptr;
}

Syms & Lex::Syms::operator =( Syms original )
{
	swap( * this, original );
	return * this;

}

// friend function
void Lex::swap( Syms & sym1, Syms & sym2 )
{
	using std::swap;
	swap( sym1.m_syms, sym2.m_syms );
}

Sym * Lex::Syms::operator []( const size_t loc )
{
	return m_syms[ loc ];
}

void Lex::Syms::push_back( Sym * const sym )
{
	m_syms.push_back( sym );
}

void Lex::Syms::pop_back()
{
	if( m_syms.empty() ) return;
	delete * ( m_syms.end() - 1 );
	m_syms.pop_back();
}

size_t Lex::Syms::size() const
{
	return m_syms.size();
}

// iteration
const std::vector< Sym * > & Lex::Syms::GetSyms() const
{
	return m_syms;
}

Lex::Syms::~Syms()
{
	for( auto & sym : m_syms ) {
		if( sym != nullptr ) delete sym;
	}
}

#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>

#include "DataTypes.hpp"

namespace Lexer
{
	std::vector< DataType::Data >
	ParseLexicoSymbols( const std::string & line );
}

#endif // LEXER_HPP

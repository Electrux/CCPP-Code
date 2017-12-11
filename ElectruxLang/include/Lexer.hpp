#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>

#include "DataTypes.hpp"

namespace Lexer
{
	std::vector< DataType::Data >
	ParseLexicoSymbols( const std::vector< std::string > & lineparts );
}

#endif // LEXER_HPP

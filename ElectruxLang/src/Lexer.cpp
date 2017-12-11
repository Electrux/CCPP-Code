#include <iostream>
#include <string>
#include <vector>

#include "../include/DataTypes.hpp"

#include "../include/Lexer.hpp"

namespace Lexer
{
	static bool VectorExists( const std::vector< std::string > & vec,
				  const std::string & key )
	{
		if( std::find( vec.begin(), vec.end(), key ) != vec.end() )
			return true;
		return false;
	}

	static void SpecifySymbol( DataType::Data & d )
	{
		if( d.type == DataType::STRING ) {

			if( VectorExists( DataType::KEYWORDS_STR, d.word ) )
				d.type = DataType::KEYWORD;
			else
				d.type = DataType::IDENTIFIER;
		}
		else if( d.type == DataType::LOGICAL ) {

			if( VectorExists( DataType::LOGICAL_OPERATORS_STR, d.word ) )
				d.type = DataType::LOGICAL;
			else
				d.type = DataType::INVALID;
		}
		else if( d.type == DataType::OPERATOR ) {

			if( VectorExists( DataType::OPERATORS_STR, d.word ) )
				d.type = DataType::OPERATOR;

			else if( VectorExists( DataType::SEPARATORS_STR, d.word ) )
				d.type = DataType::SEPARATOR;
			else
				d.type = DataType::INVALID;
		}
	}

	std::vector< DataType::Data >
	ParseLexicoSymbols( const std::vector< std::string > & lineparts )
	{
		std::vector< DataType::Data > dataline;

		for( auto data : lineparts ) {

			DataType::Data d = { DataType::GetDataType( data ), data };
			SpecifySymbol( d );
			dataline.push_back( d );

			std::cout << "(" << DataType::SYMBOL_STR[ d.type ]
				  << ", " << d.word << ") ";
		}

		std::cout << std::endl;

		return dataline;
	}
}

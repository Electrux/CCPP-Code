#include <iostream>
#include <string>
#include <vector>

#include "../include/StringFuncs.hpp"
#include "../include/DataTypes.hpp"

#include "../include/Lexer.hpp"

namespace Lexer
{
	static int VectorFind( const std::vector< std::string > & vec,
			       const std::string & key )
	{
		int loc = -1;
		for( int i = 0; i < ( int )vec.size(); ++i ) {
			if( vec[ i ] == key ) {
				loc = i;
				break;
			}
		}
		return loc;
	}

	static void SetDetailType( DataType::Data & d )
	{
		if( d.type == DataType::STRING ) {

			int loc = VectorFind( DataType::KEYWORDS_STR, d.word );

			if( loc != -1 ) {
				d.type = DataType::KEYWORD;
				d.detailtype = loc;
			}
			else {
				d.type = DataType::IDENTIFIER;
				d.detailtype = -1;
			}
		}
		else if( d.type == DataType::LOGICAL ) {

			int loc = VectorFind( DataType::LOGICAL_OPERATORS_STR, d.word );

			if( loc != -1 ) {
				d.type = DataType::LOGICAL;
				d.detailtype = loc;
			}
			else {
				d.type = DataType::INVALID;
				d.detailtype = -1;
			}
		}
		else if( d.type == DataType::OPERATOR || d.type == DataType::SEPARATOR ) {

			int loc = VectorFind( DataType::OPERATORS_STR, d.word );

			if( loc != -1 ) {
				d.type = DataType::OPERATOR;
				d.detailtype = loc;
			}
			else {
				loc = VectorFind( DataType::SEPARATORS_STR, d.word );
				if( loc != -1 ) {

					d.type = DataType::SEPARATOR;
					d.detailtype = loc;
				}
				else {
					d.type = DataType::INVALID;
					d.detailtype = -1;
				}
			}
		}
		else {
			d.detailtype = -1;
		}
	}

	std::string GetDetailType( DataType::Data & d )
	{
		if( d.type == DataType::KEYWORD ) {

			return DataType::KEYWORDS_STR[ d.detailtype ];
		}
		if( d.type == DataType::OPERATOR ) {

			return DataType::OPERATORS_STR[ d.detailtype ];
		}
		if( d.type == DataType::LOGICAL ) {

			return DataType::LOGICAL_OPERATORS_STR[ d.detailtype ];
		}
		if( d.type == DataType::SEPARATOR ) {
			return DataType::SEPARATORS_STR[ d.detailtype ];
		}

		return "none";
	}

	std::vector< DataType::Data >
	ParseLexicoSymbols( const std::string & line )
	{
		std::vector< DataType::Data > dataline;

		auto lineparts = DelimitString( line );

		int indent = GetIndentLevel( line );

		DataType::Data dat;

		dat.type = DataType::SEPARATOR;
		dat.word = "\t";

		SetDetailType( dat );

		dataline.push_back( dat );
		std::cout << "(" << DataType::SYMBOL_STR[ DataType::SEPARATOR ]
			  << ", " << dat.detailtype
			  << ", " << std::to_string( indent ) << ") ";

		for( auto data : lineparts ) {

			DataType::Data d = { DataType::GetDataType( data ), -1, data };
			SetDetailType( d );
			dataline.push_back( d );

			if( d.detailtype == -1 )
				std::cout << "(" << DataType::SYMBOL_STR[ d.type ]
					  << ", " << d.word << ") ";
			else
				std::cout << "(" << DataType::SYMBOL_STR[ d.type ]
					  << ", " << d.detailtype << ") ";
		}

		std::cout << std::endl;

		return dataline;
	}
}

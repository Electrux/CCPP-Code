#include <iostream>
#include <vector>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/Vars.hpp"
#include "../../include/LineTypeHandler/Print.hpp"

#include "../../include/LineTypeHandler/Input.hpp"

ErrorTypes ExecuteInput( const std::vector< DataType::Data > & line, DataType::Data & var )
{
	int from = 0;
	for( auto data : line ) {
		if( data.type == DataType::KEYWORD && data.detailtype == DataType::SCAN ) {
			break;
		}
		from++;
	}

	var.type = DataType::INVALID;
	var.word = "__E_R_R_O_R__";

	if( line.size() - from < 1 ) {
		std::cout << from << std::endl;
		std::cerr << "Error on line: " << line[ 0 ].fileline << ": Format for input - fetch" << std::endl;
		return SYNTAX_ERROR;
	}

	std::string input;
	std::getline( std::cin, input );

	if( * ( input.end() - 1 ) == '\n' || * ( input.end() - 1 ) == '\t' )
		input.erase( input.end() - 1 );

	var.type = DataType::GetDataType( input );
	if( var.type == DataType::INVALID ) {
		std::cerr << "Error: Unable to classify read data!" << std::endl;
		return INPUT_FAILURE;
	}
	var.detailtype = -1;
	var.fileline = line[ 0 ].fileline;
	var.indent = line[ 0 ].indent;
	var.word = input;

	return SUCCESS;
}
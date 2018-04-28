#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/Vars.hpp"
#include "../../include/ExpressionEvaluator.hpp"

#include "../../include/LineTypeHandler/Environment.hpp"

ErrorTypes ExecuteSetEnv( const std::vector< DataType::Data > & dataline )
{
	if( dataline.size() < 4 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Syntax for setenv is - setenv < variable > = < value >"
			<< std::endl;
		return SYNTAX_ERROR;
	}

	int loc = 0;
	for( auto data : dataline ) {
		if( data.type == DataType::OPERATOR && data.detailtype == DataType::ASSIGN ) {
			break;
		}

		loc++;
	}

	if( loc >= dataline.size() - 1 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": No value is given to assign to the variable in setenv.\n"
			<< "\tThe syntax for setenv is - setenv < variable > = < value >" << std::endl;
		return SYNTAX_ERROR;
	}

	Variable var;
	auto errvar = EvalExpression( dataline, 2, loc - 1, var );

	if( errvar != SUCCESS ) {
		return SYNTAX_ERROR;
	}

	Variable val;
	auto errval = EvalExpression( dataline, loc + 1, dataline.size() - 1, val );

	if( errval != SUCCESS ) {
		return SYNTAX_ERROR;
	}

	auto err = setenv( var.data.c_str(), val.data.c_str(), 1 );

	if( err != 0 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Unable to modify/add env variable: " << var.data << "!"
			<< " System returned error: " << err << std::endl;
		return SYSTEM_FAILURE;
	}

	return SUCCESS;
}

ErrorTypes ExecuteGetEnv( const std::vector< DataType::Data > & dataline, DataType::Data & result )
{
	if( dataline.size() < 3 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Syntax for setenv is - getenv < variable >"
			<< std::endl;
		return SYNTAX_ERROR;
	}

	Variable var;
	auto errvar = EvalExpression( dataline, 2, dataline.size() - 1, var );

	if( errvar != SUCCESS ) {
		return SYNTAX_ERROR;
	}

	std::string val = std::string( getenv( var.data.c_str() ) );

	result.type = DataType::GetDataType( val );

	if( result.type == DataType::INVALID )
		result.type = DataType::STRING;

	result.detailtype = -1;
	result.fileline = dataline[ 0 ].fileline;
	result.indent = dataline[ 0 ].indent;
	result.word = val;

	return SUCCESS;
}

ErrorTypes ExecuteExecCommand( const std::vector< DataType::Data > & dataline, DataType::Data & result )
{
	if( dataline.size() < 3 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Syntax for setenv is - exec < command >"
			<< std::endl;
		return SYNTAX_ERROR;
	}

	Variable var;
	auto errvar = EvalExpression( dataline, 2, dataline.size() - 1, var );

	if( errvar != SUCCESS ) {
		return SYNTAX_ERROR;
	}

	std::string val = std::to_string( std::system( var.data.c_str() ) );

	result.type = DataType::GetDataType( val );

	if( result.type == DataType::INVALID )
		result.type = DataType::NUM;

	result.detailtype = -1;
	result.fileline = dataline[ 0 ].fileline;
	result.indent = dataline[ 0 ].indent;
	result.word = val;

	return SUCCESS;
}
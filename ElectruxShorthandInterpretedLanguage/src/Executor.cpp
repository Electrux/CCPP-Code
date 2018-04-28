#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../include/Errors.hpp"
#include "../include/DataTypes.hpp"
#include "../include/Vars.hpp"
#include "../include/Functions.hpp"
#include "../include/LineTypeIncs.hpp"

#include "../include/Executor.hpp"

ErrorTypes ExecuteAll( const std::vector< std::vector< DataType::Data > > & alldata )
{
	ErrorTypes err = ErrorTypes::SUCCESS;

	for( int i = 0; i < ( int )alldata.size(); ++i ) {
		if( ( err = ExecuteStatement( alldata, i ) ) != SUCCESS )
			return err;
	}

	return SUCCESS;
}

ErrorTypes ExecuteStatement( const std::vector< std::vector< DataType::Data > > & alldata, int & line )
{
	ErrorTypes err = SUCCESS;

	// There is index 1 element in each line because the first element is tab count.
	if( alldata[ line ].size() < 2 )
		return err;

	if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::PRINT ) {
		err = ExecutePrint( alldata[ line ] );
	}
	else if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::VAR ) {
		err = HandleVar( alldata, line );
	}
	else if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::FN ) {
		err = Function::LoadFunction( alldata, line );
	}
	else if( alldata[ line ].size() > 2 && alldata[ line ][ 1 ].type == DataType::IDENTIFIER &&
		alldata[ line ][ 2 ].type == DataType::SEPARATOR && alldata[ line ][ 2 ].detailtype == DataType::PARENTHESISOPEN ) {

		auto func = Function::GetSingleton( alldata[ line ][ 1 ].word );
		if( func == nullptr ) {
			std::cerr << "Error on line: " << alldata[ line ][ 0 ].fileline << ": No function named: "
				<< alldata[ line ][ 1 ].word << " exists!" << std::endl;
			return ENTITY_NOT_FOUND;
		}
		std::vector< DataType::Data > argnames;
		Function::GetArgs( alldata[ line ], argnames );
		err = func->ExecuteFunction( argnames, alldata[ line ][ 0 ].fileline );
	}
	else if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::RETURN ) {
		err = ExecuteReturn( alldata[ line ] );
	}
	else if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::LOAD ) {
		err = LoadModule( alldata[ line ] );
	}
	else if( alldata[ line ][ 1 ].type == DataType::KEYWORD && alldata[ line ][ 1 ].detailtype == DataType::SETENV ) {
		err = ExecuteSetEnv( alldata[ line ] );
	}
	else if( alldata[ line ][ 1 ].type == DataType::IDENTIFIER ) {
		err = ExecuteGeneral( alldata[ line ] );
	}

	return err;
}

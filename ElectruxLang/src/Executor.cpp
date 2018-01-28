#include <string>
#include <vector>
#include <map>

#include "../include/Errors.hpp"
#include "../include/DataTypes.hpp"
#include "../include/Vars.hpp"

#include "../include/Executor.hpp"

static int currentline = 0;

ErrorTypes ExecuteAll( const std::vector< std::vector< DataType::Data > > & alldata )
{
	ErrorTypes err = ErrorTypes::SUCCESS;
	auto v = Vars::GetSingleton( "global" );
	std::map< std::string, int > vardeclline;

	for( int i = 0; i < alldata.size(); ++i ) {
		// TODO
		//if( ( err = ValidateStatement( alldata[ i ], v, vardeclline, i ) ) != SUCCESS )
			return err;

		++currentline;
	}

	Vars::DelSingleton( "global" );
}

ErrorTypes ExecuteStatement( const std::vector< std::vector< DataType::Data > > & alldata, const int & line,
			std::map< std::string, int > & vardeclline )
{
	// Use index 1 element in each line because the first element is tab count.
	if( alldata[ line ].size() < 2 )
		return ErrorTypes::SUCCESS;

	if( alldata[ line ][ 1 ].type == DataType::VAR ) {

	}

	return SUCCESS;
}
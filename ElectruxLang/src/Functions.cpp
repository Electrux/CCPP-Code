#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../include/Errors.hpp"
#include "../include/GlobalData.hpp"
#include "../include/Vars.hpp"
#include "../include/DataTypes.hpp"
#include "../include/Executor.hpp"

#include "../include/Functions.hpp"

Function::Function()
{
}

Function::~Function()
{
	Vars::DelSingleton( "fn_" + name );
	args = nullptr;
}

Function * Function::GetSingleton( const std::string & fnname )
{
	if( allfuncs.find( fnname ) != allfuncs.end() )
		return allfuncs[ fnname ];

	allfuncs[ fnname ] = new Function;
	allfuncs[ fnname ]->name = fnname;

	allfuncs[ fnname ]->args = Vars::GetSingleton( "fn_" + fnname );

	return allfuncs[ fnname ];
}

ErrorTypes Function::LoadFunction( const std::vector< std::vector< DataType::Data > > & alldata, int & startline )
{
	int indent = alldata[ startline ][ 0 ].indent;
	int currentfileline = alldata[ startline ][ 0 ].fileline;

	if( alldata[ startline ].size() < 6 ) {
		std::cerr << "Error at line: " << currentfileline << ": Function definition must have the syntax:\n"
			<< "\tfn < name >( < args > ) :" << std::endl;
		return SYNTAX_ERROR;
	}

	if( alldata[ startline ][ 2 ].type != DataType::IDENTIFIER ) {
		std::cerr << "Error at line: " << currentfileline << ": Must specify a function name of type: identifier!" << std::endl;
		return SYNTAX_ERROR;
	}

	// Create function instance using the function name.
	auto fn = GetSingleton( alldata[ startline ][ 2 ].word );

	int args = GetArgCount( alldata[ startline ] );

	//SetArgs

	if( args == -1 ) {
		std::cerr << "Error in function definition parenthesis syntax at line: " << currentfileline << "!" << std::endl;
		return SYNTAX_ERROR;
	}

	int i = startline + 1;
	while( i < alldata.size() && alldata[ i ][ 0 ].indent > indent ) {
		fn->lines.push_back( alldata[ i ] );
		++i;
	}

	if( fn->lines.empty() ) {
		std::cerr << "Error at line: " << currentfileline << ": No definition for the function provided!" << std::endl;
		return SYNTAX_ERROR;
	}

	startline += fn->lines.size();

	return SUCCESS;
}

ErrorTypes Function::ExecuteFunction()
{
	ErrorTypes err = SUCCESS;

	SetCurrentFunction( "fn_" + name );
	if( ( err = ExecuteAll( lines ) ) != SUCCESS )
		return err;

	RemoveLastFunction();
	return err;
}

bool Function::DelSingleton( const std::string & fnname )
{
	if( allfuncs.find( fnname ) == allfuncs.end() )
		return false;

	delete allfuncs[ fnname ];
	allfuncs.erase( fnname );

	return true;
}

int GetArgCount( const std::vector< DataType::Data > & dataline )
{
	int i = 0;

	int bracketopenloc = -1, bracketcloseloc = -1, commacount = 0;

	// Locations of brackets, and count of commas.
	for( auto data : dataline ) {
		if( data.type == DataType::SEPARATOR && data.detailtype == DataType::PARENTHESISOPEN )
			bracketopenloc = i;
		if( data.type == DataType::SEPARATOR && data.detailtype == DataType::PARENTHESISCLOSE )
			bracketcloseloc = i;

		if( bracketopenloc != -1 && bracketcloseloc == -1 &&
			data.type == DataType::SEPARATOR && data.detailtype == DataType::COMMA )
			++commacount;
		++i;
	}

	// Suntactic error!
	if( bracketopenloc == -1 || bracketcloseloc == -1 )
		return -1;

	if( bracketopenloc == bracketcloseloc - 1 )
		return 0;
	
	return commacount == 0 ? 1 : commacount + 1;
}
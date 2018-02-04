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
	argscount = 0;
}

Function::~Function()
{
	Vars::DelSingleton( "fn_" + name );
}

Function * Function::GetSingleton( const std::string & fnname )
{
	if( allfuncs.find( fnname ) != allfuncs.end() )
		return allfuncs[ fnname ];

	allfuncs[ fnname ] = new Function;
	allfuncs[ fnname ]->name = fnname;

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

	// Handle arguments.
	std::vector< DataType::Data > argnames;
	fn->argscount = GetArgs( alldata[ startline ], argnames );

	if( fn->argscount == -1 ) {
		std::cerr << "Error in function definition parenthesis syntax at line: " << currentfileline << "!" << std::endl;
		return SYNTAX_ERROR;
	}

	auto v = Vars::GetSingleton( "fn_" + fn->name );
	for( int i = 0; i < fn->argscount; ++i ) {
		if( argnames[ i ].type == DataType::IDENTIFIER )
			v->AddVar( std::to_string( i ), { Vars::STRING, argnames[ i ].word } );
	}

	// Add the function lines in the function itself.
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

ErrorTypes Function::ExecuteFunction( const std::vector< DataType::Data > & argnames, const int & fileline )
{
	ErrorTypes err = SUCCESS;

	if( argnames.size() < this->argscount ) {
		std::cerr << "Error at line: " << fileline << ": Too low argument count in function call! Expected: "
			<< this->argscount << ", found: " << argnames.size() << std::endl;
		return SYNTAX_ERROR;
	}

	if( argnames.size() > this->argscount ) {
		std::cerr << "Error at line: " << fileline << ": Too many argument count in function call! Expected: "
			<< this->argscount << ", found: " << argnames.size() << std::endl;
		return SYNTAX_ERROR;
	}

	auto v = Vars::GetSingleton( "fn_" + this->name );
	for( int i = 0; i < this->argscount; ++i ) {
		if( argnames[ i ].type != DataType::LITERAL ) {
			auto var = FetchVariable( argnames[ i ].word, fileline );
			if( var.data == "__E_R_R_O_R__" )
				return ENTITY_NOT_FOUND;

			v->AddVar( v->GetVar( std::to_string( i ) ).data, var );
		}
		else {
			v->AddVar( v->GetVar( std::to_string( i ) ).data, { Vars::STRING, argnames[ i ].word } );
		}
	}

	SetCurrentFunction( "fn_" + name );

	if( ( err = ExecuteAll( this->lines ) ) != SUCCESS ) {
		RemoveLastFunction();
		return err;
	}

	RemoveLastFunction();

	Variable returnvar = GetCurrentReturnValue();

	if( returnvar.vartype != Vars::INVALID ) {
		std::string space = GetCurrentFunction();

		if( space.empty() )
			space = "global";
		
		auto v = Vars::GetSingleton( space );
		v->AddVar( "fn_ret_" + this->name, returnvar );

		RemoveLastReturnValue();
	}

	return err;
}

bool Function::DelSingleton( const std::string & fnname )
{
	if( allfuncs.find( fnname ) == allfuncs.end() )
		return false;

	if( allfuncs[ fnname ] != nullptr )
		delete allfuncs[ fnname ];
	allfuncs.erase( fnname );

	Vars::DelSingleton( "fn_" + fnname );

	return true;
}

void Function::DelAllFuncs()
{
	for( auto it = allfuncs.begin(); it != allfuncs.end(); ) {
		if( it->second != nullptr )
			delete it->second;
		it = allfuncs.erase( it );
	}
}

int Function::GetArgs( const std::vector< DataType::Data > & dataline, std::vector< DataType::Data > & argnames )
{
	int i = 0;

	int bracketopenloc = -1, bracketcloseloc = -1;

	argnames.clear();

	// Locations of brackets, and count of commas.
	for( auto data : dataline ) {
		if( data.type == DataType::SEPARATOR && data.detailtype == DataType::PARENTHESISOPEN ) {
			bracketopenloc = i;
			++i;
			continue;
		}
		if( data.type == DataType::SEPARATOR && data.detailtype == DataType::PARENTHESISCLOSE ) {
			bracketcloseloc = i;
			++i;
			break;
		}

		if( bracketopenloc != -1 && bracketcloseloc == -1 ) {
			if( data.type == DataType::SEPARATOR && data.detailtype == DataType::COMMA ) {
				// Perhaps something in the future.
			}
			else {
				argnames.push_back( data );
			}
		}
		++i;
	}

	// Suntactic error!
	if( bracketopenloc == -1 || bracketcloseloc == -1 )
		return -1;

	if( bracketopenloc == bracketcloseloc - 1 )
		return 0;
	
	return argnames.size();
}
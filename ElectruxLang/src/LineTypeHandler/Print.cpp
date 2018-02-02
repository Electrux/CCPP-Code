#include <iostream>
#include <string>
#include <vector>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/GlobalData.hpp"
#include "../../include/StringFuncs.hpp"
#include "../../include/Vars.hpp"

#include "../../include/LineTypeHandler/Print.hpp"

ErrorTypes ExecutePrint( const std::vector< DataType::Data > & line )
{
	std::vector< std::string > args;

	int lineinfile = line[ 0 ].fileline;

	std::string resultstring = VarToString( line[ 2 ].word, lineinfile );

	for( int i = 3; i < line.size(); ++i ) {
		if( line[ i ].type != DataType::OPERATOR && line[ i ].type != DataType::LOGICAL &&
			line[ i ].type != DataType::SEPARATOR && line[ i ].type != DataType::KEYWORD &&
			line[ i ].type != DataType::INVALID )
			args.push_back( line[ i ].word );
		else {
			std::cerr << "Error at line: " << lineinfile << "! Attempted to use illegal element as argument to "
				<< "print statement: " << line[ i ].word << "!" << std::endl;
			return SYNTAX_ERROR;
		}
	}

	if( SubstituteVars( resultstring, args, lineinfile ) == -1 )
		return ENTITY_NOT_FOUND;

	if( * resultstring.begin() == '\'' )
		resultstring.erase( resultstring.begin() );

	if( * ( resultstring.end() - 1 ) == '\'' )
		resultstring.erase( resultstring.end() - 1 );

	std::cout << resultstring;
	std::cout.flush();

	return SUCCESS;
}

int SubstituteVars( std::string & str, const std::vector< std::string > & args, const int & lineinfile )
{
	int len = 0;
	std::string var;
	int temp;

	for( std::string::iterator it = str.begin(); it != str.end(); ) {
		if( * it == '{' && it + 1 != str.end() ) {
			it = str.erase( it );
			if( * it == '{' ) {
				len++;
				++it;
				continue;
			}

			var = "";
			while( it != str.end() && * it != '}' ) {
				var += * it;
				it = str.erase( it );
			}
			it = str.erase( it );

			if( StringToInteger( var, temp ) && args.size() > temp ) {
				std::string res = VarToString( args[ temp ], lineinfile );

				if( res == "__E_R_R_O_R__" )
					return -1;

				it = str.insert( it, res.begin(), res.end() );
				it += res.size();
				len += res.size();
			}
			var.clear();
			continue;
		}

		len = * it == '\n' ? 0 : len + 1;
		++it;
	}

	return len;
}

std::string VarToString( const std::string & var, const int & lineinfile )
{
	auto dt = DataType::GetDataType( var );
	if( dt == DataType::LITERAL ) {
		std::string res = var;

		res.erase( res.begin() );
		res.erase( res.end() - 1 );

		return res;
	}
	if( dt != DataType::STRING )
		return var;

	auto v = Vars::GetSingleton( "global" );
	auto fv = Vars::GetSingleton( GetCurrentFunction() );

	if( fv != nullptr && fv->GetVar( var ).data.size() > 0 )
		return fv->GetVar( var ).data;
	else if( v != nullptr && v->GetVar( var ).data.size() > 0 )
		return v->GetVar( var ).data;

	std::cerr << "Error at line: " << lineinfile << ": Undefined variable: " << var << "!" << std::endl;
	return "__E_R_R_O_R__";
}
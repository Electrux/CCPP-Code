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

	std::string resultstring = FetchVarToString( line[ 2 ].word, lineinfile );

	bool found_index = false;
	std::string index;
	for( int i = 3; i < ( int )line.size(); ++i ) {
		index = "-1";
		if( found_index ) {
			i += 3;
			found_index = false;
			if( i == ( int )line.size() )
				break;
		}

		if( line[ i ].type != DataType::OPERATOR && line[ i ].type != DataType::LOGICAL &&
			line[ i ].type != DataType::SEPARATOR && line[ i ].type != DataType::KEYWORD &&
			line[ i ].type != DataType::INVALID ) {

			if( i != line.size() - 1 && line[ i + 1 ].type == DataType::SEPARATOR &&
				line[ i + 1 ].detailtype == DataType::CURLYBRACESOPEN ) {

				if( i + 2 == line.size() ) {
					std::cerr << "Error on line: " << lineinfile << ": No index specified for variable: "
						<< line[ i ].word << " after the curly braces opening!" << std::endl;
					return SYNTAX_ERROR;
				}

				Variable var = FetchVariable( line[ i + 2 ].word, lineinfile );
				if( var.vartype != Vars::NUM ) {
					std::cerr << "Error on line: " << lineinfile << ": Index must be a number!" << std::endl;
					return SYNTAX_ERROR;
				}

				index = var.data;
				found_index = true;

			}

			std::string arg = index == "-1" ? line[ i ].word : line[ i ].word + "{" + index + "}";
			args.push_back( arg );
		}
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

			if( StringToInteger( var, temp ) ) {
				if( ( int )args.size() > temp ) {
					std::string res = FetchVarToString( args[ temp ], lineinfile );

					RemoveTrailingQuotes( res );

					if( res == "__E_R_R_O_R__" )
						return -1;

					it = str.insert( it, res.begin(), res.end() );
					it += res.size();
					len += res.size();
				}
			}
			else {
				auto v = Vars::GetSingleton( "__self_vars__" );
				auto res = v->GetVar( var ).data;

				if( res == "\n" )
					len = 0;

				it = str.insert( it, res.begin(), res.end() );
				it += res.size();
				len += res.size();
			}
			var.clear();
			continue;
		}

		len++;
		++it;
	}

	return len;
}

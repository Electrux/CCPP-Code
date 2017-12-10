#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>

#include "../../include/Stack.hpp"

#include "../../include/LangInterpreter/LanguageInterpreter.hpp"

bool IsSymbol( std::string & data );
int GetPrecedence( std::string & symbol );
std::vector< std::string > GenPostfix( const std::vector< std::string > & _infix, int line );

int Interpreter::EvalExpression( std::vector< std::string > & lineparts,
				 int from, int line, int & result )
{
	if( from >= ( int )lineparts.size() ) {
		std::cerr << "Error at line: " << line
			  << "\n\tfrom was: " << from << " but lineparts size was: "
			  << lineparts.size() << std::endl;
		return ERR;
	}

	std::vector< std::string > infix;

	for( int i = from; i < ( int )lineparts.size(); ++i ) {
		infix.push_back( lineparts[ i ] );
	}

	std::vector< std::string > postfix = GenPostfix( infix, line );



	std::string val = GetReplacementValue( * postfix.begin(), line );

	auto type = GetType( val );
	if( type == STR && !IsSymbol( val ) ) {
		std::cerr << "Error at line: " << line
			  << "\n\tInvalid term in expression!" << std::endl;
		return ERR;
	}
	result = std::stoi( val );
	postfix.erase( postfix.begin() );

	while( !postfix.empty() ) {

		std::string data = * postfix.begin();

		if( IsSymbol( data ) ) {

			postfix.erase( postfix.begin() );

			if( postfix.empty() ) {
				std::cerr << "Error at line: " << line
					  << "\n\tExpression incomplete!" << std::endl;
				return ERR;
			}

			std::string val = GetReplacementValue( * postfix.begin(), line );

			auto type = GetType( val );
			if( type == STR && !IsSymbol( val ) ) {
				std::cerr << "Error at line: " << line
					  << "\n\tInvalid term in expression!" << std::endl;
				return ERR;
			}

			postfix.erase( postfix.begin() );

			if( data == "/" )
				result /= std::stoi( val );
			if( data == "*" )
				result *= std::stoi( val );
			if( data == "%" )
				result %= std::stoi( val );
			if( data == "+" )
				result += std::stoi( val );
			if( data == "-" )
				result -= std::stoi( val );
		}
	}

	return OK;
}

int Interpreter::EvalExpression( std::vector< std::string > & lineparts,
				 int from, int line, float & result )
{
	if( from >= ( int )lineparts.size() ) {
		std::cerr << "Error at line: " << line
			  << "\n\tfrom was: " << from << " but lineparts size was: "
			  << lineparts.size() << std::endl;
		return ERR;
	}

	std::vector< std::string > infix;

	for( int i = from; i < ( int )lineparts.size(); ++i ) {
		infix.push_back( lineparts[ i ] );
	}

	std::vector< std::string > postfix = GenPostfix( infix, line );



	std::string val = GetReplacementValue( * postfix.begin(), line );

	auto type = GetType( val );
	if( type == STR && !IsSymbol( val ) ) {
		std::cerr << "Error at line: " << line
			  << "\n\tInvalid term in expression!" << std::endl;
		return ERR;
	}
	result = std::stof( val );
	postfix.erase( postfix.begin() );

	while( !postfix.empty() ) {

		std::string data = * postfix.begin();

		if( IsSymbol( data ) ) {

			postfix.erase( postfix.begin() );

			if( postfix.empty() ) {
				std::cerr << "Error at line: " << line
					  << "\n\tExpression incomplete!" << std::endl;
				return ERR;
			}

			std::string val = GetReplacementValue( * postfix.begin(), line );

			auto type = GetType( val );
			if( type == STR && !IsSymbol( val ) ) {
				std::cerr << "Error at line: " << line
					  << "\n\tInvalid term in expression!" << std::endl;
				return ERR;
			}

			postfix.erase( postfix.begin() );

			if( data == "/" )
				result /= std::stof( val );
			if( data == "*" )
				result *= std::stof( val );
			if( data == "%" )
				result = ( int )result % std::stoi( val );
			if( data == "+" )
				result += std::stof( val );
			if( data == "-" )
				result -= std::stof( val );
		}
	}

	return OK;
}

std::vector< std::string > GenPostfix( const std::vector< std::string > & _infix, int line )
{
	std::vector< std::string > output;

	if( _infix.empty() )
		return output;

	std::vector< std::string > infix;
	std::vector< std::string > stack;

	infix.push_back( "(" );
	for( auto inf : _infix ) {
		infix.push_back( inf );
	}
	infix.push_back( ")" );

	for( auto data : infix ) {

		if( IsSymbol( data ) ) {

			if( data == "(" ) {
				stack.push_back( data );
			}
			else if( data == ")" ) {

				bool foundmatch = false;
				for( int i = stack.size() - 1; i >= 0; --i ) {

					if( stack[ i ] == "(" ) {
						foundmatch = true;
						stack.erase( stack.end() - 1 );
						break;
					}

					output.push_back( stack[ i ] );
					stack.erase( stack.end() - 1 );
				}

				if( !foundmatch ) {
					std::cerr << "Error at line: " << line
						  << "\n\tMismatch in start and end parenthesis!"
						  << std::endl;
					output.clear();
					return output;
				}
			}

			else {
				int dataprec = GetPrecedence( data );
				int stackprec = GetPrecedence( stack[ stack.size() - 1 ] );

				if( dataprec > stackprec ) {
					stack.push_back( data );
				}
				else if( dataprec == stackprec ) {
					output.push_back( * stack.erase( stack.end() - 1 ) );
					stack.push_back( data );
				}
				else {
					while( dataprec <= stackprec ) {
						output.push_back(
							* stack.erase( stack.end() - 1 ) );

						stackprec = GetPrecedence(
							stack[ stack.size() - 1 ] );
					}

					stack.push_back( data );
				}
			}
		}
		else {
			output.push_back( data );
		}
	}

	return output;
}

bool IsSymbol( std::string & data )
{
	if( data == "(" || data == ")" || data == "^" || data == "/" || data == "*" ||
	    data == "%" || data == "+" || data == "-" )
		return true;

	return false;
}

int GetPrecedence( std::string & symbol )
{
	if( symbol == "(" || symbol == ")" )
		return -1;

	if( symbol == "^" )
		return 3;

	if( symbol == "/" || symbol == "*" || symbol == "%" )
		return 2;

	if( symbol == "+" || symbol == "-" )
		return 1;

	return 0;
}

#include <iostream>
#include <vector>
#include <string>

#include "../include/DataTypes.hpp"

#include "../include/StringFuncs.hpp"

std::vector< std::string > ToVector( int argc, char ** argv )
{
	std::vector< std::string > temp;

	for( int i = 0; i < argc; ++i )
		temp.push_back( argv[ i ] );

	return temp;
}

std::vector< std::string > DelimitString( const std::string & str, char delim )
{
	std::string temp;
	std::vector< std::string > tempvec;

	bool inquote = false;

	for( auto ch = str.begin(); ch != str.end(); ++ch ) {

		// Stop reading line on comment.
		if( * ch == * DataType::KEYWORDS_STR[ DataType::LINECOMMENT ].begin() )
			break;

		// Tabs and spaces for indentation
		if( * ch == '\t' )
			continue;

		if( ( ch + 3 ) < str.end() &&
		    * ch == ' ' &&
		    * ( ch + 1 ) == ' ' &&
		    * ( ch + 2 ) == ' ' &&
		    * ( ch + 3 ) == ' ' ) {

			ch += 3;
			continue;
		}

		if( * ch == '\'' || * ch == '\"' )
			inquote = !inquote;

		if( * ch == delim && !inquote ) {

			if( !temp.empty() )
				tempvec.push_back( temp );
			temp.clear();

			continue;
		}

		// Handle separators.
		if( !inquote && ( std::find( DataType::SEPARATORS_STR.begin(),
			DataType::SEPARATORS_STR.end(), std::string( 1, * ch ) ) != DataType::SEPARATORS_STR.end() ||
			std::find( DataType::OPERATORS_STR.begin(),
			DataType::OPERATORS_STR.end(), std::string( 1, * ch ) ) != DataType::OPERATORS_STR.end() ||
			( * ch == '-' && ch + 1 != str.end() && * ( ch + 1 ) == '>' ) ) ) {

			if( * ch == '.' && ch != str.begin() && ch + 1 != str.end() &&
				( * ( ch - 1 ) == ' ' || std::isdigit( * ( ch - 1 ) ) ) && std::isdigit( * ( ch + 1 ) ) ) {
				temp += * ch;
				continue;
			}

			if( !temp.empty() )
				tempvec.push_back( temp );
			temp.clear();

			if( ( * ch == '-' && ch + 1 != str.end() && * ( ch + 1 ) == '>' ) )
				tempvec.push_back( std::string( "->" ) );
			else
				tempvec.push_back( std::string( 1, * ch ) );

			continue;
		}

		temp += * ch;
	}

	if( !temp.empty() )
		tempvec.push_back( temp );

	return tempvec;
}

std::string GetWord( const std::string & str, int loc, char delim )
{
	std::string temp;
	int ctr = 0;

	for( auto ch = str.begin(); ch != str.end(); ++ch ) {

		// Tabs and spaces for indentation
		if( *ch == '\t' )
			continue;

/*		if( ( ch + 3 ) < str.end() &&
		    * ch == ' ' &&
		    * ( ch + 1 ) == ' ' &&
		    * ( ch + 2 ) == ' ' &&
		    * ( ch + 3 ) == ' ' ) {

			ch += 3;
			continue;
		}
*/
		if( * ch == delim ) {
			if( loc == ctr )
				break;
			ctr++;
		}

		if( ctr == loc )
			temp += * ch;
	}

	return temp;
}

std::string GetStringBetweenQuotes( const std::string & str )
{
	std::string temp;

	bool startquote = false;

	for( auto ch : str ) {

		if( ch == '\"' || ch == '\'' ) {
			startquote = !startquote;
		}
		else if( startquote )
			temp += ch;
	}

	return temp;
}

int GetIndentLevel( const std::string & str )
{
	if( str.empty() )
		return 1;

	int ctr = 0;

	auto it = str.begin();

	while( *it == '\t' ) {
		ctr++;
		it++;
	}

	it = str.begin();

	if( ctr == 0 ) {

		while( *it == ' ' ) {
			ctr++;
			it++;
		}
	}

	return ctr;
}

bool StringToInteger( const std::string & str, int & val )
{
	int res;
	try {
		res = std::stoi( str );
	}
	catch( const std::invalid_argument & ia ) {
		return false;
	}

	val = res;

	return true;
}

template< typename T > std::string VectorToString( const std::vector< T > & vec )
{
	if( vec.size() < 1 )
		return "";

	return VectorToString< T >( vec );
}

template <> std::string VectorToString< std::string >( const std::vector< std::string > & vec )
{
	std::string temp;
	temp += "[ ";
	for( int i = 0; i < vec.size(); ++i ) {
		temp += "\'" + vec[ i ] + "\'";
		if( i != vec.size() - 1 )
			temp += ", ";
	}
	temp += " ]";

	return temp;
}

template <> std::string VectorToString< int >( const std::vector< int > & vec )
{
	std::string temp;
	temp += "[ ";
	for( int i = 0; i < vec.size(); ++i ) {
		temp +=  "\'" + std::to_string( vec[ i ] ) + "\'";
		if( i != vec.size() - 1 )
			temp += ", ";
	}
	temp += " ]";

	return temp;
}

template <> std::string VectorToString< float >( const std::vector< float > & vec )
{
	std::string temp;
	temp += "[ ";
	for( int i = 0; i < vec.size(); ++i ) {
		temp +=  "\'" + std::to_string( vec[ i ] ) + "\'";
		if( i != vec.size() - 1 )
			temp += ", ";
	}
	temp += " ]";

	return temp;
}

void ReplaceInString( std::string & str, const std::string & from, const std::vector< std::string > & to )
{
	for( auto individualto : to )
		ReplaceInString( str, from, individualto );
}

void ReplaceInString( std::string & str, const std::string & from, const std::string & to )
{
	size_t n = 0;

	while( ( n = str.find( from, n ) ) != std::string::npos ) {
		str.replace( n, from.size(), to );

		n += to.size();
	}
}
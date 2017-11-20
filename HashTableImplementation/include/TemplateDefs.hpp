//
// Created by Electrux Redsworth on 9/12/17.
//

#ifndef HASHTABLEIMPLEMENTATION_TEMPLATEDEFS_HPP_HPP
#define HASHTABLEIMPLEMENTATION_TEMPLATEDEFS_HPP_HPP

#include <string>
#include <climits>

namespace Electrux
{
	template < typename T >
	int GetHash( T &obj )
	{
		return GetHash( obj );
	}

	template <>
	int GetHash<std::string> ( std::string &obj )
	{
		int temp = 0;

		for( auto ch : obj )
			temp += ( int ) ch;

		return temp;
	}

	template <>
	int GetHash< int > ( int &obj )
	{
		return obj;
	}

	template <>
	int GetHash< unsigned int > ( unsigned int &obj )
	{
		return obj % INT_MAX;
	}

	template <>
	int GetHash< char > ( char &obj )
	{
		return (int)obj;
	}

	template <>
	int GetHash< unsigned char > ( unsigned char &obj )
	{
		return obj;
	}

	template <>
	int GetHash< long long > ( long long &obj )
	{
		return ( int )( obj % INT_MAX );
	}

	template <>
	int GetHash< unsigned long long > ( unsigned long long &obj )
	{
		return ( int )( obj % INT_MAX );
	}

	template <>
	int GetHash< double > ( double &obj )
	{
		return ( int )obj;
	}

}

#endif //HASHTABLEIMPLEMENTATION_TEMPLATEDEFS_HPP_HPP

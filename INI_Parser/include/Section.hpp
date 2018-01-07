//
// Created by electrux on 7/25/17.
//

#ifndef INI_PARSER_SECTION_HPP
#define INI_PARSER_SECTION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "DataVars.hpp"

namespace Electrux
{
	// The data will store key and its value, and
	// smart pointers previous and next are used to cycle through all of the key value pairs.
	struct Data
	{
		std::string key;
		std::string val;
		
		std::shared_ptr<Data> prev, next;
	};

	// Section is the class which manages all the key value pairs ( data ) for each section,
	// aknowledged by section name.
	class Section
	{
		std::map< std::string, std::string > data;
	
	public:
		
		STATUS_CODES SetData( const std::string &key, const std::string &val );
		
		STATUS_CODES UpdateData( const std::string &key, const std::string &val );
		
		STATUS_CODES DeleteData( const std::string &key );
		
		STATUS_CODES GetData( const std::string &key, std::string &store_location );
		
		size_t GetSize();
		
		std::map< std::string, std::string > &GetAllData();
		
		void DisplayAll();
	};
}

#endif //INI_PARSER_SECTION_HPP

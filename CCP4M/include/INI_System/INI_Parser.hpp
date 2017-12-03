//
// Created by electrux on 7/25/17.
//

#ifndef INI_PARSER_INI_PARSER_HPP
#define INI_PARSER_INI_PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include "DataVars.hpp"
#include "Section.hpp"

namespace Electrux
{
	class INI_Parser
	{
		// Map to store all the sections.
		std::map< std::string, std::shared_ptr< Section > > sections;
		
		// Variable to store the error mode. Either Throw exception ( and terminate ),
		// just show on the std::cerr output.
		FATAL_ERROR_MODES err_mode;
		
		// Variables to store the last status code returned by the function,
		// and the function itself which called that return.
		STATUS_CODES last_code;
		std::string last_func;
		
		// Check if the line contains a section. If so, fetch the section.
		bool GetSectionFromLine( const std::string &line, std::string &section );
		
		// Break a line into key and value pair ( This will omit spaces as well ).
		bool GetKeyValPairFromString( const std::string &str,
					      std::string &key,
					      std::string &val );
		
		// Check if the opened file is empty.
		bool IsFileEmpty( std::ifstream &file );
		
		// Sets the last status code to be used in case something goes wrong.
		// Returns the same error code as parameter so that it can be used in
		// return statements.
		STATUS_CODES SetLastStatusCode( STATUS_CODES code,
						const std::string &curr_func_name );
		
	public:
		
		// Custom default constructor.
		INI_Parser();
		
		// Load INI from a file.
		STATUS_CODES LoadFromFile( const std::string &filename );
		
		// Saves INI to a file.
		STATUS_CODES SaveToFile( const std::string &filename );
		
		// Create a new INI section.
		STATUS_CODES CreateSection( const std::string &section );
		
		// Delete already existing section.
		STATUS_CODES DeleteSection( const std::string &section );
		
		// Check if the given section exists.
		bool SectionExists( const std::string &section );
		
		// Insert new data { String, Int, Float }.
		STATUS_CODES SetDataString( const std::string &section,
					    const std::string &key,
					    const std::string &val );
		STATUS_CODES SetDataInt( const std::string &section,
					 const std::string &key,
					 const int &val );
		STATUS_CODES SetDataFloat( const std::string &section,
					   const std::string &key,
					   const float &val );
		
		// Update already existing data { String, Int, Float }.
		STATUS_CODES UpdateDataString( const std::string &section,
					       const std::string &key,
					       const std::string &val );
		STATUS_CODES UpdateDataInt( const std::string &section,
					    const std::string &key,
					    const int &val );
		STATUS_CODES UpdateDataFloat( const std::string &section,
					      const std::string &key,
					      const float &val );
		
		// Delete already existing data.
		STATUS_CODES DeleteData( const std::string &section, const std::string &key );
		
		// Fetch already existing data { String, Int, Float }.
		STATUS_CODES GetDataString( const std::string &section,
					    const std::string &key,
					    std::string &store_location );
		STATUS_CODES GetDataInt( const std::string &section,
					 const std::string &key,
					 int &store_location );
		STATUS_CODES GetDataFloat( const std::string &section,
					   const std::string &key,
					   float &store_location );
		
		// Retrieve last occured error as string or its code, or display it.
		// Prefer using Display because it automatically prints to std::cerr if
		// the status is not success/none.
		std::string GetLastStatusString();
		std::string GetLastStatusCodeString();
		STATUS_CODES GetLastStatusCode();
		std::string GetLastFunction();
		void DisplayLastStatusString();
		
		// Get section count.
		size_t Size();
		
		// Set the Fatal error mode to either throw exception or to
		// simply output in std::cerr without terminating the program.
		void SetFatalErrorMode( FATAL_ERROR_MODES mode );
		
		void DisplayAll();
	};
}

#endif //INI_PARSER_INI_PARSER_HPP

//
// Created by electrux on 7/25/17.
//

#include "../include/INI_Parser.hpp"

namespace Electrux
{
	//******************PRIVATE FUNCTIONS*****************//
	
	bool INI_Parser::GetSectionFromLine( const std::string &line, std::string &section )
	{
		if( *line.begin() == '[' && *( line.end() - 1 ) == ']' )
		{
			section = line.substr( 1, line.find( ']' ) - 1 );
			
			return true;
		}

		return false;
	}
	
	bool INI_Parser::GetKeyValPairFromString( const std::string &str,
						  std::string &key,
						  std::string &val )
	{
		key.clear();
		val.clear();

		if( str.find( '=' ) == std::string::npos )
			return false;

		if( str.find( '[' ) != std::string::npos ||
		    str.find( ']' ) != std::string::npos )
			return false;

		if( * str.begin() == '#' )
			return false;

		bool found_equals = false;

		bool found_quote = false;
		char quote_type;

		for( auto ch : str )
		{
			if( ch == ' ' && !found_quote )
				continue;

			if( ch == '\'' || ch == '\"' ) {
				if( found_quote && quote_type == ch ) {
					found_quote = !found_quote;
					continue;
				}
				else if( !found_quote ) {
					found_quote = !found_quote;
					quote_type = ch;
					continue;
				}
			}

			if( ch == '=' && !found_equals )
				found_equals = true;
			else
				(found_equals) ? val += ch : key += ch;
		}

		return true;
	}
	
	bool INI_Parser::IsFileEmpty( std::ifstream &file )
	{
		return file.peek() == std::ifstream::traits_type::eof();
	}
	
	// Sets the last status code to be used in case something goes wrong.
	// Returns the same error code as parameter so that it can be used in return statements.
	STATUS_CODES INI_Parser::SetLastStatusCode( STATUS_CODES code,
						    const std::string &curr_func_name )
	{
		this->last_code     =   code;
		this->last_func     =   curr_func_name;

		return this->last_code;
	}


	//******************PUBLIC FUNCTIONS******************//

	INI_Parser::INI_Parser()
	{
		err_mode = THROW_EXCEPTION;

		last_code = NONE;
	}

	// Load INI from a file.
	STATUS_CODES INI_Parser::LoadFromFile( const std::string &filename )
	{
		std::ifstream file;

		file.open( filename );

		if ( !file )
			return this->SetLastStatusCode( FILE_NOT_FOUND,
							"Electrux::INI_Parser::LoadFromFile()" );
		
		if ( this->IsFileEmpty(file) )
		{
			file.close();

			return this->SetLastStatusCode( EMPTY_FILE,
							"Electrux::INI_Parser::LoadFromFile()" );
		}

		this->sections.clear();

		std::string line;
		std::string section;

		int section_count = 0;

		bool gotsection = false, sectionexists = false;

		std::string key, val;

		while (std::getline(file, line))
		{
			gotsection = this->GetSectionFromLine(line, section);

			if( gotsection )
			{
				section_count++;
				sectionexists = this->SectionExists(section);
				if (!sectionexists)
					this->CreateSection(section);
			}

			if ( !section.empty() )
			{
				if (this->GetKeyValPairFromString(line, key, val))
					this->SetDataString(section, key, val);
			}
		}

		file.close();

		if( section_count < 1 )
			return this->SetLastStatusCode( NO_SECTION_EXISTS_IN_FILE,
							"Electrux::INI_Parser::LoadFromFile()" );

		return this->SetLastStatusCode( SUCCESS,
						"Electrux::INI_Parser::LoadFromFile()" );
	}

	// Save INI to a file.
	STATUS_CODES INI_Parser::SaveToFile( const std::string &filename )
	{
		std::fstream file;
		file.open(filename, std::ios::out);

		if( !file )
			return this->SetLastStatusCode( FILE_NOT_OPEN_FOR_WRITE,
							"Electrux::INI_Parser::SaveToFile()" );

		if( sections.empty() )
		{
			file.close();
			return this->SetLastStatusCode( NO_SECTION_EXISTS_IN_PARSER,
							"Electrux::INI_Parser::SaveToFile()" );
		}

		for( auto section : sections )
		{
			file << "[" << section.first << "]\n\n";

			for(auto data : section.second->GetAllData() )
				file << data.first << " = " << data.second << "\n";

			file << "\n";
		}

		file.close();

		return this->SetLastStatusCode( SUCCESS, "Electrux::INI_Parser::SaveToFile()" );
		
	}

	// Create a new INI section.
	STATUS_CODES INI_Parser::CreateSection( const std::string &section )
	{
		if( this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_ALREADY_EXISTS,
							"Electrux::INI_Parser::CreateSection()" );

		sections[ section ] = std::make_shared< Section >();

		return this->SetLastStatusCode( SUCCESS,
						"Electrux::INI_Parser::CreateSection()" );
	}

	// Delete already existing section.
	STATUS_CODES INI_Parser::DeleteSection( const std::string &section )
	{
		if( !this->SectionExists( section ))
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::DeleteSection()" );

		// Automatically calls shared_ptr< ... >::reset() to deallocate the memory.
		sections.erase( section );

		return this->SetLastStatusCode( SUCCESS,
						"Electrux::INI_Parser::DeleteSection()" );
	}

	// Check if the given section exists.
	bool INI_Parser::SectionExists( const std::string &section )
	{
		return ( sections.find( section ) != sections.end() );
	}

	// Insert new data { String, Int, Float }.
	STATUS_CODES INI_Parser::SetDataString( const std::string &section,
						const std::string &key,
						const std::string &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::SetDataString()" );

		STATUS_CODES lastcode = sections[ section ]->SetData( key, val );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::SetDataString()" );
	}

	STATUS_CODES INI_Parser::SetDataInt( const std::string &section,
					     const std::string &key,
					     const int &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::SetDataInt()" );

		STATUS_CODES lastcode =
			sections[ section ]->SetData( key, std::to_string( val ) );

		return this->SetLastStatusCode( lastcode, "Electrux::INI_Parser::SetDataInt()" );
	}

	STATUS_CODES INI_Parser::SetDataFloat( const std::string &section,
					       const std::string &key,
					       const float &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::SetDataFloat()" );

		STATUS_CODES lastcode =
			sections[ section ]->SetData( key, std::to_string( val ) );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::SetDataFloat()" );
	}

	// Update already existing data { String, Int, Float }.
	STATUS_CODES INI_Parser::UpdateDataString( const std::string &section,
						   const std::string &key,
						   const std::string &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::UpdateDataString()" );

		STATUS_CODES lastcode = sections[ section ]->UpdateData( key, val );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::UpdateDataString()" );
	}

	STATUS_CODES INI_Parser::UpdateDataInt( const std::string &section,
						const std::string &key,
						const int &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::UpdateDataInt()" );

		STATUS_CODES lastcode =
			sections[ section ]->UpdateData( key, std::to_string( val ) );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::UpdateDataInt()" );
	}

	STATUS_CODES INI_Parser::UpdateDataFloat( const std::string &section,
						  const std::string &key,
						  const float &val )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::UpdateDataFloat()" );

		STATUS_CODES lastcode =
			sections[ section ]->UpdateData( key, std::to_string( val ) );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::UpdateDataFloat()" );
	}

	// Delete already existing data.
	STATUS_CODES INI_Parser::DeleteData( const std::string &section, const std::string &key )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::DeleteData()" );

		STATUS_CODES lastcode = sections[ section ]->DeleteData( key );

		if( sections[ section ]->GetSize() < 1 )
		{
			this->DeleteSection( section );
			lastcode = SECTION_REMOVED_NO_DATA;
		}

		return this->SetLastStatusCode( lastcode, "Electrux::INI_Parser::DeleteData()" );
	}

	// Fetch already existing data { String, Int, Float }.
	STATUS_CODES INI_Parser::GetDataString( const std::string &section,
						const std::string &key,
						std::string &store_location )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::GetDataString()" );

		STATUS_CODES lastcode = sections[ section ]->GetData(key, store_location );

		return this->SetLastStatusCode( lastcode,
						"Electrux::INI_Parser::GetDataString()" );
	}

	STATUS_CODES INI_Parser::GetDataInt( const std::string &section,
					     const std::string &key,
					     int &store_location )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::GetDataInt()" );

		std::string temp_store;
		
		if( sections[ section ]->GetData(key, temp_store ) == KEY_NOT_EXISTS )
			return this->SetLastStatusCode( KEY_NOT_EXISTS,
							"Electrux::INI_Parser::GetDataInt()" );

		try
		{
			store_location = std::stoi( temp_store );
		}
		catch ( std::invalid_argument &e )
		{
			std::cerr << "Error in file: " __FILE__
				  << "\n\tFunction: " << "Electrux::Section::GetDataInt() : "
				  << e.what() << "\n";

			if( this->err_mode == THROW_EXCEPTION )
				throw e;

			return this->SetLastStatusCode( INVALID_DATA_TYPE,
							"Electrux::INI_Parser::GetDataInt()" );
		}
		catch( std::out_of_range &o )
		{
			std::cerr << "Error in file: " __FILE__
				  << "\n\tFunction: "
				  << "Electrux::Section::GetDataInt() ERR_OUT_OF_RANGE : "
				  << o.what() << "\n";

			if( this->err_mode == THROW_EXCEPTION )
				throw o;

			return this->SetLastStatusCode( DATA_OUT_OF_RANGE,
							"Electrux::INI_Parser::GetDataInt()" );
		}

		return this->SetLastStatusCode( SUCCESS, "Electrux::INI_Parser::GetDataInt()" );
	}
	
	STATUS_CODES INI_Parser::GetDataFloat( const std::string &section,
					       const std::string &key,
					       float &store_location )
	{
		if( !this->SectionExists( section ) )
			return this->SetLastStatusCode( SECTION_NOT_EXISTS,
							"Electrux::INI_Parser::GetDataFloat()" );

		std::string temp_store;

		if( sections[ section ]->GetData(key, temp_store ) == KEY_NOT_EXISTS )
			return this->SetLastStatusCode( KEY_NOT_EXISTS,
							"Electrux::INI_Parser::GetDataFloat()" );

		try
		{
			store_location = std::stof( temp_store );
		}
		catch ( std::invalid_argument &e )
		{
			std::cerr << "Error in file: " __FILE__
				  << "\n\tFunction: " << "Electrux::Section::GetDataFloat() : "
				  << e.what() << "\n";

			if( this->err_mode == THROW_EXCEPTION )
				throw e;

			return this->SetLastStatusCode( INVALID_DATA_TYPE,
							"Electrux::INI_Parser::GetDataFloat()" );
		}
		catch( std::out_of_range &o )
		{
			std::cerr << "Error in file: " __FILE__ << "\n\tFunction: "
				  << "Electrux::Section::GetDataFloat() ERR_OUT_OF_RANGE : "
				  << o.what() << "\n";

			if( this->err_mode == THROW_EXCEPTION )
				throw o;

			return this->SetLastStatusCode( DATA_OUT_OF_RANGE,
							"Electrux::INI_Parser::GetDataFloat()" );
		}

		return this->SetLastStatusCode( SUCCESS, "Electrux::INI_Parser::GetDataFloat()" );
	}

	// Retrieve last occured error as string or its code, or display it.
	// Prefer using Display because it automatically prints to std::cerr if
	// the status is not success/none.
	std::string INI_Parser::GetLastStatusString()
	{
		return "In function: "
			+ this->last_func
			+ "\n\tStatus: "
			+ STATUS_MSG[ this->last_code ];
	}

	std::string INI_Parser::GetLastStatusCodeString()
	{
		return STATUS_MSG[ this->last_code ];
	}

	STATUS_CODES INI_Parser::GetLastStatusCode()
	{
		return this->last_code;
	}

	std::string INI_Parser::GetLastFunction()
	{
		return this->last_func;
	}

	void INI_Parser::DisplayLastStatusString()
	{
		if( this->last_code != SUCCESS && this->last_code != NONE )
			std::cerr << this->GetLastStatusString() << "\n";
		else
			std::cout << this->GetLastStatusString() << "\n";
	}

	// Retrieve section count.
	size_t INI_Parser::Size()
	{
		return sections.size();
	}

	// Set the Fatal error mode to either throw exception or to
	// simply output in std::cerr without terminating the program.
	void INI_Parser::SetFatalErrorMode( FATAL_ERROR_MODES mode )
	{
		this->err_mode = mode;
	}

	void INI_Parser::DisplayAll()
	{
		if( sections.empty() )
			std::cout << "NO SECTION AVAILABLE\n";

		for(auto section : sections )
		{
			std::cout << "***************Section: "
				  << section.first
				  << "************************\n\n";

			section.second->DisplayAll();

			std::cout << "\n";
		}
	}
}

//
// Created by electrux on 7/25/17.
//

#include "../../include/INI_System/Section.hpp"

namespace Electrux
{
	//******************PUBLIC FUNCTIONS******************//

	STATUS_CODES Section::SetData( const std::string &key, const std::string &val )
	{
		if( data.find( key ) != data.end() ) return KEY_ALREADY_EXISTS;

		data[ key ] = val;

		return SUCCESS;
	}

	STATUS_CODES Section::UpdateData( const std::string &key, const std::string &val )
	{
		if( data.find( key ) == data.end() ) return KEY_NOT_EXISTS;

		data[ key ] = val;

		return SUCCESS;
	}

	STATUS_CODES Section::DeleteData(const std::string &key)
	{
		if( data.find( key ) == data.end() ) return KEY_NOT_EXISTS;

		data.erase( key );

		return SUCCESS;
	}

	STATUS_CODES Section::GetData( const std::string &key, std::string &store_location )
	{
		if( data.find( key ) == data.end() ) return KEY_NOT_EXISTS;

		store_location = data[ key ];

		return SUCCESS;
	}

	size_t Section::GetSize()
	{
		return data.size();
	}

	std::map< std::string, std::string > &Section::GetAllData()
	{
		return this->data;
	};

	void Section::DisplayAll()
	{
		if( data.empty() )
			std::cout << "NO DATA AVAILABLE\n";

		for ( auto temp : data )
			std::cout << "Key: " << temp.first
				  << "\t\tData: " << temp.second << "\n";
	}
}

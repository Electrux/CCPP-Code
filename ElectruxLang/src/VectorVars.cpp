#include <string>
#include <vector>
#include <map>

#include "../include/DataTypes.hpp"

#include "../include/VectorVars.hpp"

static std::map< std::string, VectorVars * > spaces;

VectorVars::VectorVars()
{}

VectorVars::~VectorVars()
{}

VectorVars * VectorVars::GetSingleton( const std::string & space )
{	
	if( space.empty() )
		return nullptr;

	if( spaces.find( space ) != spaces.end() )
		return spaces[ space ];

	spaces[ space ] = new VectorVars;
	spaces[ space ]->spacename = space;

	return spaces[ space ];
}

void VectorVars::AddVars( const std::map< std::string, std::vector< std::string > > & vars )
{
	for( auto elem : vars )
		this->vars[ elem.first ] = elem.second;
}

void VectorVars::AddVar( const std::string & key, const std::string & val )
{
	vars[ key ].push_back( val );
}

std::vector< std::string > & VectorVars::GetVar( const std::string & key )
{
	return vars[ key ];
}

std::vector< int > VectorVars::GetNumVar( const std::string & key )
{
	std::vector< int > numvars;
	for( auto var : vars[ key ] )
		numvars.push_back( std::stoi( var ) );

	return numvars;
}

std::vector< float > VectorVars::GetFloatVar( const std::string & key )
{
	std::vector< float > floatvars;
	for( auto var : vars[ key ] )
		floatvars.push_back( std::stoi( var ) );

	return floatvars;
}

bool VectorVars::VarExists( const std::string & key )
{
	return vars.find( key ) != vars.end();
}

bool VectorVars::DeleteVar( const std::string & key )
{
	auto loc = vars.find( key );

	if( loc == vars.end() )
		return false;

	vars.erase( loc );
	return true;
}

bool VectorVars::DelSingleton( const std::string & space )
{
	if( spaces.find( space ) == spaces.end() )
		return false;

	delete spaces[ space ];
	spaces.erase( space );

	return true;
}

bool VectorVars::IsEmpty()
{
	return vars.empty();
}
#include <map>
#include <string>

#include "../include/DataTypes.hpp"

#include "../include/Vars.hpp"

static std::map< std::string, Vars * > spaces;

Vars::Vars()
{}

Vars::~Vars()
{}

Vars * Vars::GetSingleton( const std::string & space )
{
	if( spaces.find( space ) != spaces.end() )
		return spaces[ space ];

	spaces[ space ] = new Vars;
	spaces[ space ]->spacename = space;

	return spaces[ space ];
}

void Vars::AddVars( const std::map< std::string, std::string > & vars )
{
	for( auto elem : vars )
		this->vars[ elem.first ] = elem.second;
}

void Vars::AddVar( const std::string & key, const std::string & val )
{
	vars[ key ] = val;
}

std::string & Vars::GetVar( const std::string & key )
{
	return vars[ key ];
}

int Vars::GetNumVar( const std::string & key )
{
	if( !VarExists( key ) )
		return std::numeric_limits< int >::min();

	return std::stoi( vars[ key ] );
}

float Vars::GetFloatVar( const std::string & key )
{
	if( !VarExists( key ) )
		return std::numeric_limits< float >::infinity();

	return std::stof( vars[ key ] );
}

bool Vars::VarExists( const std::string & key )
{
	return vars.find( key ) != vars.end();
}

bool Vars::DeleteVar( const std::string & key )
{
	auto loc = vars.find( key );

	if( loc == vars.end() )
		return false;

	vars.erase( loc );

	return true;
}

bool Vars::DelSingleton( const std::string & space )
{
	if( spaces.find( space ) == spaces.end() )
		return false;

	delete spaces[ space ];
	spaces.erase( space );

	return true;
}

bool Vars::IsEmpty()
{
	return vars.empty();
}
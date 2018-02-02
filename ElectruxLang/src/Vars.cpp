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
	if( space.empty() )
		return nullptr;

	if( spaces.find( space ) != spaces.end() )
		return spaces[ space ];

	spaces[ space ] = new Vars;
	spaces[ space ]->spacename = space;

	spaces[ space ]->vars[ "invalid" ] = { Vars::INVALID, "" };

	return spaces[ space ];
}

void Vars::AddVars( const std::map< std::string, Variable > & vars )
{
	for( auto elem : vars )
		this->vars[ elem.first ] = elem.second;
}

void Vars::AddVar( const std::string & key, const Variable & val )
{
	vars[ key ] = val;
}

Variable & Vars::GetVar( const std::string & key )
{
	return VarExists( key ) ? vars[ key ] : vars[ "invalid" ];
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
#include <iostream>
#include <map>
#include <string>

#include "../include/DataTypes.hpp"
#include "../include/GlobalData.hpp"

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

	if( spaces[ space] != nullptr )
		delete spaces[ space ];
	spaces.erase( space );

	return true;
}

void Vars::InitializeVars()
{
	auto v = Vars::GetSingleton( "__self_vars__" );

	v->AddVar( "o", { Vars::STRING, "\033[0m" } );

	v->AddVar( "r", { Vars::STRING, "\033[0;31m" } );
	v->AddVar( "g", { Vars::STRING, "\033[0;32m" } );
	v->AddVar( "y", { Vars::STRING, "\033[0;33m" } );
	v->AddVar( "b", { Vars::STRING, "\033[0;34m" } );
	v->AddVar( "m", { Vars::STRING, "\033[0;35m" } );
	v->AddVar( "c", { Vars::STRING, "\033[0;36m" } );
	v->AddVar( "w", { Vars::STRING, "\033[0;37m" } );

	v->AddVar( "br", { Vars::STRING, "\033[1;31m" } );
	v->AddVar( "bg", { Vars::STRING, "\033[1;32m" } );
	v->AddVar( "by", { Vars::STRING, "\033[1;33m" } );
	v->AddVar( "bb", { Vars::STRING, "\033[1;34m" } );
	v->AddVar( "bm", { Vars::STRING, "\033[1;35m" } );
	v->AddVar( "bc", { Vars::STRING, "\033[1;36m" } );
	v->AddVar( "bw", { Vars::STRING, "\033[1;37m" } );

	v->AddVar( "fc", { Vars::STRING, "\033[0;33m" } );
	v->AddVar( "sc", { Vars::STRING, "\033[0;36m" } );
	v->AddVar( "tc", { Vars::STRING, "\033[0;35m" } );
	v->AddVar( "ec", { Vars::STRING, "\033[0;34m" } );

	v->AddVar( "nl", { Vars::STRING, "\n" } );
	v->AddVar( "ts", { Vars::STRING, "\t" } );
}

void Vars::DelAllVars()
{
	for( auto it = spaces.begin(); it != spaces.end(); ) {
		if( it->second != nullptr )
			delete it->second;
		it = spaces.erase( it );
	}
}

bool Vars::IsEmpty()
{
	return vars.empty();
}

Variable FetchVariable( const std::string & var, const int & lineinfile )
{
	auto dt = DataType::GetDataType( var );
	if( dt == DataType::LITERAL ) {
		std::string res = var;

		res.erase( res.begin() );
		res.erase( res.end() - 1 );

		return { Vars::STRING, res };
	}
	if( dt != DataType::STRING ) {
		if( dt == DataType::NUM )
			return { Vars::NUM, var };
		if( dt == DataType::FLOAT )
			return { Vars::FLOAT, var };
	}

	auto v = Vars::GetSingleton( "global" );
	auto fv = Vars::GetSingleton( GetCurrentFunction() );

	if( fv != nullptr && fv->GetVar( var ).data.size() > 0 )
		return fv->GetVar( var );
	else if( v != nullptr && v->GetVar( var ).data.size() > 0 )
		return v->GetVar( var );

	std::cerr << "Error at line: " << lineinfile << ": Undefined variable: " << var << "!" << std::endl;
	return { Vars::INVALID, "__E_R_R_O_R__" };
}

std::string FetchVarToString( const std::string & var, const int & lineinfile )
{
	return FetchVariable( var, lineinfile ).data;
}
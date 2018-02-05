#ifndef VARS_HPP
#define VARS_HPP

#include <string>
#include <vector>
#include <map>

#include "DataTypes.hpp"

struct Variable;

// Singleton class.
class Vars
{
	std::string spacename;

	std::map< std::string, Variable > vars;

	Vars();
	~Vars();
public:
	enum VarType
	{
		NUM,
		FLOAT,
		STRING,

		INVALID
	};

	static Vars * GetSingleton( const std::string & space );

	void AddVars( const std::map< std::string, Variable > & vars );

	void AddVar( const std::string & key, const Variable & val );
	void AddVar( const std::string & key, const std::string & val );

	Variable & GetVar( const std::string & key );

	bool DeleteVar( const std::string & key );

	static bool DelSingleton( const std::string & space );

	bool VarExists( const std::string & key );

	static void InitializeVars( const int & argc, const char ** argv );

	static void DelAllVars();

	bool IsEmpty();
};

struct Variable
{
	Vars::VarType vartype;
	std::string data;
};

Variable FetchVariable( const std::string & var, const int & lineinfile, const int & show_error = true );

std::string FetchVarToString( const std::string & var, const int & lineinfile, const int & show_error = true );

#endif // VARS_HPP

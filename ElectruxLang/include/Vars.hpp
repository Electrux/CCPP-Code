#ifndef VARS_HPP
#define VARS_HPP

#include <string>
#include <vector>
#include <map>

#include "DataTypes.hpp"

// Singleton class.
class Vars
{
	std::string spacename;

	std::map< std::string, std::string > vars;

	Vars();
	~Vars();
public:
	static Vars * GetSingleton( const std::string & space );

	void AddVars( const std::map< std::string, std::string > & vars );

	void AddVar( const std::string & key, const std::string & val );

	std::string & GetVar( const std::string & key );
	int GetNumVar( const std::string & key );
	float GetFloatVar( const std::string & key );

	bool DeleteVar( const std::string & key );

	static bool DelSingleton( const std::string & space );

	bool VarExists( const std::string & key );

	bool IsEmpty();
};

#endif // VARS_HPP
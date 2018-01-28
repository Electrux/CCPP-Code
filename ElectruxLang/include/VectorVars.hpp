#ifndef VECTORVARS_HPP
#define VECTORVARS_HPP

#include <string>
#include <vector>
#include <map>

#include "DataTypes.hpp"

class VectorVars
{
	std::string spacename;

	std::map< std::string, std::vector< std::string > > vars;

	VectorVars();
	~VectorVars();
public:
	static VectorVars * GetSingleton( const std::string & space );

	void AddVars( const std::map< std::string, std::vector< std::string > > & vars );

	void AddVar( const std::string & key, const std::string & val );

	std::vector< std::string > & GetVar( const std::string & key );
	std::vector< int > GetNumVar( const std::string & key );
	std::vector< float > GetFloatVar( const std::string & key );

	bool DeleteVar( const std::string & key );

	static bool DelSingleton( const std::string & space );

	bool VarExists( const std::string & key );

	bool IsEmpty();
};

#endif // VECTORVARS_HPP
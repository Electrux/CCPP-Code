#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>
#include <map>

#include "Errors.hpp"
#include "Vars.hpp"
#include "VectorVars.hpp"
#include "DataTypes.hpp"

class Function
{
	std::string name;

	Vars * args;
	VectorVars * vecargs;

	std::vector< std::vector< DataType::Data > > lines;

	Function();
	~Function();

public:

	static Function * GetSingleton( const std::string & fnname );

	static ErrorTypes LoadFunction( const std::vector< std::vector< DataType::Data > > & alldata, const int & startline );
	ErrorTypes ExecuteFunction();

	static bool DelSingleton( const std::string & fnname );
};

int GetArgCount( const std::vector< DataType::Data > & dataline );

static std::map< std::string, Function * > allfuncs;

#endif // FUNCTIONS_HPP
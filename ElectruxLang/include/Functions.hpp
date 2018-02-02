#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>
#include <map>

#include "Errors.hpp"
#include "Vars.hpp"
#include "DataTypes.hpp"

class Function
{
	std::string name;

	int argscount;

	std::vector< std::vector< DataType::Data > > lines;

	Function();
	~Function();

public:

	static Function * GetSingleton( const std::string & fnname );

	static ErrorTypes LoadFunction( const std::vector< std::vector< DataType::Data > > & alldata, int & startline );
	ErrorTypes ExecuteFunction( const std::vector< DataType::Data > & argnames, const int & fileline );

	static bool DelSingleton( const std::string & fnname );

	static void DelAllFuncs();

	static int GetArgs( const std::vector< DataType::Data > & dataline, std::vector< DataType::Data > & argnames );
};

static std::map< std::string, Function * > allfuncs;

#endif // FUNCTIONS_HPP
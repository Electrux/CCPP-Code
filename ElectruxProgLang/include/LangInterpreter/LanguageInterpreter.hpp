#ifndef LANGUAGEINTERPRETER_HPP
#define LANGUAGEINTERPRETER_HPP

#include <vector>
#include <unordered_map>

#include "../FileParser.hpp"

class Interpreter
{
public:
	Interpreter( FileParser & parser );

	int Interpret();

private:

	// VARIABLES
	std::vector< std::string > & lines;

	std::unordered_map< std::string, std::string > strvars;
	std::unordered_map< std::string, int > intvars;

	// FUNCTIONS
	int InterpretPrint( std::vector< std::string > & lineparts, int line );

	int InterpretNewVar( std::vector< std::string > & lineparts, int line );

	int InterpretScan( std::vector< std::string > & lineparts, int line );

	// Common Functions

	int AddVariable( const std::string & var,
			 const std::string & val,
			 int line, bool isvarcheck = true );

	int FormatString( std::vector< std::string > & lineparts,
			  std::string & fmtstr,
			  int line );

	int IsInt( const std::string & data );

	bool IsConstString( const std::string & data);

	bool GetVarVal( const std::string & key, std::string & val, const int line );
};

#endif // LANGUAGEINTERPRETER_HPP

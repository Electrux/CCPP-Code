#ifndef LANGUAGEINTERPRETER_HPP
#define LANGUAGEINTERPRETER_HPP

#include <vector>
#include <unordered_map>

#include "../Commands.hpp"
#include "../DataTypes.hpp"
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
	std::unordered_map< std::string, float > fltvars;

	// FUNCTIONS

	int ExecuteLine( const std::vector< std::string > & lines, int & line );

	int InterpretPrint( std::vector< std::string > & lineparts, int line );

	int InterpretNewVar( std::vector< std::string > & lineparts, int line );

	int InterpretScan( std::vector< std::string > & lineparts, int line );

	int InterpretConditional( const std::vector< std::string > & lines,
				  const std::vector< std::string > & lineparts,
				  int & line );

	int InterpretLoop( const std::vector< std::string > & lines,
			   const std::vector< std::string > & lineparts,
			   int & line );

	// Eval Condition function
	int EvalCondition( std::vector< std::string > lineparts, int line );

	// Common Functions

	COMMANDS GetReturnCode( int val );

	int DeleteVariable( const std::string & var, int line );

	int UpdateVariable( const std::string & var,
			    const std::string & val,
			    int line, bool isvarcheck = true );

	int AddVariable( const std::string & var,
			 const std::string & val,
			 int line, bool isvarcheck = true );

	int FormatString( std::vector< std::string > & lineparts,
			  std::string & fmtstr,
			  int line );

	std::string GetReplacementValue( const std::string & str, int line );

	DataTypes GetType( const std::string & data );

	bool IsConstString( const std::string & data);

	bool GetVarVal( const std::string & key, std::string & val, const int line );
};

#endif // LANGUAGEINTERPRETER_HPP

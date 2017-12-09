#include <iostream>
#include <vector>
#include <string>

#include "../../include/DataTypes.hpp"

#include "../../include/LangInterpreter/LanguageInterpreter.hpp"

int Interpreter::EvalCondition( std::vector< std::string > lineparts, int line )
{
	// if a CONDITION b :
	std::string replval1 = GetReplacementValue( lineparts[ 1 ], line + 1 );
	std::string replval2 = GetReplacementValue( lineparts[ 3 ], line + 1 );

	if( replval1.empty() || replval2.empty() )
		return -1;

	// if a CONDITION b :
	auto dt1 = GetType( replval1 );
	auto dt2 = GetType( replval2 );

	if( dt1 != dt2 ) {
		std::cerr << "Error in line: " << line + 1
			  << "\n\tTypes of data in the condition do not match!" << std::endl;
		return -1;
	}

	std::string cond = lineparts[ 2 ];

	if( dt1 == FLT ) {

		float val1, val2;

		val1 = std::stof( replval1 );
		val2 = std::stof( replval2 );

		if( cond == "<" )
			return val1 < val2;
		else if( cond == "<=" )
			return val1 <= val2;

		else if( cond == ">" )
			return val1 > val2;
		else if( cond == ">=" )
			return val1 >= val2;

		else if( cond == "!=" )
			return val1 != val2;
		else if( cond == "==" )
			return val1 == val2;
	}

	if( dt1 == INT ) {

		int val1, val2;

		val1 = std::stoi( replval1 );
		val2 = std::stoi( replval2 );

		if( cond == "<" )
			return val1 < val2;
		else if( cond == "<=" )
			return val1 <= val2;

		else if( cond == ">" )
			return val1 > val2;
		else if( cond == ">=" )
			return val1 >= val2;

		else if( cond == "!=" )
			return val1 != val2;
		else if( cond == "==" )
			return val1 == val2;
	}

	if( dt1 == STR ) {

		std::string & val1 = replval1;
		std::string & val2 = replval2;

		if( cond == "<" )
			return val1 < val2;
		else if( cond == "<=" )
			return val1 <= val2;

		else if( cond == ">" )
			return val1 > val2;
		else if( cond == ">=" )
			return val1 >= val2;

		else if( cond == "!=" )
			return val1 != val2;
		else if( cond == "==" )
			return val1 == val2;
	}

	return -1;
}

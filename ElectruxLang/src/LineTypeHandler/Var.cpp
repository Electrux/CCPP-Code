#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"

#include "../../include/LineTypeHandler/Var.hpp"

ErrorTypes HandleVar( const std::vector< std::vector< DataType::Data > > & alldata, const int & line,
			std::map< std::string, int > & vardeclline )
{
	auto currline = alldata[ line ];

	if( currline.size() < 5 || ( currline[ 2 ].type != DataType::IDENTIFIER ||
					currline[ 3 ].detailtype != DataType::ASSIGN ) ) {
		std::cerr << "Error: Syntax for declaring a variable is - var < name > = < value >\nError on line: "
			<< line << std::endl;
		return SYNTAX_ERROR;
	}

	// Now, evaluate the RHS expression.
}
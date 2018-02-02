#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/GlobalData.hpp"
#include "../../include/Vars.hpp"
#include "../../include/ExpressionEvaluator.hpp"

#include "../../include/LineTypeHandler/Var.hpp"

ErrorTypes HandleVar( const std::vector< std::vector< DataType::Data > > & alldata, const int & line )
{
	auto currline = alldata[ line ];

	if( currline.size() < 5 || ( currline[ 2 ].type != DataType::IDENTIFIER ||
					currline[ 3 ].detailtype != DataType::ASSIGN ) ) {
		std::cerr << "Error: Syntax for declaring a variable is - var < name > = < value >\nError on line: "
			<< line << std::endl;
		return SYNTAX_ERROR;
	}

	// Now, evaluate the RHS expression.
	Variable tempvar;

	auto err = EvalExpression( alldata[ line ], 4, alldata[ line ].size() - 1, tempvar );
	if( err != SUCCESS )
		return err;

	std::string space = GetCurrentFunction();
	if( space.empty() )
		space = "global";

	auto v = Vars::GetSingleton( space );

	v->AddVar( currline[ 2 ].word, tempvar );

	return SUCCESS;
}
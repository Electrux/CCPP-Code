#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/GlobalData.hpp"
#include "../../include/Vars.hpp"
#include "../../include/ExpressionEvaluator.hpp"
#include "../../include/Functions.hpp"

#include "../../include/LineTypeHandler/Var.hpp"

ErrorTypes HandleVar( const std::vector< std::vector< DataType::Data > > & alldata, const int & line )
{
	auto & currline = alldata[ line ];

	if( currline.size() < 5 || ( currline[ 2 ].type != DataType::IDENTIFIER ||
					currline[ 3 ].detailtype != DataType::ASSIGN ) ) {
		std::cerr << "Error: Syntax for declaring a variable is - var < name > = < value >\nError on line: "
			<< currline[ 0 ].fileline << std::endl;
		return SYNTAX_ERROR;
	}

	if( FetchVarToString( currline[ 2 ].word, currline[ 0 ].fileline, false ) != "__E_R_R_O_R__" ) {
		std::cerr << "Error on line: " << currline[ 0 ].fileline << ": Variable already defined: " << currline[ 2 ].word
			<< "!" << std::endl;
		return SYNTAX_ERROR;
	}

	// Fetch return value from a function!
	if( currline.size() >= 7 && currline[ 4 ].type == DataType::IDENTIFIER && currline[ 5 ].type == DataType::SEPARATOR &&
		currline[ 5 ].detailtype == DataType::PARENTHESISOPEN ) {

		auto func = Function::GetSingleton( currline[ 4 ].word );
		if( func == nullptr ) {
			std::cerr << "Error on line: " << currline[ 0 ].fileline << ": No function named: "
				<< currline[ 4 ].word << " exists!" << std::endl;
			return ENTITY_NOT_FOUND;
		}
		std::vector< DataType::Data > argnames;
		Function::GetArgs( currline, argnames );
		func->ExecuteFunction( argnames, currline[ 0 ].fileline );

		std::string space = GetCurrentFunction();
		if( space.empty() )
			space = "global";

		auto fv = Vars::GetSingleton( space );

		auto v = Vars::GetSingleton( space );

		Variable tempvar = fv->GetVar( "fn_ret_" + alldata[ line ][ 4 ].word );
		if( tempvar.vartype == Vars::INVALID ) {
			std::cerr << "Error on line: " << alldata[ line ][ 0 ].fileline << ": Cannot set value for a variable from a function "
				<< "which does not return a value!" << std::endl;
			return SYNTAX_ERROR;
		}
		fv->DeleteVar( "fn_ret_" + alldata[ line ][ 4 ].word );
		v->AddVar( currline[ 2 ].word, tempvar );

		return SUCCESS;
	}

	// Now, evaluate the RHS expression.
	Variable tempvar;

	auto err = EvalExpression( currline, 4, currline.size() - 1, tempvar );
	if( err != SUCCESS )
		return err;

	std::string space = GetCurrentFunction();
	if( space.empty() )
		space = "global";

	auto v = Vars::GetSingleton( space );

	v->AddVar( currline[ 2 ].word, tempvar );

	return SUCCESS;
}

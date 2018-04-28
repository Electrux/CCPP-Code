#include <iostream>
#include <string>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/GlobalData.hpp"
#include "../../include/Vars.hpp"
#include "../../include/ExpressionEvaluator.hpp"

#include "../../include/LineTypeHandler/General.hpp"

ErrorTypes ExecuteGeneral( const std::vector< DataType::Data > & dataline )
{
	if( dataline.size() < 3 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Format for a generic expression is: < var > = < val >!" << std::endl;
		return SYNTAX_ERROR;
	}

	Variable tempres;
	auto err = EvalExpression( dataline, 3, dataline.size() - 1, tempres );

	if( err != SUCCESS )
		return err;

	std::string space = GetCurrentFunction();
	if( space.empty() )
		space = "global";

	auto v = Vars::GetSingleton( space );

	if( !v->VarExists( dataline[ 1 ].word ) ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Variable: " << dataline[ 1 ].word << " does not exist!" << std::endl;
		return SYNTAX_ERROR;
	}

	v->AddVar( dataline[ 1 ].word, tempres );
	return err;
}
#include <iostream>
#include <string>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/GlobalData.hpp"
#include "../../include/Vars.hpp"
#include "../../include/ExpressionEvaluator.hpp"

#include "../../include/LineTypeHandler/Return.hpp"

ErrorTypes ExecuteReturn( const std::vector< DataType::Data > & dataline )
{
	if( GetCurrentFunction().empty() ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Return can only be used inside a function!" << std::endl;
		return SYNTAX_ERROR;
	}

	if( dataline.size() < 3 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Nothing to return!" << std::endl;
		return SYNTAX_ERROR;
	}

	// a simple return statement.
	/*if( dataline.size() == 3 ) {
		SetCurrentReturnValue( FetchVariable( dataline[ 2 ].word, dataline[ 2 ].fileline ) );
		return SUCCESS;
	}*/

	Variable tempres;
	auto err = EvalExpression( dataline, 2, dataline.size() - 1, tempres );

	if( err == SUCCESS )
		SetCurrentReturnValue( tempres );

	return err;
}
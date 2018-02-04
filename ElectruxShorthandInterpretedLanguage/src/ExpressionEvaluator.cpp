#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>

#include "../include/Errors.hpp"
#include "../include/DataTypes.hpp"
#include "../include/GlobalData.hpp"
#include "../include/StringFuncs.hpp"
#include "../include/Stack.hpp"
#include "../include/Vars.hpp"

#include "../include/ExpressionEvaluator.hpp"

ErrorTypes EvalExpression( const std::vector< DataType::Data > & dataline, const int & from, const int & to, Variable & result )
{
	if( from > to )
		return INVALID_EXPRESSION;

	std::vector< DataType::Data > postfix;

	ErrorTypes err;
	if( ( err = GenPostfix( dataline, from, to, postfix ) ) != SUCCESS )
		return err;

	if( !SetAllVariableValues( postfix ) )
		return ENTITY_NOT_FOUND;

	//Get the overall data type for the expression.
	auto dt = GetOverallDataType( postfix );
	if( dt == DataType::INVALID )
		return INVALID_EXPRESSION;

	// Actual evaluation starts here.
	std::string tempres = CalculatePostfixExpression( postfix, dt );
	if( tempres.empty() )
		return INVALID_EXPRESSION;

	result.data = tempres;
	if( dt == DataType::STRING )
		result.vartype = Vars::STRING;
	if( dt == DataType::NUM )
		result.vartype = Vars::NUM;
	if( dt == DataType::FLOAT )
		result.vartype = Vars::FLOAT;

	return SUCCESS;
}

ErrorTypes GenPostfix( const std::vector< DataType::Data > & dataline, const int & from, const int & to,
				std::vector< DataType::Data > & postfix )
{
	Stack< DataType::Data > opstack;

	for( int i = from; i <= to; ++i ) {
		if( !IsValidDataType( dataline[ i ] ) ) {
			std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Invalid element in expression: "
				<< dataline[ i ].word << std::endl;
			return INVALID_EXPRESSION;
		}

		if( IsSymbol( dataline[ i ].word ) ) {
			if( dataline[ i ].word == "(" ) {
				opstack.Push( dataline[ i ] );
			}
			else if( dataline[ i ].word == ")" ) {
				if( opstack.Size() < 1 ) {
					std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Invalid closing parenthesis!"
						<< std::endl;
					return BRACKET_MISMATCH;
				}
				auto last = opstack.Pop();
				while( last.word != "(" ) {
					postfix.push_back( last );
					if( opstack.Size() < 1 ) {
						std::cerr << "Error on line: " << dataline[ 0 ].fileline
							<< ": Invalid closing parenthesis!" << std::endl;
						return BRACKET_MISMATCH;
					}
					last = opstack.Pop();
				}
			}
			else {
				while( opstack.Size() > 0 && GetPrec( opstack.Last().word ) >= GetPrec( dataline[ i ].word ) ) {
					postfix.push_back( opstack.Pop() );
				}
				opstack.Push( dataline[ i ] );
			}
		}
		else {
			postfix.push_back( dataline[ i ] );
		}
	}

	while( opstack.Size() > 0 ) {
		postfix.push_back( opstack.Pop() );
	}

	return SUCCESS;
}

DataType::SymbolType GetOverallDataType( const std::vector< DataType::Data > & postfixexpr )
{
	bool numexists = false, floatexists = false, strexists = false, symbol_other_than_plus_exists = false;

	for( auto data : postfixexpr ) {
		if( data.type == DataType::NUM )
			numexists = true;
		else if( data.type == DataType::FLOAT )
			floatexists = true;
		else if( data.type == DataType::STRING || data.type == DataType::LITERAL )
			strexists = true;
		else if( data.type == DataType::OPERATOR && data.detailtype != DataType::ADD )
			symbol_other_than_plus_exists = true;
	}

	if( symbol_other_than_plus_exists && strexists ) {
		std::cerr << "Error on line: " << postfixexpr[ 0 ].fileline << ": Expressions with strings can only be added!"
			<< std::endl;
		return DataType::INVALID;
	}

	if( strexists )
		return DataType::STRING;

	if( numexists && floatexists )
		return DataType::FLOAT;

	if( numexists && !floatexists )
		return DataType::NUM;

	if( !numexists && floatexists )
		return DataType::FLOAT;

	std::cerr << "Error on line: " << postfixexpr[ 0 ].fileline << ": Invalid expression!" << std::endl;
	return DataType::INVALID;
}

std::string CalculatePostfixExpression( const std::vector< DataType::Data > & postfixexpr, const DataType::SymbolType & exprtype )
{
	Stack< DataType::Data > operands;

	for( auto data : postfixexpr ) {
		if( IsSymbol( data.word ) ) {
			if( operands.Size() < 1 ) {
				std::cerr << "Error on line: " << postfixexpr[ 0 ].fileline << ": Invalid expression!"
					<< std::endl;
				return "";
			}

			auto op2 = operands.Pop();
			auto op1 = operands.Pop();
			auto datatemp = op2;

			datatemp.type = DataType::STRING;
			datatemp.word = PerformOperation( op1, op2, data, exprtype );
			if( exprtype == DataType::FLOAT && datatemp.word.find( '.' ) != std::string::npos ) {
				while( * ( datatemp.word.end() - 1 ) == '0' )
					datatemp.word.erase( datatemp.word.end() - 1 );
			}

			operands.Push( datatemp );

			continue;
		}

		operands.Push( data );
	}

	return operands.Size() > 0 ? operands.Pop().word : "";
}

std::string PerformOperation( const DataType::Data & op1, const DataType::Data & op2,
			const DataType::Data & op, const DataType::SymbolType & exprtype )
{
	if( exprtype == DataType::STRING ) {
		if( op.detailtype == DataType::ADD ) {
			return RemoveTrailingQuotes( op1.word ) + RemoveTrailingQuotes( op2.word );
		}
		return "";
	}

	if( exprtype == DataType::FLOAT ) {
		if( op.detailtype == DataType::ADD ) {
			return std::to_string( std::stof( op1.word ) + std::stof( op2.word ) );
		}
		if( op.detailtype == DataType::SUB ) {
			return std::to_string( std::stof( op1.word ) - std::stof( op2.word ) );
		}
		if( op.detailtype == DataType::MULT ) {
			return std::to_string( std::stof( op1.word ) * std::stof( op2.word ) );
		}
		if( op.detailtype == DataType::DIV ) {
			return std::to_string( std::stof( op1.word ) / std::stof( op2.word ) );
		}
		if( op.detailtype == DataType::MOD ) {
			std::cerr << "Error on line: " << op1.fileline
				<< ": Cannot use the modulo operator with floating point values!" << std::endl;
			return "";
		}

		return "";
	}

	if( exprtype == DataType::NUM ) {
		if( op.detailtype == DataType::ADD ) {
			return std::to_string( std::stoi( op1.word ) + std::stoi( op2.word ) );
		}
		if( op.detailtype == DataType::SUB ) {
			return std::to_string( std::stoi( op1.word ) - std::stoi( op2.word ) );
		}
		if( op.detailtype == DataType::MULT ) {
			return std::to_string( std::stoi( op1.word ) * std::stoi( op2.word ) );
		}
		if( op.detailtype == DataType::DIV ) {
			return std::to_string( std::stoi( op1.word ) / std::stoi( op2.word ) );
		}
		if( op.detailtype == DataType::MOD ) {
			return std::to_string( std::stoi( op1.word ) % std::stoi( op2.word ) );
		}

		return "";
	}

	return "";
}

bool SetAllVariableValues( std::vector< DataType::Data > & postfixexpr )
{
	auto v = Vars::GetSingleton( "global" );
	auto fv = Vars::GetSingleton( GetCurrentFunction() );
	for( auto & data : postfixexpr ) {
		if( data.type == DataType::IDENTIFIER ) {
			std::string res = FetchVarToString( data.word, data.fileline );
			if( res == "__E_R_R_O_R__" ) {
				return false;
			}
			else {
				data.type = DataType::GetDataType( res );
				data.word = res;

				continue;
			}
		}

		if( data.type == DataType::LITERAL ) {
			data.word.erase( data.word.begin() );
			data.word.erase( data.word.end() - 1 );
		}
	}

	return true;
}

bool IsValidDataType( const DataType::Data & data )
{
	if( data.type == DataType::NUM || data.type == DataType::FLOAT || data.type == DataType::IDENTIFIER ||
		data.type == DataType::OPERATOR || data.type == DataType::LITERAL ||
		( data.type == DataType::SEPARATOR &&
			( data.detailtype == DataType::PARENTHESISOPEN || data.detailtype == DataType::PARENTHESISCLOSE ) ) )
		return true;
	return false;
}

bool IsSymbol( const std::string & data )
{
	if( data == "(" || data == ")" || data == "^" || data == "/" || data == "*" ||
		data == "%" || data == "+" || data == "-" )
		return true;

	return false;
}

int GetPrec( const std::string & symbol )
{
	if( symbol == "(" || symbol == ")" )
		return -1;
	if( symbol == "^" )
		return 3;
	if( symbol == "*" || symbol == "/" || symbol == "%" )
		return 2;
	if( symbol == "+" || symbol == "-" )
		return 1;

	return 0;
}
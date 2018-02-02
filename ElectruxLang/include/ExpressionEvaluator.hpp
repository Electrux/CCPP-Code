#ifndef EXPRESSIONEVALUATOR_HPP
#define EXPRESSIONEVALUATOR_HPP

#include <string>
#include <vector>

#include "Errors.hpp"
#include "DataTypes.hpp"

ErrorTypes EvalExpression( const std::vector< DataType::Data > & dataline, const int & from, const int & to, Variable & result );

ErrorTypes GenPostfix( const std::vector< DataType::Data > & dataline, const int & from, const int & to,
				std::vector< DataType::Data > & postfix );

DataType::SymbolType GetOverallDataType( const std::vector< DataType::Data > & postfixexpr );

std::string CalculatePostfixExpression( const std::vector< DataType::Data > & postfixexpr, const DataType::SymbolType & exprtype );

std::string PerformOperation( const DataType::Data & op1, const DataType::Data & op2,
			const DataType::Data & op, const DataType::SymbolType & exprtype );

bool SetAllVariableValues( std::vector< DataType::Data > & postfixexpr );

bool IsValidDataType( const DataType::Data & data );

bool IsSymbol( const std::string & data );

int GetPrec( const std::string & symbol );

#endif // EXPRESSIONEVALUATOR_HPP
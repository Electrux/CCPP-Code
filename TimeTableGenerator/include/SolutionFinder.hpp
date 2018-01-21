#ifndef SOLUTIONFINDER_HPP
#define SOLUTIONFINDER_HPP

#include <vector>

#include "DataStructure.hpp"

void Randomize( const int attempt );

int GetRandomBetween( const int lo, const int hi );

bool FindSolution( const int tablecount, const int rows, const int cols, std::vector< Data > & alldata );

void ClearTables( const Table * tables, const int tablecount );

int GetTotalFrequency( const std::vector< Data > & alldata );

bool ArrangeInTables( Table * tables, const int tablecount, const int rows, const int cols, const std::vector< Data > & alldata );

bool InsertDataInTable( Table * tables, int tablesize, int table, Data & data );

bool IsTableFull( const Table & table );

bool AnyPossibleLocationLeft( const Table * tables, const int tablesize, const int table, const Data & data, const int i, const int j );

bool DataOccursInOtherTablesAt( const Table * tables, const int tablesize, const int excludetable,
			const int i, const int j, const Data & data );

bool IsValidLocation( const Table * tables, const int tablesize, const int table, const Data & data, const int i, const int j );

Table * AllocateTables( const int tablecount, const int rows, const int cols );

void DeAllocateTables( Table * tables, const int tablecount, const int rows );

void DisplayTable( const Table & table );

#endif // SOLUTIONFINDER_HPP
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../include/DataStructure.hpp"
#include "../include/DisplayFuncs.hpp"

#include "../include/SolutionFinder.hpp"

void Randomize( const int attempt )
{
	std::srand( std::time( NULL ) );

	MoveOutputCursorBack();
	DisplayData( "\n{G}Info: Using a new random seed, attempt: {C}" + std::to_string( attempt ) + " {G}... " );
}

int GetRandomBetween( const int lo, const int hi )
{
	return std::rand() % ( hi - lo ) + lo;
}

bool FindSolution( const int tablecount, const int rows, const int cols, std::vector< Data > & alldata )
{
	int totalfreq = GetTotalFrequency( alldata );

	DisplayData( "{G}Total cells: {C}" + std::to_string( rows * cols ) +
	"\t{G}Total frequency: {C}" + std::to_string( totalfreq ) + "\n" );

	if( rows * cols < totalfreq ) {
		DisplayData( "{R}Cannot find solution!\nThe total frequency is more than the actual number of cells in the table!\n");
		return false;
	}

	int ctr = 0;
	int attempt = 1;

	bool foundsol = false;

	Randomize( attempt );
	++ctr;

	Table * tables = AllocateTables( tablecount, rows, cols );

	while( !foundsol ) {

		if( ctr % 50000 == 0 )
			DisplayOneLinerString( std::to_string( ctr ) );

		ClearTables( tables, tablecount );

		if( ArrangeInTables( tables, tablecount, rows, cols, alldata ) )
			foundsol = true;

		if( ctr % ( 300000 * tablecount ) == 0 ) {
			ctr = 0;
			Randomize( ++attempt );
		}
		++ctr;
	}

	DeAllocateTables( tables, tablecount, rows );

	return true;
}

void ClearTables( const Table * tables, const int tablecount )
{
	for( int i = 0; i < tablecount; ++i ) {
		for( int j = 0; j < tables[ i ].rows; ++j ) {
			for( int k = 0; k < tables[ i ].cols; ++k ) {
				tables[ i ].data[ j ][ k ] = "NULL";
			}
		}
	}
}

int GetTotalFrequency( const std::vector< Data > & alldata )
{
	int total = 0;

	for( auto data : alldata )
		total += data.frequency;

	return total;
}

bool ArrangeInTables( Table * tables, const int tablecount, const int rows, const int cols, const std::vector< Data > & alldata )
{
	std::vector< Data > tempdata = alldata;

	for( int i = 0; i < tablecount; ++i ) {
		for( auto data : tempdata )
			if( !InsertDataInTable( tables, tablecount, i, data ) )
				return false;
	}

	for( int i = 0; i < tablecount; ++i )
		DisplayTable( tables[ i ] );

	return true;
}

bool InsertDataInTable( Table * tables, int tablesize, int table, Data & data )
{
	while( data.frequency > 0 ) {
		int i, j;

		do {
			if( IsTableFull( tables[ table ] ) )
				return false;
			i = GetRandomBetween( 0, tables[ table ].rows );
			j = GetRandomBetween( 0, tables[ table ].cols );

			if( !AnyPossibleLocationLeft( tables, tablesize, table, data, i, j ) )
				return false;
		}
		while( !IsValidLocation( tables, tablesize, table, data, i, j ) );

		tables[ table ].data[ i ][ j ] = data.name;
		data.frequency--;
	}

	return true;
}

bool IsTableFull( const Table & table )
{
	for( int i = 0; i < table.rows; ++i ) {
		for( int j = 0; j < table.cols; ++j ) {
			if( table.data[ i ][ j ] == "NULL" )
				return false;
		}
	}

	return true;
}

bool AnyPossibleLocationLeft( const Table * tables, const int tablesize, const int table, const Data & data, const int i, const int j )
{
	if( j != tables[ table ].cols - 1 && tables[ table ].data[ i ][ j + 1 ] == data.name )
		return false;

	if( j != 0 && tables[ table ].data[ i ][ j - 1 ] == data.name )
		return false;

	for( int p = 0; p < tables[ table ].rows; ++p ) {
		for( int q = 0; q < tables[ table ].cols; ++q ) {
			if( !DataOccursInOtherTablesAt( tables, tablesize, table, p, q, data ) )
				return true;
		}
	}
	DisplayData( "Returning false\n" );

	return false;
}

bool DataOccursInOtherTablesAt( const Table * tables, const int tablesize, const int excludetable,
			const int i, const int j, const Data & data )
{
	for( int k = 0; k < tablesize; ++k ) {
		if( k != excludetable && tables[ k ].data[ i ][ j ] == data.name )
			return true;
	}

	return false;
}

bool IsValidLocation( const Table * tables, const int tablesize, const int table, const Data & data, const int i, const int j )
{
	if( i >= tables[ table ].rows || j >= tables[ table ].cols )
		return false;

	if( tables[ table ].data[ i ][ j ] != "NULL" )
		return false;

	if( j != tables[ table ].cols - 1 && tables[ table ].data[ i ][ j + 1 ] == data.name )
		return false;

	if( j != 0 && tables[ table ].data[ i ][ j - 1 ] == data.name )
		return false;

	for( int p = 0; p < tablesize; ++p ) {
		if( i >= tables[ p ].rows || j >= tables[ p ].cols )
			continue;
		
		if( tables[ p ].data[ i ][ j ] == data.name )
			return false;
	}

	return true;
}

Table * AllocateTables( const int tablecount, const int rows, const int cols )
{
	Table * tables = new Table[ tablecount ];

	for( int i = 0; i < tablecount; ++i ) {
		tables[ i ].data = new std::string *[ rows ];
		for( int j = 0; j < rows; ++j ) {
			tables[ i ].data[ j ] = new std::string[ cols ];
			for( int k = 0; k < cols; ++k )
				tables[ i ].data[ j ][ k ] = "NULL";
		}
		
		tables[ i ].rows = rows;
		tables[ i ].cols = cols;
	}

	return tables;
}

void DeAllocateTables( Table * tables, const int tablecount, const int rows )
{
	if( tables == nullptr )
		return;

	for( int i = 0; i < tablecount; ++i ) {
		for( int j = 0; j < rows; ++j )
			delete[] tables[ i ].data[ j ];
		delete[] tables[ i ].data;
	}
	delete[] tables;

	tables = nullptr;
}

void DisplayTable( const Table & table )
{
	DisplayData( "\n" );
	DisplayData( "\n" );

	for( int i = 0; i < table.rows; ++i ) {
		for( int j = 0; j < table.cols; ++j ) {
			if( table.data[ i ][ j ] == "NULL" )
				DisplayData( "{BR}" + table.data[ i ][ j ] + "\t" );
			else
				DisplayData( "{BM}" + table.data[ i ][ j ] + "\t" );
		}
		DisplayData( "\n" );
	}

	DisplayData( "\n" );
	DisplayData( "\n" );
}
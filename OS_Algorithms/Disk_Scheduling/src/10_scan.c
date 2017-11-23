#include <stdio.h>
#include <stdlib.h>

#include "../include/common.h"
#include "../include/disk.h"
#include "../include/operation.h"

int operation_at_sector( struct Operation ** operations, const int count, int sector )
{
	for( int i = 0; i < count; ++i )
		if( operations[ i ]->sector == sector )
			return i;

	return -1;
}

float perform_operations( struct Disk * disk,
			  struct Operation ** operations,
			  const int count,
			  int initialsector )
{
	int currentsector = initialsector;

	float total_time = 0.0;

	int finished_operations = 0;

	int isdone[ count ];

	for( int i = 0; i < count; ++i )
		isdone[ i ] = 0;

	// will be negative when reversing the direction. First right, then left...
	int increment = 1;

	while( finished_operations != count ) {

		int loc = operation_at_sector( operations, count, currentsector );

		if( loc != -1 && isdone[ loc ] != 1 ) {
			total_time += operations[ loc ]->datasize * 1024 / disk->speed;
			isdone[ loc ] = 1;
			finished_operations++;
		}

		if( currentsector == disk->sectors - 1 )
			increment = -increment;

		total_time += time_to_get_to_position( disk,
						       currentsector,
						       currentsector + increment );

		currentsector += increment;
	}

	return total_time;
}

int main()
{
	int opcount;
	int initialsector;
	
	struct Disk * disk;
	struct Operation ** operations;

	printf( "Enter disk details:-\n" );
	disk = create_disk();

	printf( "\nEnter initial sector: " );
	scanf( "%d", & initialsector );

	// A precaution...
	if( initialsector > disk->sectors )
		initialsector = initialsector % disk->sectors;

	printf( "\nEnter number of operations to be performed: " );
	scanf( "%d", & opcount );

	printf("\n" );

	operations = ( struct Operation ** )
		malloc( sizeof( * operations ) * opcount );


	for( int i = 0; i < opcount; ++i ) {
		printf( "Enter operation %d details:-\n", i + 1 );
		operations[ i ] = create_operation();
	}

	printf( "\nTotal time: %.4f seconds\n",
		perform_operations( disk, operations, opcount, initialsector ) );

	for( int i = 0; i < opcount; ++i )
		free( operations[ i ] );

	free( operations );
	free( disk );
	
	return 0;
}

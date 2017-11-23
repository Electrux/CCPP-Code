#include <stdio.h>
#include <stdlib.h>

#include "../include/common.h"
#include "../include/disk.h"
#include "../include/operation.h"

float perform_operations( struct Disk * disk,
			  struct Operation ** operations,
			  const int count,
			  int initialsector )
{
	int currentsector = initialsector;

	float total_time = 0.0;

	for( int i = 0; i < count; ++i ) {
		float disk_time =
			time_to_get_to_position( disk,
						 currentsector,
						 operations[ i ]->sector );

		currentsector = operations[ i ]->sector;

		float data_time = operations[ i ]->datasize * 1024 / ( float ) disk->speed;

		total_time += data_time + disk_time;
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

	printf( "\nTotal time: %.4f\n",
		perform_operations( disk, operations, opcount, initialsector ) );

	printf( "Sequence:-\n" );
	for( int i = 0; i < opcount; ++i )
		printf( "%d\n", operations[ i ]->sector );
	
	for( int i = 0; i < opcount; ++i )
		free( operations[ i ] );

	free( operations );
	free( disk );
	
	return 0;
}

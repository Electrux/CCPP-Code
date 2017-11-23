#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/common.h"
#include "../include/disk.h"
#include "../include/operation.h"

int get_min_seektime( struct Disk * disk,
		      struct Operation ** operations,
		      const int count,
		      int * isdone,
		      int currentsector )
{
	int minseekpos = -1;
	float minseektime = FLT_MAX;

	for( int i = 0; i < count; ++i ) {
		
		float seektime = time_to_get_to_position( disk,
							currentsector,
							operations[ i ]->sector );

		if( seektime < minseektime && isdone[ i ] != 1 ) {
			minseektime = seektime;
			minseekpos = i;
		}
	}

	if( minseekpos != -1 )
		isdone[ minseekpos ] = 1;

	return minseekpos;
}

float perform_operations( struct Disk * disk,
			  struct Operation ** operations,
			  const int count,
			  int initialsector )
{
	int currentsector = initialsector;

	float total_time = 0.0;

	int isdone[ count ];

	int totaldone = 0;

	for( int i = 0; i < count; ++i )
		isdone[ i ] = 0;

	while( totaldone != count ) {

		int minseek =
			get_min_seektime( disk, operations, count, isdone, currentsector );

		if( minseek == -1 )
			break;

		printf( "At %d, we have %d\n", totaldone, minseek );
		float disk_time =
			time_to_get_to_position( disk,
						 currentsector,
						 operations[ minseek ]->sector );

		currentsector = operations[ minseek ]->sector;

		float data_time =
			operations[ minseek ]->datasize * 1024 / ( float ) disk->speed;

		total_time += data_time + disk_time;

		totaldone++;
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

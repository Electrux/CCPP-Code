#include <stdio.h>
#include <stdlib.h>
#include "../include/process.h"

void swap( struct Process * p1, struct Process * p2 )
{
	struct Process temp = * p1;
	* p1 = * p2;
	* p2 = temp;
}

void sortmincpu( struct Process * processes, int count )
{
	for( int i = 0; i < count; ++i ) {
		for( int j = 0; j < count - i - 1; ++j )
			if( processes[ j ].duration > processes[ j + 1 ].duration ) {
				swap( & processes[ j ], & processes[ j + 1 ] );
			}
	}
}

float calc_wait_time( struct Process * processes, int count )
{
	int procwait = 0;
	int totalwait = 0;

	for( int i = 1; i < count; ++i ) {

		procwait += processes[ i - 1 ].duration;

		totalwait += procwait;

	}
	
	return totalwait / ( float ) count;
}

int main()
{
	int count;

	printf( "Enter number of processes: " );
	scanf( "%d", & count );

	struct Process * processes;

	processes = ( struct Process * )
		malloc( sizeof( * processes ) * count );

	for( int i = 0; i < count; ++i ) {

		printf( "Enter process %d details\n", i + 1 );
		processes[ i ] = create_process();
	}

	for( int i = 0; i < count; ++i )
		display_process( & processes[ i ] );
	
	printf( "Average wait time is: %.2f\n",
		calc_wait_time( processes, count ) );

	free( processes );
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../include/process.h"
#include "../include/funcs.h"

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

	sortmincpu( processes, count );

	for( int i = 0; i < count; ++i )
		display_process( & processes[ i ] );
	
	printf( "Average wait time is: %.2f\n",
		calc_wait_time( processes, count ) );

	free( processes );
	
	return 0;
}

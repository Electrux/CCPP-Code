#include <stdio.h>
#include <stdlib.h>

#define PRIORITY

#include "../include/process.h"
#include "../include/funcs.h"

int main()
{
	int count;

	printf( "Enter number of processes: " );
	scanf( "%d", & count );

	struct Process ** processes;

	processes = ( struct Process ** )
		malloc( sizeof( * processes ) * count );

	for( int i = 0; i < count; ++i ) {

		printf( "Enter process %d details\n", i + 1 );
		processes[ i ] = create_process();
	}

	sortmaxpriority( processes, count );

	for( int i = 0; i < count; ++i )
		display_process( processes[ i ] );
	
	printf( "Average wait time is: %.2f\n",
		calc_basic_wait_time( processes, count ) );

	for( int i = 0; i < count; ++i )
		free( processes[ i ] );

	free( processes );
	
	return 0;
}

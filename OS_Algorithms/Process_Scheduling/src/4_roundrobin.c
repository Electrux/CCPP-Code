#include <stdio.h>
#include <stdlib.h>

#define ROUNDROBIN
#include "../include/process.h"

int get_total_rem_time( struct Process ** processes, int count )
{
	int total = 0;
	
	for( int i = 0; i < count; ++i )
		total += processes[ i ]->remaining;

	return total;
}

void add_wait_to_all_except( struct Process ** processes, int count, int which, int dur )
{
	for( int i = 0; i < count; ++i ) {
		if( processes[ i ]->remaining <= 0 ) continue;
		
		if( i != which )
			processes[ i ]->waittime += dur;
	}
}

int spendslice( struct Process ** processes, int count, int which, int delta )
{
	int spenttime = 0;

	if( processes[ which ]->remaining > 0 ) {
		
		if( processes[ which ]->remaining - delta >= 0 ) {
			spenttime = delta;
			processes[ which ]->remaining -= delta;
		}
		else {
			spenttime = processes[ which ]->remaining;
			processes[ which ]->remaining = 0;
		}

		add_wait_to_all_except( processes, count, which, spenttime );
	}

	return spenttime;
}

float calc_wait_time( struct Process ** processes, int count, int delta )
{
	int totalremaining = get_total_rem_time( processes, count );
	
	while( totalremaining > 0 ) {
		for( int i = 0; i < count; ++i ) {
			totalremaining -= spendslice( processes, count, i, delta );
		}
	}

	int totalwait = 0;

	for( int i = 0; i < count; ++i )
		totalwait += processes[ i ]->waittime;

	return totalwait / ( float )count;
}

int main()
{
	int count;
	int delta;

	printf( "Enter time slice for each process: " );
	scanf( "%d", & delta );
	
	printf( "Enter number of processes: " );
	scanf( "%d", & count );

	struct Process ** processes;
	
	processes = ( struct Process ** )
		malloc( sizeof( * processes ) * count );

	for( int i = 0; i < count; ++i ) {

		printf( "Enter process %d details\n", i + 1 );
		processes[ i ] = create_process();
	}


	printf( "Total wait time is: %.4f\n",
		calc_wait_time( processes, count, delta ) );

	for( int i = 0; i < count; ++i )
		display_process( processes[ i ] );

	for( int i = 0; i < count; ++i )
		free( processes[ i ] );

	free( processes );

	return 0;
}

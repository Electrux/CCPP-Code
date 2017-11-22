#ifndef FUNCS_H
#define FUNCS_H

#include "process.h"

void swap( struct Process * p1, struct Process * p2 )
{
	struct Process temp = * p1;
	* p1 = * p2;
	* p2 = temp;
}

#ifdef PRIORITY
void sortmaxpriority( struct Process * processes, int count )
{
	for( int i = 0; i < count; ++i )
		for( int j = 0; j < count - i - 1; ++j )
			if( processes[ j ].priority < processes[ j + 1 ].priority )
				swap( & processes[ j ], & processes[ j + 1 ] );
}
#endif

void sortmincpu( struct Process * processes, int count )
{
	for( int i = 0; i < count; ++i )
		for( int j = 0; j < count - i - 1; ++j )
			if( processes[ j ].duration > processes[ j + 1 ].duration )
				swap( & processes[ j ], & processes[ j + 1 ] );
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

#endif

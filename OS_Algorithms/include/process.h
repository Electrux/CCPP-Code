#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>

static int _process_id = 0;

struct Process
{
	int id;
	char name[ 200 ];
	int duration;
	
#ifdef PRIORITY
	int priority;
#endif
};

struct Process create_process()
{
	struct Process process;

	process.id = _process_id++;
	
	printf( "Enter process name: " );
	scanf( "%s", process.name );

	printf( "Enter process duration: " );
	scanf( "%d", & process.duration );
	
#ifdef PRIORITY
	printf( "Enter process priority: " );
	scanf( "%d", & process.priority );
#endif
	printf( "\n" );

	return process;
}

void display_process( struct Process * process )
{
#ifndef PRIORITY
	printf( "Process ID: %d\tName: %s\tDuration: %d\n",
		process->id,
		process->name,
		process->duration );
#else
	printf( "Process ID: %d\tName: %s\tDuration: %d\tPriority: %d\n",
		process->id,
		process->name,
		process->duration,
		process->priority );
#endif
}

#endif

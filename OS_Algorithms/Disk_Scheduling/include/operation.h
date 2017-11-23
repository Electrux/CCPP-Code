#ifndef OPERATION_H
#define OPERATION_H

#include <stdio.h>
#include <stdlib.h>

struct Operation
{
	int sector;
	float datasize; // in GB
};

struct Operation * create_operation()
{
	struct Operation * operation = ( struct Operation * )
		malloc( sizeof( * operation ) );

	printf( "Enter operation sector: " );
	scanf( "%d", & operation->sector );

	printf( "Enter data size in GiB: " );
	scanf( "%f", & operation->datasize );

	printf( "\n" );

	return operation;
}

#endif

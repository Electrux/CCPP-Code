#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

struct Disk
{
	int sectors; // total sectors
	int rotationdist; // defines how many sectors per rotation
	int rotationtime; // defines time required per rotation
	int seektime;
	float speed; // MBps
};

struct Disk * create_disk()
{
	struct Disk * disk = ( struct Disk * )
		malloc( sizeof( * disk ) );

	printf( "Enter total number of sectors: " );
	scanf( "%d", & disk->sectors );

	printf( "Enter number of sectors covered per rotation: " );
	scanf( "%d", & disk->rotationdist );

	printf( "Enter time in miliseconds required to rotate one time: " );
	scanf( "%d", & disk->rotationtime );

	printf( "Enter time in miliseconds required to seek per unit sector: " );
	scanf( "%d", & disk->seektime );

	printf( "Enter data transfer speed in MiBps: " );
	scanf( "%f", & disk->speed );

	return disk;
}

int get_rotations( struct Disk * disk, int currentsector, int to_sector )
{
	int delta_sector = get_abs( currentsector - to_sector );
	
	return delta_sector / disk->rotationdist;
}

float time_to_get_to_position( struct Disk * disk, int currentsector, int to_sector )
{
	int rot_count = get_rotations( disk, currentsector, to_sector );
	int rot_time = rot_count * disk->rotationtime;

	int delta_sector = get_abs( currentsector - to_sector );
	int sector_time = delta_sector * disk->seektime;

	// Divide by 1000 for seconds.
	return ( rot_time + sector_time ) / 1000.0f;
}

#endif

/*
	Copyright (c) 2019, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef VM_DY_LIB_H
#define VM_DY_LIB_H

#include "uthash.h"

void dy_init();
void dy_deinit();

void * dy_load( const char * file );
void * dy_unload( const char * file );

void * dy_get_sym( const char * file, const char * sym );

#endif // VM_DY_LIB_H
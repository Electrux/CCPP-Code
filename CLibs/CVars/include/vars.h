#ifndef VARS_H
#define VARS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data
{
	char * key;
	void * val;
	size_t val_size;

	struct Data * prev;
	struct Data * next;
};

struct Vars
{
	size_t count;

	struct Data * start;
	struct Data * end;
};

struct Data * alloc_data();

int dealloc_data( struct Data * data );

struct Vars * init_vars();

int delete_vars( struct Vars * vars );

int var_add( struct Vars * vars, const char * key, const void * val );

struct Data * var_get_ptr( const struct Vars * vars, const char * key );

// uses strcpy because we don't want original value to be modified accidentally
int var_get( const struct Vars * vars, const char * key, void * result );

int var_del( struct Vars * vars, const char * key );

#endif // VARS_H

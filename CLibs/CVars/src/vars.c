#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vars.h"

struct Data * alloc_data()
{
	struct Data * data = ( struct Data * )malloc( sizeof( struct Data ) );

	data->prev = NULL;
	data->next = NULL;

	data->key = NULL;
	data->val = NULL;
	data->val_size = -1;

	return data;
}

int dealloc_data( struct Data * data )
{
	if( data == NULL )
		return 0;
	if( data->key != NULL )
		free( data->key );
	if( data->val != NULL )
		free( data->val );
	free( data );

	return 0;
}

struct Vars * init_vars()
{
	struct Vars * vars = ( struct Vars * )malloc( sizeof( struct Vars ) );

	vars->count = 0;
	vars->start = vars->end = NULL;

	return vars;
}

int delete_vars( struct Vars * vars )
{
	if( vars == NULL )
		return 0;

	struct Data * iterator = NULL;
	struct Data * next = vars->start;

	while( next != NULL ) {
		iterator = next;
		next = next->next;

		dealloc_data( iterator );
	}

	free( vars );

	return 0;
}

int var_add( struct Vars * vars, const char * key, const void * val, size_t val_size )
{
	if( vars == NULL || key == NULL || val == NULL )
		return -1;

	if( vars->start == NULL || vars->end == NULL ) {
		vars->start = alloc_data();
		if( vars->start == NULL )
			return -1;
		vars->end = vars->start;
		// Single element, so no front or back, therefore no change to next and prev pointers
	}
	else {
		vars->end->next = alloc_data();
		vars->end->next->prev = vars->end;
		// next pointer will be NULL. This is NOT circular list
		// vars->end->next->next = NULL;
		vars->end = vars->end->next;
	}

	vars->end->key = strdup( key );
	vars->end->val = ( void * ) malloc( val_size );
	memcpy( vars->end->key, val, val_size );
	vars->end->val_size = val_size;
	vars->count += 1;

	return vars->count;
}

struct Data * var_get_ptr( const struct Vars * vars, const char * key )
{
	if( vars == NULL || key == NULL )
		return NULL;

	struct Data * iterator = vars->start;

	while( iterator != NULL ) {
		if( strcmp( iterator->key, key ) == 0 ) {
			return iterator;
		}
		iterator = iterator->next;
	}

	return NULL;
}

// uses strcpy because we don't want original value to be modified accidentally
int var_get( const struct Vars * vars, const char * key, void * result )
{
	if( vars == NULL || key == NULL )
		return -1;

	struct Data * data = var_get_ptr( vars, key );
	if( data == NULL )
		return 1;

	if( result != NULL )
		 memcpy( result, data->val, data->val_size );

	return 0;
}

int var_del( struct Vars * vars, const char * key )
{
	if( vars == NULL || key == NULL )
		return -1;

	struct Data * data = var_get_ptr( vars, key );
	if( data == NULL )
		return 1;

	if( data->prev != NULL )
		data->prev->next = data->next;

	if( data->next != NULL )
		data->next->prev = data->prev;
	if( data == vars->start )
		vars->start = data->next;
	if( data == vars->end )
		vars->end = data->prev;

	dealloc_data( data );
	vars->count -= 1;

	return vars->count;
}

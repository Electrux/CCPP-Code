#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	int size;
	bool isFree;
	struct node * left;
	struct node * right;
} node;

node * root = NULL;

int MAX_ALLOCATION = 1024;

int tot_mem_added = 0;

pthread_mutex_t mtx;

void InitMem()
{
	pthread_mutex_lock( & mtx );
	printf( "The initial memory address is: %p\n", sbrk( 0 ) );
	pthread_mutex_unlock( & mtx );
}

void PrintMemAddr()
{
	pthread_mutex_lock( & mtx );
	printf( "Current memory: %p\n", sbrk( 0 ) );
	pthread_mutex_unlock( & mtx );
}

node * create_new( int data )
{
	node * temp = NULL;
	printf( "Current memory used: %d, Reached data: %d\n", tot_mem_added, data );
	if( tot_mem_added + sizeof( node ) + data >= MAX_ALLOCATION )
		return NULL;
	printf( "Allocating new memory for: %d\n", data );
	tot_mem_added += sizeof( node ) + data;
	pthread_mutex_lock( & mtx );
	temp = ( node * )sbrk( sizeof( node ) + data );
	pthread_mutex_unlock( & mtx );
	temp->size = data;
	temp->isFree = false;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void * Insert( int data )
{
	if( root == NULL ) {
		root = create_new( data );
		if( root == NULL )
			return NULL;
		return ( void * ) & ( * root );
	}
	// n is the traveler
	node * n = root;

begin:
	if( n->size < data ) {
		// go right
		if( n->right == NULL ) {
			n->right = create_new( data );
			if( n->right == NULL )
				return NULL;
			n = n->right;
		}
		else {
			n = n->right;
			goto begin;
		}
	}
	else {
		// go left
		if( n->left == NULL ) {
			n->left = create_new( data );
			if( n->left == NULL )
				return NULL;
			n = n->left;
		}
		else {
			n = n->left;
			goto begin;
		}
	}

	return ( void * ) & ( * n );
}

void * FindBestFit( int data )
{
	// n is the traveler
	node * n = root;

best_begin:
	if( n == NULL ) {
		return NULL;
	}

	if( n->size > data ) {
		if( n->isFree ) {
			printf( "Allocating pre-existing memory location for: %d held formerly by: %d\n", data, n->size );
			n->size = data;
			n->isFree = false;
			return ( void * )n;
		}
		n = n->left;
		goto best_begin;
	}
	else {
		n = n->right;
		goto best_begin;
	}
}

void * NEW( int data )
{
	void * temp;
	if( ( temp = FindBestFit( data ) ) == NULL ) {
		// insert as a new element if no best was found
		temp = Insert( data );
	}

	if( temp == NULL )
		return NULL;

	// convert to char * is necessary to allow 1 byte shifts in the pointer
	return ( void * )( ( ( char * ) temp ) + sizeof( node ) );
}

void FreeMem()
{
	root = NULL;
	pthread_mutex_lock( & mtx );
	sbrk( -tot_mem_added );
	pthread_mutex_unlock( & mtx );
	printf( "Final memory: %p\n", sbrk( 0 ) );
}

void DEL( void * loc )
{
	printf( "Deleted variable: %d at: %p\n", ( ( node * )( ( ( char * ) loc ) - sizeof( node ) ) )->size, ( ( ( char * ) loc ) - sizeof( node ) ) );
	( ( node * )( ( ( char * ) loc ) - sizeof( node ) ) )->isFree = true;
}

void Traverse( node * n )
{
	if( n == NULL )
		return;

	Traverse( n->left );
	Traverse( n->right );

	printf( "%d ", n->size );
}

int main( int argc, char * argv[] )
{
	//           100
	//         /     \
	//        66(50)  144(123)
	//        \         \
	//         78        200
	int data[] = { 100, 66, 144, 50, 78, 123, 888, 200 };

	printf( "******** Initial memory address ********\n" );
	InitMem();

	int i;
	void * memPtr[ sizeof( data ) / sizeof( int ) ];

	for ( i = 0; i < sizeof( data ) / sizeof( int ); i++ ) {
		if ( i == 3 ) {
			DEL( memPtr[ 1 ] );
			printf( "Deleted %d\n", data[ 1 ] );
		}

		printf( "Inserting %d\n", data[ i ] );
		memPtr[ i ] = NEW( data[ i ] );
		PrintMemAddr();
		if ( memPtr[ i ] == NULL ) {
			printf( "Error - Not enough memory for %d\n", data[ i ] );
		} else {
			memset( memPtr[ i ], 0, data[ i ] );
		}

		if( i == 4 ) {
			DEL( memPtr[ 2 ] );
			printf( "Deleted %d\n", data[ 2 ] );
		}
	}

	printf("******** Traverse ********\n");
	Traverse(root);

	printf("\n******** Final memory address ********\n");
	FreeMem();

	return 0;
}
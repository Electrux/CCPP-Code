#include <iostream>
#include <vector>
#include <climits>

void push( int * arr, int val, int & size )
{
	for( int i = size; i >= 1; --i ) {
		arr[ i ] = arr[ i - 1 ];
	}
	++size;
	arr[ 0 ] = val;
}

int pop( int * arr, int & size )
{
	int res = arr[ 0 ];
	for( int i = 0; i < size - 1; ++i ) {
		arr[ i ] = arr[ i + 1 ];
	}
	--size;
	return res;
}

int get_min( int * arr, int & size )
{
	int total = size;
	int tmp_arr[ size ];
	int tmp_size = 0;
	int min = INT_MAX;
	for( int i = 0; i < total; ++i ) {
		if( min > arr[ 0 ] ) min = arr[ 0 ];
		push( tmp_arr, pop( arr, size ), tmp_size );
	}
	for( int i = 0; i < total; ++i ) {
		push( arr, pop( tmp_arr, tmp_size ), size );
	}
	return min;
}

int main()
{
	int arr[] = { 5, 4, 3, 1, 2 };
	int size = 5;
	std::cout << "Original stack: ";
	for( int i = 0; i < size; ++i ) std::cout << arr[ i ] << " ";
	std::cout << "\n";
	std::cout << "Min: " << get_min( arr, size ) << "\n";
	std::cout << "Final stack: ";
	for( int i = 0; i < size; ++i ) std::cout << arr[ i ] << " ";
	std::cout << "\n";
}

#include <iostream>
#include <vector>

void disp_arr( const std::vector< int > & arr )
{
	for( auto & i : arr ) std::cout << i << " ";
}

std::vector< int > merge( std::vector< int > a,
			std::vector< int > b )
{
	std::vector< int > res;
	int i = 0, j = 0;
	while( i < a.size() && j < b.size() ) {
		if( a[ i ] < b[ j ] ) {
			res.push_back( a[ i++ ] );
		} else {
			res.push_back( b[ j++ ] );
		}
	}
	while( i < a.size() ) res.push_back( a[ i++ ] );
	while( j < b.size() ) res.push_back( b[ j++ ] );
	return res;
}

std::vector< int > merge_sort( std::vector< int > arr )
{
	if( arr.size() <= 1 ) return arr;
	int mid = arr.size() / 2;
	std::vector< int > arr1, arr2;
	for( int i = 0; i < mid; ++i )
		arr1.push_back( arr[ i ] );
	for( int j = mid; j < arr.size(); ++j )
		arr2.push_back( arr[ j ] );
	auto res1 = merge_sort( arr1 );
	auto res2 = merge_sort( arr2 );
	return merge( res1, res2 );
}

int main()
{
	std::vector< int > arr = { 5, 1, 3, 4, 2 };
	std::cout << "beginning: ";
	disp_arr( arr );
	std::cout << "\n";
	auto res = merge_sort( arr );
	std::cout << "end: ";
	disp_arr( res );
	std::cout << "\n";
	return 0;
}

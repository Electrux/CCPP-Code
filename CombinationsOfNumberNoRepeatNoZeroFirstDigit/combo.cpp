#include <iostream>
#include <unordered_map>

unsigned long long fact( int n )
{
	unsigned long long f = n;
	while( --n ) f *= n;
	return f;
}

unsigned long long find_combinations( const std::string & str )
{
	int zero_count = 0;
	for( auto & s : str ) {
		if( s == '0' ) ++zero_count;
	}

	std::unordered_map< char, int > repeats;
	for( auto & s : str ) {
		if( repeats.find( s ) != repeats.end() ) ++repeats[ s ];
		else repeats[ s ] = 1;
	}

	unsigned long long rep = 1;
	for( auto & repeat : repeats ) {
		rep *= fact( repeat.second );
	}

	int len = str.size();
	return ( len - zero_count ) * fact( len - 1 ) / rep;
}

int main()
{
	std::string s;
	std::cout << "Enter the string: ";
	std::cin >> s;
	std::cout << "Total count: " << find_combinations( s ) << "\n";
	return 0;
}

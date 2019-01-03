#include <iostream>
#include <string>

void find_permutations( std::string first, std::string others )
{
	if( others.size() <= 0 ) {
		std::cout << first << "\n";
		return;
	}
	int len = others.size();
	for( int i = 0; i < len; ++i ) {
		std::string sub = others;
		std::string first_tmp = first;
		first_tmp += sub[ i ];
		sub.erase( sub.begin() + i );
		find_permutations( first_tmp, sub );
	}
}

int main()
{
	std::string s = "chirag";
	int len = s.size();
	for( int i = 0; i < len; ++i ) {
		std::string sub = s;
		sub.erase( sub.begin() + i );
		find_permutations( std::string( 1, s[ i ] ), sub );
	}
	return 0;
}

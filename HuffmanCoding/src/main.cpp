#include <iostream>
#include "../include/HuffmanCode.hpp"

std::string GetBinary( char c )
{
	std::string temp;

	int val = ( int ) c;

	while( val > 0 ) {
		temp += std::to_string( val % 2 );
		val /= 2;
	}

	std::string finalstr;

	for( auto revch = temp.rbegin(); revch != temp.rend(); ++revch )
		finalstr += *revch;

	return finalstr;
}

// Algorithm driver.
int main(int argc, char *argv[])
{
	std::string test_str = "This is a test string";
	
	HuffmanCoding hcoding;
	
	hcoding.insert( test_str );
	
	hcoding.generate_huffman_coding();
	
	std::cout << "\n\n\nFor statement: " << test_str << "\n";
	hcoding.display_huffman_codes();

	auto huffmancode = hcoding.get_huffman_codes();

	std::cout << "\nThe huffman code is:\n";

	int count = 0;
	for( auto ch : test_str ) {
		count += huffmancode[ ch ].size();
		std::cout << huffmancode[ ch ];
	}

	std::cout << "\nSize: " << count << "\n";
	std::cout << "\n";

	std::cout << "\nThe binary of the statement is:\n";

	count = 0;
	
	for( auto ch : test_str ) {
		count += GetBinary( ch ).size();
		std::cout << GetBinary( ch );
	}

	std::cout << "\nCount = " << count << "\n";
	std::cout << "\n";
	
	return 0;
}

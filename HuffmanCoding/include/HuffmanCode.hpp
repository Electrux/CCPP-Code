//
// Created by electrux on 7/24/17.
//

#ifndef HUFFMANCODING_HUFFMANCODE_HPP
#define HUFFMANCODING_HUFFMANCODE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


// This structure defines the symbol and number of times it occurs in the given string.
// Note that symbol is of type string so as to enable multiple symbols ( single characters )
// to be stored when addition/combination is done in the Huffman Code Generation.
struct SymbolCount
{
	int count;
	std::string symbol;
};

// The greater than operator definition for SymbolCount structure to be used in sorting.
bool operator >(SymbolCount a, SymbolCount b)
{
	return a.count > b.count;
}

// Main Huffman Coding class to handle every related thing.
class HuffmanCoding
{
	// SymbolCount vector to store all the symbols occured.
	std::vector< SymbolCount > symbols;
	
	// Map for each symbol to its respective huffman code ( string ).
	std::map< char, std::string > huffmancode;
	
	// SymbolCount swap function to be used in sorting.
	void swap( SymbolCount &a, SymbolCount &b )
	{
		SymbolCount temp;
		
		temp = a;
		a = b;
		b = temp;
	}
	
	// Sort function to sort a SymbolCount vector in ascending order.
	// This sort function is simply bubble sort.
	void sort_vector( std::vector< SymbolCount > &vec )
	{
		for( size_t i = 0; i < vec.size(); ++i )
		{
			for( size_t j = 0; j < vec.size() - i - 1; ++j )
			{
				if( vec[ j ] > vec[ j + 1 ] )
					this->swap( vec[ j ], vec[ j + 1 ] );
			}
		}
	}

public:
	
	// Insert function to insert the entire data as string which shall be used to generate
	// the huffman code.
	void insert( std::string data )
	{
		// The location of the string in which is present symbol/character in SymbolCount
		// vector ( loc[ 0 ] ) and in the string, the location of symbol itself ( loc[ 1 ] ).
		int loc[ 2 ];
		
		// For each character in the string data.
		for( auto ch : data )
		{
			// Fetch the location, in loc, of the character from the string in SymbolCount
			// structure, in the SymbolCount vector.
			if( !this->find_symbol( ch, loc[ 0 ], loc[ 1 ] ) )
			{
				// If cant find location, meaning it does not exist already, in which case,
				// enter it in the SymbolCount vector with count = 1, and string = the character.
				// Note that the string constructor to convert char to string requires the number
				// of times the character is repeated as its first parameter ( here 1 ).
				symbols.push_back( { 1, std::string( 1, ch ) } );
				huffmancode[ ch ] = std::string();
			}
			else
			{
				// If the character is found, increment its count in its location in SymbolCount vector.
				symbols[ loc[ 0 ] ].count++;
			}
		}
		
		// Sort the SymbolCount vector to make it ready to be applied the huffman coding algorithm on.
		this->sort_vector( symbols );
	}
	
	// Generate the huffman codes for all symbols present in the SymbolCount vector.
	void generate_huffman_coding()
	{
		// Temporary objects to pick the first, and second element in the SymbolCount vector
		// and one for combining both of the above elements.
		SymbolCount first, second;
		SymbolCount combine;
		
		// New temporary SymbolCount vector of all symbols to modify the data for the algorithm
		// without tampering with the original vector.
		std::vector< SymbolCount > temp = symbols;
		
		// While there is more than one element in the temporary vector, perform the loop.
		while( temp.size() > 1 )
		{
			// Move the first element of temp in first variable.
			first = *temp.begin();
			// Move the second element int second variable after erasing the first element
			// from the temporary vector.
			second = *temp.erase( temp.begin() );
			// Erase the second element ( now first ) from the temporary vector.
			temp.erase( temp.begin() );
			
			// Use this statement to show the current symbols being used in loop.
			//std::cout << "First: " << first.symbol << "\tSecond: " << second.symbol << "\n";
			
			// Add the count and symbol of the first and second element and store in combine variable.
			combine.count = first.count + second.count;
			combine.symbol = first.symbol + second.symbol;
			
			// Update the huffman code strings for the first and second symbol( s ).
			// The first symbol is on left side, therefore represented as zero,
			// and second symbol is on right side, and therefore represents one.
			this->update_huffman_code( first.symbol, second.symbol );
			
			// Insert the combine variable in the beginning of string.
			// Beginning because then it will work as expected ( it will take the combine variable
			// first if the counts are equal for it and other symbols ).
			temp.insert( temp.begin(), combine );
			
			// Sort the temporary vector.
			this->sort_vector( temp );
		}
		
		// Reverse all the huffman code strings to give the actual strings.
		for( auto huff_code : huffmancode )
		{
			std::reverse( huff_code.second.begin(), huff_code.second.end() );
		}
	}
	
	// Update the symbol huffman code in the huffmancode map.
	void update_huffman_code( std::string left_symbols, std::string right_symbols )
	{
		// For all symbols in left parameter, append zero to their strings in map.
		for( auto left_symbol : left_symbols )
			huffmancode[ left_symbol ] += std::to_string( 0 );
		
		// Same as above for the right symbols and append one here.
		for( auto right_symbol : right_symbols )
			huffmancode[ right_symbol ] += std::to_string( 1 );
	}
	
	// Finds the symbol ( c ) in the entire SymbolCount vector, and return its location
	// in loci, and locj.
	bool find_symbol( char c, int &loci, int &locj )
	{
		// Set the ith and jth location variables to zero.
		loci = 0, locj = 0;
		
		// For each SymbolCount in SymbolCount vector.
		for(auto symbol : symbols)
		{
			// For each character in the string symbol of each SymbolCount.
			for(auto ch : symbol.symbol)
			{
				// If the character from the string is the required character, return true and,
				// indirectly, its position.
				if( ch == c )
					return true;
				
				// Increment the jth location counter.
				++locj;
			}
			
			// Increment the ith location counter.
			++loci;
		}
		
		// If this place is reached, the symbol does not exist already, thereby return false.
		return false;
	}
	
	
	// Display the huffman code map, ie, the symbol and its huffman code.
	void display_huffman_codes()
	{
		std::cout << "\n\nHuffman Codes:\n\n";
		
		for( auto huff_code : huffmancode )
			std::cout << "Character: " << huff_code.first << "\tCode: " << huff_code.second << "\n";
		
		std::cout << "\n\n";
	}

	std::map< char, std::string > get_huffman_codes() { return huffmancode; }
	
};


#endif //HUFFMANCODING_HUFFMANCODE_HPP

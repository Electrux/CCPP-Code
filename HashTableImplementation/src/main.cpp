#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "../include/HashTable.hpp"

// Max number of strings for the test dataset
const int MAX_STR_COUNT = 1000000;

int main()
{
	// File from which to read the test dataset.
	std::fstream file( "../src/words.txt", std::ios::in );

	// Each lines in its own array index.
	std::string *lines;
	lines = new std::string[ MAX_STR_COUNT ];

	// Array indexer for reading the liness.
	int ctr = 0;
	while( std::getline( file, lines[ ctr ] ) && ctr < MAX_STR_COUNT )
		ctr++;

	// Loop for test cases. There are 100 test cases.
	for( int i = 1; i <= 100; ++i ) {

		// Start the timer to note the time taken to execute the test case.
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

		//Create hash table and allocate the memory for hashkeys.
		Electrux::HashTable< std::string, std::string > test;
		Electrux::HashKey< std::string > *keys;
		keys = new Electrux::HashKey< std::string >[ MAX_STR_COUNT / 2 ];

		int currmax = i * 10000;

		// Insert the strings in the hashkeys.
		for( int j = 0; j < currmax; j += 2 )
			keys[ j / 2 ] = lines[ j ];

		// Insert the hashkeys along with their respective values in the hash table.
		for( int j = 0; j < currmax; j += 2 )
			test.Insert( keys[ j / 2 ], lines[ (j + 1)/2 ] );

		// Retrieve all the keys from the hash table.
		//for( int i = 0; i < currmax / 2; ++i )
		//	test.Get( keys[ i ] );

		// Stop the clock marking the finish of the test.
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

		// Check the difference in the starting and ending times, in milliseconds.
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>( end - start );

		// Print the details of the hashtable and the time difference in milliseconds.
		std::cout << "Table Count: " << test.GetCtr() << "\tPair Count: " << test.GetCount() << "\tTime taken: " << diff.count() << "ms" << "\n";
	}

	// Free the space consumed by the lines - string array.
	delete[] lines;

	// Exit the program.
	return 0;
}

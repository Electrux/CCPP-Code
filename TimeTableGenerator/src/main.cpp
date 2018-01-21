#include <iostream>
#include <string>

#include "../include/DataStructure.hpp"
#include "../include/DisplayFuncs.hpp"
#include "../include/FileHandler.hpp"
#include "../include/SolutionFinder.hpp"

int main()
{
	int rows, cols, tables;
	std::string filename;

	std::cout << "Enter the number of tables: ";
	std::cin >> tables;
	std::cout << "Enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Enter the number of columns: ";
	std::cin >> cols;

	std::cout << "Enter the file from which to load the data: ";
	std::cin >> filename;

	std::cout << "\n";

	auto alldata = RetrieveFile( filename );
	if( alldata.empty() )
		return 1;

	return !( int )FindSolution( tables, rows, cols, alldata );
}
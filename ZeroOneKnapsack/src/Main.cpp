#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "ZOKnapSack.hpp"

int main()
{
	std::system("cls");

	Electrux::ZOKnapSack sack;
	///*
	sack.Insert("1", 1, 1);
	sack.Insert("2", 2, 2);
	sack.Insert("3", 4, 3);
	sack.Insert("4", 2, 2);
	sack.Insert("5", 5, 5);


	Electrux::ZOKnapSack::ItemSet sol = sack.GenerateBestSolution(10);
	//*/
	/*
	sack.Insert("1", 1, 2);
	sack.Insert("2", 2, 3);
	sack.Insert("3", 5, 4);

	ItemSet sol = sack.GenerateBestSolution(6);
	*/


	std::cout << "Final solution: ";
	for (auto it = sol.prev.begin(); it != sol.prev.end(); ++it)
	{
		std::cout << *it << "->";
	}
	std::cout << "X\n\n";

	std::cout << "Total profit: " << sol.profit << "\tWeight: " << sol.weight;

	std::cout << "\n\n";


	std::system("pause");
	return 0;
}
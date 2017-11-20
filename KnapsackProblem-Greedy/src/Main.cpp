#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>

#include "KnapSack.hpp"

int main()
{
	std::system("cls");

	ItemDB items;
	
	//Args: Name, Profit, Weight
	items.Insert("1", 10, 2);
	items.Insert("2", 5, 3);
	items.Insert("3", 15, 5);
	items.Insert("4", 7, 7);
	items.Insert("5", 6, 1);
	items.Insert("6", 18, 4);
	items.Insert("7", 3, 1);

	//Args: Total weight
	items.GenerateBestDistribution(15);

	items.Clear();

	items.Insert("1", 30, 5);
	items.Insert("2", 20, 10);
	items.Insert("3", 100, 20);
	items.Insert("4", 90, 30);
	items.Insert("5", 160, 40);

	items.GenerateBestDistribution(60);

	items.Clear();

	items.Insert("1", 30, 18);
	items.Insert("2", 21, 15);
	items.Insert("3", 18, 10);

	items.GenerateBestDistribution(20);

	items.Clear();

	std::system("pause");
	return 0;
}
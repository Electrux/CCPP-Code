#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "JobSequencer.hpp"


int main()
{
	std::system("cls");

	JobPool jobs;

	//Args: Name, Profit, Deadline
	jobs.Insert("1", 15, 7);
	jobs.Insert("2", 20, 2);
	jobs.Insert("3", 30, 5);
	jobs.Insert("4", 18, 3);
	jobs.Insert("5", 18, 4);
	jobs.Insert("6", 10, 5);
	jobs.Insert("7", 23, 2);
	jobs.Insert("8", 16, 7);
	jobs.Insert("9", 25, 3);

	
	int maxprofit = jobs.GenerateBestDistribution();

	jobs.DisplayDistribution();
	jobs.DisplayJobs();
	std::cout << "Net Profit: " << maxprofit << "\n\n";

	jobs.Clear();

	std::system("pause");
	return 0;
}
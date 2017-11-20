#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <thread>
#include <future>
#include <chrono>
#include "XInt.hpp"


xint getFact(unsigned long long num2, unsigned long long to) {
	xint temp;
	temp = std::string("1");
	while (num2 >= to)
	{
		temp *= num2;
		num2--;
	}
	return temp;
}


int main()
{
	system("cls");
	xint fact;
	unsigned long long num;
	unsigned int cores = 2;
	std::cout << "Enter factorial of: ";
	std::cin >> num;
	fact = std::string("1");
	std::cout << "Enter number of CPU cores (1, 2, or 4): ";
	std::cin >> cores;
	std::time_t start = std::clock();
	if (cores == 1)
	{
		while (num > 1)
		{

			fact *= num;
			num--;
		}
	}
	else if (cores == 2)
	{
		std::future<xint> future1, future2;
		future1 = std::async(getFact, num, ((num * 3) / 4) + 1);
		future2 = std::async(getFact, ((num * 3) / 4), 2);
		fact = future2.get() * future1.get();
	}
	else if (cores == 4)
	{
		std::future<xint> future[4];
		future[0] = std::async(getFact, num, ((num * 3) / 4) + 1);
		future[1] = std::async(getFact, ((num * 3) / 4), (num / 2) + 1);
		future[2] = std::async(getFact, num / 2, ((num * 1) / 4) + 1);
		future[3] = std::async(getFact, ((num * 1) / 4), 2);
		fact *= future[3].get();
		fact *= future[2].get();
		fact *= future[1].get();
		fact *= future[0].get();
	}
	std::time_t end = std::clock();
	long double time1 = (std::chrono::duration<long double, std::milli>(end - start).count());
	std::cout << "Factorial: " << fact << "\nTime1: " << time1;
	system("pause");
	return 0;
}
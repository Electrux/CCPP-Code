#include <iostream>
#include <queue>
#include <iomanip>
#include <random>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>


std::mutex RNGMutex, CoutMutex;

const int total = 100'000'00,
			threadscount = 10,
			rngamount = total / threadscount / 10;

void LockMutex(std::mutex &mutex)
{
	while (true)
	{
		if (mutex.try_lock())
			break;
	}
}

void UnlockMutex(std::mutex &mutex)
{
	mutex.unlock();
}

void FillRNG(std::queue<int> &id, int seed, int amount)
{
	std::srand(seed);
	for (int i = 0; i < amount; ++i)
	{
		id.push(std::rand() % 6 + 1);
	}
}

int wins[threadscount] = { 0 },
	winsfirst[threadscount] = { 0 },
	lose2312[threadscount] = { 0 },
	lose[threadscount] = { 0 };

int winstot = 0,
	winsfirsttot = 0,
	lose2312tot = 0,
	losetot = 0;

void Play100Mill(int id)
{
	int roll;

	std::queue<int> rng;

	std::vector<int> points;

	for (int i = 0; i < total/threadscount; ++i)
	{
		if (rng.empty())
		{
			LockMutex(RNGMutex);
			FillRNG(rng, id, rngamount);
			UnlockMutex(RNGMutex);
		}

		roll = rng.front();
		rng.pop();

		roll += rng.front();
		rng.pop();

		if (roll == 7 || roll == 11)
		{
			winsfirst[id]++;
		}
		
		else if (roll == 2 || roll == 3 || roll == 12)
		{
			lose2312[id]++;
		}
		
		else
		{
			points.push_back(roll);
		}
	}

	for (auto point = points.begin(); point != points.end();)
	{
		if (rng.empty())
		{
			LockMutex(RNGMutex);
			FillRNG(rng, id, rngamount);
			UnlockMutex(RNGMutex);
		}

		roll = rng.front();
		rng.pop();

		roll += rng.front();
		rng.pop();

		if (roll == *point)
		{
			wins[id]++;
			point = points.erase(point);
		}
		
		else if (roll == 7)
		{
			lose[id]++;
			point = points.erase(point);
		}
	}

	std::cout << "Thread: " << id << " finished!\n";
}

int main()
{
	int threadid = 0;

	std::vector<std::thread> threads;

	for (int i = 0; i < threadscount; ++i)
	{
		threads.push_back(std::thread(Play100Mill, i));
	}

	for (auto &thread : threads)
	{
		thread.join();
	}
	
	std::cout << "\n\n";

	for (int i = 0; i < threadscount; ++i)
	{
		winstot += wins[i];
		winsfirsttot += winsfirst[i];
		lose2312tot += lose2312[i];
		losetot += lose[i];

	}

	std::cout << std::left
		<< "Wins: " << (winstot + winsfirsttot) * 100 / (float)total << std::setw(14) << "%"
		<< "Wins First: " << winsfirsttot * 100 / (float)total << std::setw(14) << "%"
		<< "Lose 2/3/12: " << lose2312tot * 100 / (float)total << std::setw(14) << "%"
		<< "Lose: " << losetot * 100 / (float)total << std::setw(14) << "%"
		<< "\n";

	std::system("pause");

	return 0;
}
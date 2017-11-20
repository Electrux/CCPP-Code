#pragma once

//Job contents

struct TimeSlot
{
	int t1,
		t2;
};

struct Job
{
	int id;

	std::string name;

	float profit;
	
	int	deadline;
	TimeSlot timeslot;
};

bool operator <(TimeSlot a, TimeSlot b)
{
	if (a.t1 < b.t1) return true;
	return false;
}

//Job manager

class JobPool
{
	std::vector<Job> jobs;
	std::map<TimeSlot, int> timeslots;

	bool SortByProfit() //Sorts the jobs in descending order with respect to their respective weights.
	{
		if (jobs.empty()) return false;

		Job job;

		for (size_t i = 0; i < jobs.size(); ++i) //Starts from the beginning of the list.
		{
			for (size_t j = 0; j < jobs.size() - i - 1; ++j)
			{
				if (jobs[j].profit < jobs[j + 1].profit)
				{
					job = jobs[j];
					jobs[j] = jobs[j + 1];
					jobs[j + 1] = job;
				}
			}
		}

		return true;
	}

	bool SortByID() //Sorts the jobs in ascending order with respect to their respective ids.
	{
		if (jobs.empty()) return false;

		Job job;

		for (size_t i = 0; i < jobs.size(); ++i) //Starts from the beginning of the list.
		{
			for (size_t j = 0; j < jobs.size() - i - 1; ++j)
			{
				if (jobs[j].id > jobs[j + 1].id)
				{
					job = jobs[j];
					jobs[j] = jobs[j + 1];
					jobs[j + 1] = job;
				}
			}
		}

		return true;
	}

	int GetMaxDeadline()
	{
		int dead = 0;
		
		for (size_t i = 0; i < jobs.size(); ++i)
		{
			if (dead < jobs[i].deadline)
				dead = jobs[i].deadline;
		}

		return dead;
	}

	std::map<TimeSlot, int> GenerateTimeSlots(int maxdeadline)
	{
		std::map<TimeSlot, int> tempslots;

		TimeSlot temp;

		for (int i = 0; i < maxdeadline; ++i)
		{
			temp.t1 = i;
			temp.t2 = i + 1;

			tempslots[temp] = -1;
		}

		return tempslots;
	}

	void FeedJobsInTimeSlots(std::map<TimeSlot, int> &slots, Job &job, TimeSlot &slot)
	{
		int deadline = job.deadline;
		bool done = false;

		slot.t1 = -1;
		slot.t2 = -1;

		TimeSlot temp;

		for (int i = deadline - 1; i >= 0; --i)
		{
			temp.t1 = i;
			temp.t2 = i + 1;

			if (slots[temp] == -1)
			{
				slots[temp] = job.id;
				
				slot.t1 = i;
				slot.t2 = i + 1;

				done = true;
				break;
			}
		}
	}

public:

	void Insert(std::string name, float profit, int deadline)
	{
		Job job;

		job.id = jobs.size();

		job.name = name;
		job.profit = profit;
		job.deadline = deadline;

		job.timeslot.t1 = -1;
		job.timeslot.t2 = -1;

		jobs.push_back(job);
	}

	bool Delete(std::string name)
	{
		std::vector<Job>::iterator torem;
		bool rem = false;

		for (auto it = jobs.begin(); it != jobs.end(); ++it)
		{
			if (it->name == name)
			{
				rem = true;
				torem = it;
				break;
			}
		}

		if (rem == true)
		{
			jobs.erase(torem);
			int count = 0;

			this->SortByID();

			for (auto it = jobs.begin(); it != jobs.end(); ++it)
			{
				it->id = count;
				++count;
			}
		}

		return rem;
	}

	void Clear()
	{
		jobs.clear();
		timeslots.clear();
	}

	std::vector<Job> GetJobs()
	{
		return jobs;
	}

	void DisplayJobs()
	{
		std::cout << "\n\n************ Contents ************\n\n";

		if (jobs.empty())
		{
			std::cout << "ERROR: No available data in the list!!!\n\n";
		}
		else
		{
			for (auto it = jobs.begin(); it != jobs.end(); ++it)
			{
				if (it->timeslot.t1 == -1 || it->timeslot.t2 == -1)
					std::cout << std::left
						<< "Job: " << std::setw(18) << it->name
						<< "Profit: " << std::setw(18) << it->profit
						<< "Time Slot: " << std::setw(18) << "None"
						<< "\n";
				else
					std::cout << std::left
						<< "Job: " << std::setw(18) << it->name
						<< "Profit: " << std::setw(18) << it->profit
						<< "Time Slot: " << it->timeslot.t1 << " - " << std::setw(18) << it->timeslot.t2
						<< "\n";
			}
		}

		std::cout << "\n\n**********************************\n\n";
	}

	void DisplayDistribution()
	{
		std::cout << "\n\n************ Contents ************\n\n";

		if (timeslots.empty())
		{
			std::cout << "ERROR: No available data in the list!!!\n\n";
		}
		else
		{
			for (auto it = timeslots.begin(); it != timeslots.end(); ++it)
			{
				std::cout << std::left
					<< "Time Slot: " << it->first.t1 << " - " << std::setw(18) << it->first.t2
					<< "Job: " << std::setw(18) << jobs[it->second].name
					<< "\n";
			}
		}

		std::cout << "\n\n**********************************\n\n";
	}

	int GenerateBestDistribution()
	{
		int maxdeadline = this->GetMaxDeadline();
		
		TimeSlot fedreturnval;

		float maxprofit = 0.0;
		std::cout << "Max deadline = " << maxdeadline << "\n";
		this->timeslots = this->GenerateTimeSlots(maxdeadline);

		this->SortByProfit();

		for (auto it = jobs.begin(); it != jobs.end(); ++it)
		{
			this->FeedJobsInTimeSlots(this->timeslots, *it, fedreturnval);

			if (fedreturnval.t1 != -1 && fedreturnval.t2 != -1)
			{
				maxprofit += it->profit;
			}

			it->timeslot.t1 = fedreturnval.t1;
			it->timeslot.t2 = fedreturnval.t2;
		}

		this->SortByID();

		return maxprofit;
	}

};

#pragma once

//Item contents

struct Item
{
	int id;

	std::string name;

	float profit,
		weight,
		newprofit,
		newweight,
		ppuw, //Profit Per Unit Weight
		mult; //Multiplier for adjusting to max capacity available
};


//Item manager

class ItemDB
{
	std::vector<Item> items;

	bool Swap(size_t pos1, size_t pos2)
	{
		if (pos1 >= items.size() || pos1 < 0 ||
			pos2 >= items.size() || pos2 < 0) return false;

		Item item;

		item = items[pos1];
		items[pos1] = items[pos2];
		items[pos2] = item;

		return true;
	}

	bool SortByPPW() //Sorts the items in descending order with respect to their respective weights.
	{
		if (items.empty()) return false;
		
		Item item;

		for (size_t i = 0; i < items.size(); ++i) //Starts from the beginning of the list.
		{
			for (size_t j = 0; j < items.size() - i - 1; ++j)
			{
				if (items[j].ppuw < items[j + 1].ppuw)
					this->Swap( j, j + 1 );
			}
		}

		return true;
	}

	bool SortByID() //Sorts the items in ascending order with respect to their respective ids.
	{
		if (items.empty()) return false;

		Item item;

		for (size_t i = 0; i < items.size(); ++i) //Starts from the beginning of the list.
		{
			for (size_t j = 0; j < items.size() - i - 1; ++j)
			{
				if (items[j].id > items[j + 1].id)
					this->Swap( j, j + 1 );
			}
		}

		return true;
	}

	float GetOptimalMultiplier(float weight, float &totalw)
	{
		if (totalw <= 0.0) return 0.0;

		float optimult;

		if (weight > totalw)
		{
			optimult = totalw / weight;
			totalw = 0.0;
		}
		else
		{
			optimult = 1.0;
			totalw -= weight;
		}

		return optimult;
	}

public:

	void Insert(std::string name, float profit, float weight)
	{
		Item item;

		item.id = items.size();

		item.name = name;
		item.profit = profit;
		item.weight = weight;
		item.ppuw = profit / weight;

		item.mult = -1.0;
		item.newprofit = -1.0;
		item.newweight = -1.0;

		items.push_back(item);
	}

	bool Delete(std::string name)
	{
		std::vector<Item>::iterator torem;
		bool rem = false;

		for (auto it = items.begin(); it != items.end(); ++it)
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
			items.erase(torem);
			int count = 0;
			
			this->SortByID();

			for (auto it = items.begin(); it != items.end(); ++it)
			{
				it->id = count;
				++count;
			}
		}

		return rem;
	}

	void Clear()
	{
		items.clear();
	}

	std::vector<Item> GetItems()
	{
		return items;
	}

	void DisplayItems(std::vector<Item> vec, bool showquan = false)
	{
		std::cout << "\n\n************ Contents ************\n\n";

		if (vec.empty())
		{
			std::cout << "ERROR: No available data in the list!!!\n\n";
		}
		else
		{
			for (auto it = vec.begin(); it != vec.end(); ++it)
			{
				if (showquan == false || it->mult == -1.0)
					std::cout << std::left
						//<< "ID: " << std::setw(18) << it->id
						<< "Item: " << std::setw(18) << it->name
						<< "Profit: " << std::setw(18) << it->profit
						<< "Weight: " << std::setw(18) << it->weight
						<< "PPUW: " << it->ppuw
						<< "\n";
				else
					std::cout << std::left
						//<< "ID: " << std::setw(18) << it->id
						<< "Item: " << std::setw(18) << it->name
						<< "New Profit: " << std::setw(18) << it->newprofit
						<< "New Weight: " << std::setw(18) << it->newweight
						<< "PPUW: " << it->ppuw
						<< "\n";
			}
		}

		std::cout << "\n\n**********************************\n\n";
	}

	void GenerateBestDistribution(float totalweight) //totwt is redundant....
	{
		float totprofit = 0.0, totwt = 0.0, availablewt = totalweight;

		this->SortByPPW();

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			it->mult = this->GetOptimalMultiplier(it->weight, availablewt);

			it->newprofit = it->profit * it->mult;
			it->newweight = it->weight * it->mult;

			totprofit += it->newprofit;
			totwt += it->newweight;
		}

		this->SortByID();

		this->DisplayItems(this->items, true);

		std::cout << "Net Weight: " << totwt << "\nNet Profit: " << totprofit << "\n\n\n\n";
	}

};

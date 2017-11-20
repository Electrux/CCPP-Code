#pragma once

namespace Electrux
{
	class ZOKnapSack
	{
		struct Item
		{
			int id;

			std::string name;

			float profit, weight;
		};

		std::vector<Item> items;

	public:

		struct ItemSet
		{
			float profit, weight;

			std::vector<int> prev;
		};

		bool Insert(std::string name, float profit, float weight)
		{
			if (this->ItemExists(name)) return false;

			Item item;

			item.id = items.size() + 1;
			item.name = name;
			item.profit = profit;
			item.weight = weight;

			this->items.push_back(item);

			return true;
		}

		bool Delete(std::string name)
		{
			std::vector<Item>::iterator it = this->GetItemLocation(name);
			if (it == this->items.end()) return false;

			int loc = it->id;

			for (auto it2 = it + 1; it2 != this->items.end(); ++it2)
			{
				it2->id = loc;
				loc++;
			}

			this->items.erase(it);

			return true;
		}

		ItemSet GenerateBestSolution(int weight)
		{
			std::vector<ItemSet> first, next, finale;

			ItemSet temp;

			temp.profit = 0;
			temp.weight = 0;

			first.push_back(temp);

			for (auto it = this->items.begin(); it != this->items.end(); ++it)
			{
				next = first;

				this->AddItemInSet(next, *it);

				this->GenerateUnion(finale, first, next);

				this->PurgeCrap(finale, weight);

				this->DisplayItemSet(finale);
				std::cout << "\n\nAdded: " << it->name << "\n\n\n\n";

				first = finale;
			}

			temp = *finale.begin();

			for (auto it = finale.begin() + 1; it != finale.end(); ++it)
			{
				if (it->weight <= weight && it->profit > temp.profit)
				{
					temp = *it;
				}
			}

			return temp;

		}

		void AddItemInSet(std::vector<ItemSet> &set, Item &item)
		{
			for (auto it = set.begin(); it != set.end(); ++it)
			{
				it->profit += item.profit;
				it->weight += item.weight;

				it->prev.push_back(item.id);
			}
		}

		void GenerateUnion(std::vector<ItemSet> &finale, std::vector<ItemSet> &first, std::vector<ItemSet> &second)
		{
			finale.clear();

			for (auto it = first.begin(); it != first.end(); ++it)
			{
				finale.push_back(*it);
			}

			for (auto it = second.begin(); it != second.end(); ++it)
			{
				finale.push_back(*it);
			}
		}

		void PurgeCrap(std::vector<ItemSet> &set, int maxwt)
		{
			for (auto it = set.begin(); it != set.end();)
			{
				if (it->weight > maxwt)
				{
					it = set.erase(it);
				}
				else ++it;

			}

			bool del1, del2;

			for (auto it = set.begin(); it != set.end();) //it++ is not included here because the erase method does the job so it wud b twice if used here. Same for it2.
			{
				del1 = false;
				for (auto it2 = it + 1; it2 != set.end();)
				{
					del2 = false;
					if (it->weight == it2->weight) // ==  and > conditions for weight are seperate because both do different tasks.
					{
						if (it->profit <= it2->profit)
						{
							del1 = true;
							break;
						}
						else
						{
							it2 = set.erase(it2);
							del2 = true;
						}
					}
					else if (it->weight > it2->weight && it->profit <= it2->profit)
					{
						del1 = true;
						break;
					}
					if (!del2) ++it2;
				}
				if (del1 == true)
				{
					it = set.erase(it);
				}
				else ++it;
			}
		}

		std::vector<Item>::iterator GetItemLocation(std::string name)
		{
			for (auto it = this->items.begin(); it != this->items.end(); ++it)
			{
				if (it->name == name) return it;
			}

			return this->items.end();
		}

		bool ItemExists(std::string name)
		{
			for (auto it = this->items.begin(); it != this->items.end(); ++it)
			{
				if (it->name == name) return true;
			}

			return false;
		}

		void DisplayItemSet(std::vector<ItemSet> &set)
		{
			for (auto it = set.begin(); it != set.end(); ++it)
				std::cout << std::left
				<< "Item: " << std::setw(18) << it->profit
				<< "Weight: " << std::setw(18) << it->weight
				<< "\n";
		}

	};
}

#include "../include/Graph.hpp"

namespace Electrux
{

	bool operator ==(Data one, Data two)
	{
		return (one.from_id == two.from_id && one.to_id == two.to_id && one.weight == two.weight);
	}

	ShortestPathData Graph::CustomGetShortestPath(int src, int dest, std::vector<int> &path, int dist)
	{
		if (std::find(path.begin(), path.end(), src) != path.end()) return { -1, path }; //Prevent Cycle lock in graph

		path.push_back(src);
		NodeList *srclist = GetNodeList(src);

		//std::cout << "New node: " << src << " with dist = " << dist << "\n";
		//disp_node_tree(path);
		//std::cout << "\n";
		//std::cout << "New node end\n\n";
		ShortestPathData data = { -1, path };

		std::vector<int> origpath = path;

		if (srclist->get_node() == dest)
		{
			//std::cout << "final data new = " << dist << " with path = ";
			//disp_node_tree(path);
			//std::cout << "\nExiting: " << src << "\n";
			//std::cout << "\n\n";
			data.dist = dist;
			data.path = path;

			return data;
		}

		Node *it = srclist->getStart();
		if (it == nullptr)
		{
			//std::cout << "No path available on node " << src << ". Returning";
			//disp_node_tree(data.path);
			//std::cout << " and dist: " << data.dist << "\n";
			return data;
		}
		data.dist = 0;

		ShortestPathData newdata;
		int found = 0;

		while (it != nullptr)
		{
			if ((newdata = CustomGetShortestPath(it->id, dest, path, dist + it->weight)).dist > 0)
			{
				//std::cout << "Received new data: " << newdata.dist << ", prevdata: " << data.dist << "\n";
				if (data.dist > newdata.dist || data.dist == 0)
				{
					std::cout << "Possible Path found... dist = " << newdata.dist << " with path = ";
					disp_node_tree(newdata.path);
					std::cout << "\n";
					data = newdata;
				}
				found++;
			}
			path = origpath;
			it = it->next;
		}

		//std::cout << "Exiting: " << src << " with Found: " << found << " and data.dist = " << data.dist << "\n\n\n";

		if (found <= 0)
		{
			data = { -1, path };
		}

		return data;

	}
	
	Data Graph::getSmallestDist(std::vector<Data> data)
	{
		Data temp = { -1, -1, -1 };

		temp = *data.begin();

		for (auto it : data)
		{
			//std::cout << "Data: " << it.from_id << "\t" << it.to_id << "\t" << it.weight << "\n";
			if (it.weight < temp.weight)
				temp = it;
		}
		//std::cout << "Mini: " << temp.from_id << "\t" << temp.to_id << "\t" << temp.weight << "\n\n";

		return temp;
	}

	Graph::Graph()
	{
		start = end = nullptr;
		directed = Direction::DIRECTED;
	}

	Graph::Graph(int direction)
	{
		start = end = nullptr;
		if (direction != Direction::DIRECTED && direction != Direction::UNDIRECTED)
			directed = Direction::DIRECTED;
		else directed = direction;
	}

	bool Graph::add_node(int id)
	{
		NodeList *base;
		if ((base = GetNodeList(id)) != nullptr)
		{
			return false;
		}
		else
		{
			if (start == nullptr)
			{
				start = end = new NodeList;
				start->set_node(id);
			}
			else
			{
				end->setNext(new NodeList);
				end->getNext()->setPrev(end);
				end->getNext()->setNext(nullptr);
				end = end->getNext();
				end->set_node(id);
			}
			NodeList *list = new NodeList;
			list->set_node(id);
		}
		return true;
	}

	bool Graph::delete_node(int id)
	{
		NodeList *it = start;
		while (it != nullptr)
		{
			if (it->get_node() == id)
			{
				Node *deleter = it->getStart();							//
				while (deleter != nullptr)								//
				{														//
					NodeList *deletion = GetNodeList(deleter->id);		//Handle the deletion of this node from all other nodes
					deletion->delete_edge(it->get_node());				//
					deleter = deleter->next;							//
				}														//
				if (it == start)
				{
					start = start->getNext();
					start->setPrev(nullptr);
				}
				else if (it == end)
				{
					end = it->getPrev();
					it->getPrev()->setNext(nullptr);
				}
				else
				{
					it->getPrev()->setNext(it->getNext());
					it->getNext()->setPrev(it->getPrev());
				}
				delete it;
				return true;
			}
			it = it->getNext();
		}
		return false;
	}

	void Graph::disp_node_tree(std::vector<int> vec)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << "->";
		}
		std::cout << "X\n";
	}

	bool Graph::add_edge(int srcnode, int destnode, int weight)
	{
		NodeList *src = GetNodeList(srcnode), *dest = GetNodeList(destnode);
		if (src == nullptr || dest == nullptr) return false;
		if (directed == Direction::DIRECTED)
		{
			src->add_edge(destnode, weight);
		}
		else if (directed == Direction::UNDIRECTED)
		{
			src->add_edge(destnode, weight);
			dest->add_edge(srcnode, weight);
		}
		return true;
	}

	bool Graph::delete_edge(int from, int to)
	{
		NodeList *node1 = GetNodeList(from), *node2 = GetNodeList(to);
		if (node1 == nullptr || node2 == nullptr) return false;
		if (directed == Direction::DIRECTED)
		{
			node1->delete_edge(to);
		}
		else if (directed == Direction::UNDIRECTED)
		{
			node1->delete_edge(to);
			node2->delete_edge(from);
		}
		return true;
	}

	NodeList* Graph::GetNodeList(int _base)
	{
		NodeList *temp = start;
		while (temp != nullptr)
		{
			if (temp->get_node() == _base)
			{
				return temp;
			}
			temp = temp->getNext();
		}
		return nullptr;
	}

	bool Graph::NodeListExists(int _base)
	{
		NodeList *temp = start;
		while (temp != nullptr)
		{
			if (temp->get_node() == _base)
			{
				return true;
			}
			temp = temp->getNext();
		}
		delete temp;
		return false;
	}

	int Graph::edge_exists(int from, int to)
	{
		NodeList *fromnode = GetNodeList(from);
		if (fromnode == 0) return -1;
		if (!NodeListExists(to)) return -1;
		int dist = fromnode->edge_exists(to);
		if (dist != 0) return dist;
		return 0;
	}

	std::vector<int> Graph::getNodes()
	{
		NodeList *temp = start;
		std::vector<int> allnodes;
		allnodes.clear();
		while (temp != nullptr)
		{
			allnodes.push_back(temp->get_node());
			temp = temp->getNext();
		}
		return allnodes;
	}

	ShortestPathData Graph::getShortestPath(int src, int dest)
	{
		std::vector<int> path;

		return CustomGetShortestPath(src, dest, path);
	}

	Graph Graph::generateKruskalGraph()
	{
		Graph ans;

		std::vector<int> tovisit = this->getNodes();
		int nodecount = tovisit.size();

		std::vector<Data> visits;

		int from_node = *tovisit.begin();

		std::vector<int> smallestfound;

		while ((int)smallestfound.size() < nodecount)
		{
			auto nodelist = GetNodeList(from_node);

			auto node = nodelist->getStart();

			while (node != nullptr)
			{
				if (std::find(tovisit.begin(), tovisit.end(), node->id) != tovisit.end())
				{
					visits.push_back({ from_node, node->id, node->weight });
				}
				node = node->next;
			}

			auto smallest = this->getSmallestDist(visits);

			auto visitsexists = std::find(visits.begin(), visits.end(), smallest);
			if(visitsexists != visits.end())
				visits.erase(visitsexists);

			if (std::find(smallestfound.begin(), smallestfound.end(), smallest.to_id) == smallestfound.end())
			{
				ans.add_node(smallest.from_id);
				ans.add_node(smallest.to_id);
				ans.add_edge(smallest.from_id, smallest.to_id, smallest.weight);

				if (std::find(smallestfound.begin(), smallestfound.end(), smallest.from_id) == smallestfound.end())
					smallestfound.push_back(smallest.from_id);

				smallestfound.push_back(smallest.to_id);
			}

			auto exists = std::find(tovisit.begin(), tovisit.end(), from_node);
			if(exists != tovisit.end())
				tovisit.erase(exists);

			from_node = smallest.to_id;
		}

		return ans;
	}

	void Graph::arrangeVisits(std::vector<mnode> &vec)
	{
		std::vector<mnode> vtemp;
		while (!vec.empty())
		{
			auto temp = vec.begin();
			for (auto it = vec.begin(); it != vec.end(); ++it)
			{
				if (temp->dist > it->dist)
				{
					temp = it;
				}
			}
			vtemp.push_back(*temp);
			vec.erase(temp);
		}
		vec = vtemp;
	}

	bool Graph::findInVector(std::vector<mnode> &vec, int id)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it->id == id)
			{
				return true;
			}
		}
		return false;
	}

	std::ostream & operator << (std::ostream &os, const Graph &graph)
	{
		NodeList *temp = graph.start;
		while (temp != nullptr)
		{
			os << "\nNode: " << temp->get_node() << "\n";
			if (temp->getStart() == nullptr)
			{
				os << "----No outgoing edge available----\n";
			}
			else
			{
				os << *temp;
			}
			temp = temp->getNext();
		}
		delete temp;
		return os;
	}

}

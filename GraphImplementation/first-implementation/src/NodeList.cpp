#include "NodeList.hpp"

namespace Electrux
{
	NodeList::NodeList()
	{
		start = end = nullptr;
		node = -1;
		next = prev = nullptr;
	}

	NodeList::NodeList(int _node)
	{
		start = end = nullptr;
		node = _node;
		next = prev = nullptr;
	}

	void NodeList::setNext(NodeList *ne)
	{
		next = ne;
	}

	void NodeList::setPrev(NodeList *pr)
	{
		prev = pr;
	}

	NodeList* NodeList::getNext()
	{
		return next;
	}

	NodeList* NodeList::getPrev()
	{
		return prev;
	}

	Node* NodeList::getStart()
	{
		return start;
	}
	
	void NodeList::set_node(int n)
	{
		node = n;
	}
	
	int NodeList::get_node()
	{
		return node;
	}
	
	void NodeList::add_edge(int to_id, int weight)
	{
		if (!edge_exists(to_id))
		{
			if (start == nullptr)
			{
				start = end = new Node;
				start->id = to_id;
				start->weight = weight;
				start->next = nullptr;
				start->prev = nullptr;
			}
			else
			{
				end->next = new Node;
				end->next->prev = end;
				end->next->next = nullptr;
				end = end->next;
				end->id = to_id;
				end->weight = weight;
			}
		}
	}
	
	int NodeList::edge_exists(int to_id)
	{
		Node *it = start;
		while (it != nullptr)
		{
			if (it->id == to_id)
				return it->weight;
			it = it->next;
		}
		return 0;
	}
	
	bool NodeList::delete_edge(int to_id)
	{
		if (edge_exists(to_id))
		{
			Node *it = start;
			while (it != nullptr)
			{
				if (it->id == to_id)
				{
					if (it == start)
					{
						start = start->next;
						start->prev = nullptr;
					}
					else if (it == end)
					{
						end = it->prev;
						it->prev->next = nullptr;
					}
					else
					{
						it->prev->next = it->next;
						it->next->prev = it->prev;
					}
					delete it;
					return true;
				}
				it = it->next;
			}
		}
		return false;
	}

	std::ostream & operator <<(std::ostream &os, const NodeList &obj)
	{
		Node *temp = obj.start;
		while (temp != nullptr)
		{
			os << "Destination: " << temp->id << "\tWeight: " << temp->weight << "\n";
			temp = temp->next;
		}
		delete temp;
		return os;
	}
}
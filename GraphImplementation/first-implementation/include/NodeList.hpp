#include <iostream>
#include <vector>
#include <map>

namespace Electrux
{
	struct Node
	{
		int id;
		int weight;
		Node *next, *prev;
	};

	struct Data
	{
		int from_id;
		int to_id;
		int weight;
	};

	struct mnode
	{
		int id, dist;
	};

	class NodeList
	{
		Node *start, *end;
		int node;
		NodeList *next, *prev;
	public:
		NodeList();
		NodeList(int _node);
		void setNext(NodeList *ne);
		void setPrev(NodeList *pr);
		NodeList *getNext();
		NodeList *getPrev();
		Node *getStart();
		void set_node(int n);
		int get_node();
		void add_edge(int to_id, int weight);
		int edge_exists(int to_id);
		bool delete_edge(int to_id);
		friend std::ostream & operator <<(std::ostream &os, const NodeList &obj);
	};
}

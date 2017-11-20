#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include "../include/BST.hpp"


// Left is "<" right is ">="
// Level begins with 0 as root level


int main()
{
	bs_tree<int> tree;
	tree.insert_data(5);
	tree.insert_data(3);
	tree.insert_data(2);
	tree.insert_data(16);
	tree.insert_data(9);
	tree.insert_data(23);
	tree.insert_data(32);
	tree.insert_data(345);
	tree.insert_data(3445);
	tree.insert_data(51);
	tree.insert_data(11);
	tree.insert_data(1);
	tree.insert_data(1231);
	tree.delete_data(345);
	/*tree.insert_data(65);
	tree.insert_data(67);
	tree.insert_data(69);
	tree.insert_data(50);
	tree.insert_data(40);
	tree.insert_data(30);
	tree.insert_data(20);
	tree.insert_data(45);
	tree.insert_data(47);
	tree.insert_data(49);
	tree.insert_data(48);
	tree.insert_data(46);*/
	std::cout << "Level: " << tree.get_level() << "\n\n";
	tree.display_tree(bs_tree<int>::TRAVERSAL::VLR);
	std::cout << "\n\n";
	std::system("pause");
	return 0;
}

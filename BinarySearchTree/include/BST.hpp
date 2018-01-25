#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

//The structure of each node of the Binary Search Tree.
template <class T> struct bintree {

	//Bintree node contains pointer to parent of this node.
	bintree<T> *parent;
	
	//Create variable of the template type to store the data.
	T data;
	
	//Create a level variable to store the node's level.
	int level;

	//Left and right child pointers of the node.
	bintree<T> *left, *right;

};

//The Binary Search Tree class. This is to be used to create BSTs.
template <class T> class bs_tree {

	//The root node of the BST.
	bintree<T> *root;

	//The levelmap which contains information of each level of the tree.
	std::map<int, int> levelmap;

	//Private function which deletes given data starting to find it from the given node.
	bool delete_data(bintree<T> *node, T data);

	//Private function to decrease the levelmap values.
	bool decrease_levelmap(int level);

	//Private function to allocate a new node and set its default values.
	bintree<T> *create_node();

public:

	//Enum to handle the traversal types (Preorder - VLR, Postorder - LRV, and Inorder - LVR).
	enum TRAVERSAL {
		VLR,
		LRV,
		LVR
	};

	//Constructor for the BST objects.
	bs_tree<T>();

	//Inserts new data in the tree. Returns true if success, false if failed.
	bool insert_data(T data);

	//Deletes data from the tree. Returns true if success, false if failed.
	bool delete_data(T data);

	//Fetches the pointer to the inorder successor of the given node.
	bintree<T> *get_inorder_successor(bintree<T> *node);

	//Displays the BST with given traversal type.
	void display_tree(int trav_type = TRAVERSAL::LVR);

	//Displays the BST with given traversal type from the given node.
	void display_tree(bintree<T> *temp, int trav_type = TRAVERSAL::LVR);

	//Gets the level of the tree.
	size_t get_level();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


//Private Functions.

template <class T> bool bs_tree<T>::delete_data(bintree<T> *node, T data)
{
	//Create a traveller node initializing it from the node from which to begin.
	bintree<T> *walker = node;

	//If this node is nullptr, return false since we can't delete null.
	if (walker == nullptr) return false;

	//If this node is the required data, perform checks and delete it.
	if (walker->data == data)
	{
		//If the right of this node is nullptr, check for the left.
		if (walker->right == nullptr)
		{
			//If both are nullptr, simply remove this node and decrease levelmap.
			if (walker->left == nullptr)
			{
				//This is the left child of its parent.
				//Otherwise this is the right child of its parent.
				if (walker->parent->left == walker)
					walker->parent->left = nullptr;
				else
					walker->parent->right = nullptr;

				//If the level count in levelmap of this level is 1, erase the level from levelmap.
				//Otherwise decrement the count of this level in levelmap.
				if (levelmap[walker->level] == 1)
					levelmap.erase(walker->level);
				else
					levelmap[walker->level]--;

				//Delete the traveller, deallocate memory.
				delete walker;

				//All good, return true.
				return true;
			}
			//Well, life isnt so easy, gotta handle the nodes connected to this node.
			else
			{
				//Set this data of this node to be the data in the left of this node.
				walker->data = walker->left->data;

				//Delete the left node of this node by calling this function recursively.
				delete_data(walker->left, walker->left->data);

				//All good! Go home happ now.
				return true;
			}
		}
		//The right of the walker is not nullptr. Get the inorder successor.
		else
		{
			//Get the inorder successor of this data.
			bintree<T> *del = get_inorder_successor(walker);

			//If the inordersuccessor comes to be nullptr, end up returning false (this should never happen under normal circumstances).
			if (del != nullptr)
			{
				//Move the data of the inorder successor to this node.
				walker->data = del->data;

				//Delete the inordersuccessor by recursively calling this function.
				delete_data(del, del->data);

				//All good. You are good to return true.
				return true;
			}
		}
		//This should not come under normal circumstances.
		return false;
	}
	//This node aint the required data. Dive deeper.
	else
	{
		//If there is something on the left and data to be deleted is less than this node's data, go left.
		//Otherwise, go right if the right node is not nullptr.
		if (data < walker->data && walker->left != nullptr)
			delete_data(walker->left, data);
		else if (walker->right != nullptr)
			delete_data(walker->right, data);

		//After deleting completing the recursion, return true since the job has been taken care of.
		return true;
	}
}

template <class T> bool bs_tree<T>::decrease_levelmap(int level)
{
	//Check if there exists a level of that value.
	if (levelmap.count(level) > 0)
	{
		//If the levelmap has only one count of that value, remove the level from the map.
		//Otherwise decrease the count.
		if (levelmap[level] == 1)
			levelmap.erase(level);
		else
			levelmap[level]--;

		//All good. Return true.
		return true;
	}

	//If the level does not exist in the levelmap, return false.
	return false;
}


//Public Functions.

template <class T> bs_tree<T>::bs_tree()
{
	//Initialize the root with nullptr.
	root = nullptr;
}

template <class T> bool bs_tree<T>::insert_data(T data)
{
	//If not used double pointer,  due to single pointer, the changes made on the address of tree gets removed after the function exits. Becoz i wud b changing the value of pointer if not for double pointer. which means
	//its like changing the value of a non pointer used data type (primitive). More info in the pic....
	bool done = false;
	int tempcounter = -1;
	
	//If there exists no root, create root and start the tree.
	if (root == nullptr)
	{
		root = create_node();
		root->data = data;

		//Increase the value of tempcounter, and set the level of root to be equal to tempcounter.
		tempcounter++;
		root->level = tempcounter;
		
		//Set the count of zeroth level in levelmap to be equal to 1.
		levelmap[0] = 1;

		//Insertion/Addition has been done.
		done = true;
	}
	//There exists root. Gotta insert it using BST properties.
	else
	{
		//Get the root in temp variable (traveller).
		bintree<T> *tree = root;

		//Run an infinite loop which stops when the element is inserted (break condition).
		while (true)
		{
			//As the loop goes, the counter increases signifying increase in level.
			tempcounter++;

			//Data is less that the data of current node. Go left.
			if (data < tree->data)
			{
				//Left of current node is nullptr. Insert the new node there.
				if (tree->left == nullptr)
				{
					//Create new node and insert data.
					tree->left = create_node();
					tree->left->data = data;
					tree->left->parent = tree;

					//Increment counter and set the level of the node.
					tempcounter++;
					tree->left->level = tempcounter;

					//If there is no key in levelmap of this counter, set the count to be one.
					//Otherwise, increment the counter.
					if (levelmap.count(tempcounter) == 0)
						levelmap[tempcounter] = 1;
					else
						levelmap[tempcounter]++;
					
					//All done. Now break.
					done = true;
					break;
				}
				//Left of current node is not nullptr. Go there and repeat process.
				else
				{
					tree = tree->left;
				}
			}
			//Data is greater than or equal to current node. Go right.
			else
			{
				//Right of current node is nullptr. Insert the new node there.
				if (tree->right == nullptr)
				{
					//Create new node and insert data.
					tree->right = create_node();
					tree->right->data = data;
					tree->right->parent = tree;

					//Increment counter and set the level of the node.
					tempcounter++;
					tree->right->level = tempcounter;

					//If there is no key in levelmap of this counter, set the count to be one.
					if (levelmap.count(tempcounter) == 0) levelmap[tempcounter] = 1;
					
					//Otherwise, increment the counter.
					else levelmap[tempcounter]++;

					//All done. Now break.
					done = true;
					break;
				}
				//Right of current node is not nullptr. Go there and repeat process.
				else
				{
					tree = tree->right;
				}
			}
		}
	}
	//Return the value of done. This function is success if done == true.
	return done;
}

template <class T> bintree<T> *bs_tree<T>::create_node()
{
	//Allocate memory of a new node.
	bintree<T> *temp = new bintree<T>;

	//Set the default parameters of the new node.
	temp->left = nullptr;
	temp->right = nullptr;
	temp->parent = nullptr;
	temp->level = -1;

	//Return the new node.
	return temp;
}

template <class T> bool bs_tree<T>::delete_data(T data)
{
	//Delete the given data searching for it from root.
	return delete_data(root, data);
}

template <class T> bintree<T> *bs_tree<T>::get_inorder_successor(bintree<T> *node)
{
	//Set the given node to be original node. We will set the given node back to the original node.
	//And, set the inorder successor (newvar) equal to nullptr.
	bintree<T> *orig = node, *newvar = nullptr;
	
	//If this node is nullptr, return nullptr. Cant find inorder successor of nullptr afterall.
	if (node == nullptr)
		return nullptr;

	//If there is no left and right of this node (both are nullptr, return nullptr.
	if (node->left == nullptr && node->right == nullptr)
		return nullptr;

	//Run this loop while this node isnt equal to nullptr.
	while (node != nullptr)
	{
		//If the left and right of this node are nullptr, the inorder successor of the original node is this node.
		if (node->left == nullptr && node->right == nullptr)
		{
			//Set the inorder successor of the original node to be this node.
			newvar = node;

			//Break the loop.
			break;
		}
		//Otherwise, move to the next node.
		else
		{
			//If the left of this node is nullptr and this node is not the original given node, check if there is something on the left of the left of this node.
			//Otherwise, if the right of this node is not nullptr and this node is original node, check the left of the right of this node.
			//Otherwise, set the inorder successor to be equal to this node and break the loop.
			if (node->left != nullptr && node != orig)
			{
				//If the left of the left of this node is nullptr, we found the inorder successor of the given node.
				//Otherwise, set the traveller to be the left of this node and repeat the loop.
				if (node->left->left == nullptr)
				{
					//Set the inorder successor equal to the left of this node.
					newvar = node->left;

					//Break the loop.
					break;
				}
				else
				{
					node = node->left;
				}
			}
			else if (node->right != nullptr && node == orig)
			{
				//If the left of the right of this node is not nullptr, set the left of the right of this node to be the traveller and repeat the loop.
				//Otherwise set the inorder successor to be the right of this node and break the loop.
				if (node->right->left != nullptr)
				{
					node = node->right->left;
				}
				else
				{
					newvar = node->right;
					break;
				}
			}
			else
			{
				newvar = node;
				break;
			}
		}
	}

	//Set the node variable back to the original node variable received by the function.
	node = orig;

	//If the original node and its inorder successor are same, there is no inorder successor of the original node and therefore return nullptr.
	if (orig == newvar)
		return nullptr;

	//Otherwise return the inorder successor.
	return newvar;
}

template <class T> void bs_tree<T>::display_tree(int trav_type)
{
	//Display the tree from the root.
	display_tree(root, trav_type);
}

template <class T> void bs_tree<T>::display_tree(bintree<T> *temp, int trav_type)
{
	//The traversal type is Preorder.
	if (trav_type == TRAVERSAL::VLR)
	{
		//If the node to begin with is nullptr, nothing can be displayed.
		if (temp != nullptr)
		{
			//If the parent of this node is not nullptr, display which side of its parent this node falls in.
			//The parent of this node is nullptr, meaning, this node is root.
			if (temp->parent != nullptr)
			{
				//If this is left child of its parent, show as left child.
				//Otherwise show as right child.
				if (temp->parent->left == temp)
					std::cout << "Left child of Parent = " << temp->parent->data << "\tData = " << temp->data;
				else
					std::cout << "Right child of Parent = " << temp->parent->data << "\tData = " << temp->data;
			}
			else
			{
				//Display this node as root.
				std::cout << "Root, Data = " << temp->data;
			}

			//A new line please.
			std::cout << "\n";

			//Display the left of this node.
			display_tree(temp->left, trav_type);

			//Display the right of this node.
			display_tree(temp->right, trav_type);
		}
	}
	//The traversal type is Postorder.
	else if (trav_type == TRAVERSAL::LRV)
	{
		//If the node to begin with is nullptr, nothing can be displayed.
		if (temp != nullptr)
		{
			//Display the left of this node.
			display_tree(temp->left, trav_type);

			//Display the right of this node.
			display_tree(temp->right, trav_type);

			//If the parent of this node is not nullptr, display which side of its parent this node falls in.
			if (temp->parent != nullptr)
			{
				//If this is left child of its parent, show as left child.
				//Otherwise show as right child.
				if (temp->parent->left == temp)
					std::cout << "Left child of Parent = " << temp->parent->data << "\tData = " << temp->data;
				else
					std::cout << "Right child of Parent = " << temp->parent->data << "\tData = " << temp->data;
			}
			//The parent of this node is nullptr, meaning, this node is root.
			else
			{
				//Display this node as root.
				std::cout << "Root, Data = " << temp->data;
			}

			//A new line please.
			std::cout << "\n";
		}
	}
	//The traversal type is Inorder.
	else if (trav_type == TRAVERSAL::LVR)
	{
		//If the node to begin with is nullptr, nothing can be displayed.
		if (temp != nullptr)
		{
			//Display the left of this node.
			display_tree(temp->left, trav_type);

			//If the parent of this node is not nullptr, display which side of its parent this node falls in.
			if (temp->parent != nullptr)
			{
				//If this is left child of its parent, show as left child.
				//Otherwise show as right child.
				if (temp->parent->left == temp)
					std::cout << "Left child of Parent = " << temp->parent->data << "\tData = " << temp->data;
				else
					std::cout << "Right child of Parent = " << temp->parent->data << "\tData = " << temp->data;
			}
			//The parent of this node is nullptr, meaning, this node is root.
			else
			{
				//Display this node as root.
				std::cout << "Root, Data = " << temp->data;
			}

			//A new line please.
			std::cout << "\n";

			//Display the right of this node.
			display_tree(temp->right, trav_type);
		}
	}
}

template <class T> size_t bs_tree<T>::get_level()
{
	//Return the max level of the tree. - 1 because the size does not count from zero but level does.
	return levelmap.size() - 1;
}

#endif // BST_HPP

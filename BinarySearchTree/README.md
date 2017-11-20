# Electrux-Codes

This is a C++ code to create a Binary Search Tree of any type of data, provided, the data can be tested for greater/less than ( >, >=, <, <= ) and equal to ( == ).
	The following functions are part of the class bs_tree.
	Note: T is template class for defining templates.
	
	Functions:
	
		Public:
	
			bs_tree<T>();

				No parameter constructor for the Binary Search Tree. Initializes the root node to nullptr.
			
			
			bool insert_data(T data);
				
				This function is used to input data in the BST. Returns true if the data was successfully inserted, false otherwise.
				(Will return true always because there is no reason for insertion to be denied.)
				
			
			bool delete_data(T data);
			
				This function will delete any data (given in parameter) and return true/false depending on success/failure.
				Internally calls overloaded function delete_data(root, T data); (See private Functions section.)
				
			
			bintree<T> *get_inorder_successor(bintree<T> *node);
			
				Retrieves in order successor of any given node in the Tree. Public function, but used internally to apply the deletion logics.
				
			
			void display_tree(int trav_type = TRAVERSAL::LVR);
			
				Displays the entire data in tree along with parent (unless root, in which case it shows it as root). TRAVERSAL defines the order of displaying.
					- VLR : Displays the tree with the root/node data first, then the left and right sub-trees.		(bs_tree<T>::TRAVERSAL::VLR)
					- LVR : Displays the tree with left sub-tree first, then root/node data, then right sub-tree.	(bs_tree<T>::TRAVERSAL::LVR)
					- LRV : Displays the tree with left sub-tree first, then right sub-tree, then root/node data.	(bs_tree<T>::TRAVERSAL::LRV)
					
					Here, V is representation for Root, L is Left, R is Right.
					
			
			void display_tree(bintree<T> *temp, int trav_type = TRAVERSAL::LVR);
			
				Same as above, but also takes a node as parameter and then displays the tree from there. The above function uses this internally, by calling it with root. (Recursive Function.)
				
		
			size_t get_level();
			
				Fetches the level of ENTIRE tree (not a specific node). Quite efficient since it evaluates the level without needing traversals in trees specifically.
				Modified at the time of insertion/deletin in tree.
	
	
		
		Private:
		
			bool delete_data(bintree<T> *node, T data);
			
				Internally called by the public function delete_data(T data); It calls this function with parameter node = root. (Recursive Function.)
				
				
			bool decrease_levelmap(int level);
			
				Internal function to manage tree level modifications.
				
			
			bintree<T> *create_node();
			
				Allocates memory for new node thereby creating it. Internal function.
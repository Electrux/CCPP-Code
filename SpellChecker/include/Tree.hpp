#ifndef TREE_HPP
#define TREE_HPP

#include <vector>

class Tree
{
	char c;
	bool isword;

	std::vector< Tree * > nodes;

public:

	Tree() { isword = false; }

	~Tree()
	{
		for( auto node : nodes )
			delete node;
	}

	void SetChar( char c )
	{
		this->c = c;
	}

	char GetChar()
	{
		return c;
	}

	void SetIsWord( bool isword ) { this->isword = isword; }

	bool IsWord() { return isword; }

	Tree* Add( char c )
	{
		for( auto node : nodes ) {
			if( node->GetChar() == c )
				return node;
		}

		nodes.push_back( new Tree );
		( *( nodes.end() - 1 ) )->SetChar( c );

		return *( nodes.end() - 1 );
	}

	Tree* Exists( char c )
	{
		for( auto node : nodes ) {
			if( node->GetChar() == c )
				return node;
		}

		return nullptr;
	}
	
};

#endif // TREE_HPP

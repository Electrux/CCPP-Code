#ifndef SPELLINGTREE_HPP
#define SPELLINGTREE_HPP

#include <iostream>
#include "Stack.hpp"
#include "Tree.hpp"

class SpellTree
{
	Tree *root;

	Stack< Tree * > prevtempswhileadding;
	Tree *tempwhileadding;

	size_t count;

	std::string checkstr;

public:
	struct ReturnValue
	{
		bool result;
		std::string checkstr;
	};
	
	SpellTree()
	{
		root = new Tree;
		root->SetChar( '_' );
		root->SetIsWord( false );

		tempwhileadding = root;
		
		count = 0;
	}

	~SpellTree() { delete root; }

	void AddWord( std::string word )
	{
		Tree *temp = root;

		for( auto ch : word ) {
			temp = temp->Add( ch );
		}

		temp->SetIsWord( true );
	}

	bool CheckWord( std::string word )
	{
		Tree *temp = root;

		for( auto ch : word ) {
			temp = temp->Exists( ch );

			if( temp == nullptr )
				return false;
		}

		return temp->IsWord();
	}

	std::string GetCheckString() { return checkstr; }

	bool GetCurrentCheckResult() { return tempwhileadding->IsWord(); }

	ReturnValue CheckWhileAddingCharacter( char c )
	{
		prevtempswhileadding.Push( tempwhileadding );

		tempwhileadding = tempwhileadding->Exists( c );

		if( tempwhileadding == nullptr ) {
			tempwhileadding = prevtempswhileadding.Pop();
			return { false, checkstr + c };
		}

		checkstr += c;

		return { tempwhileadding->IsWord(), checkstr };
	}

	ReturnValue CheckWhileErasingCharacter()
	{
		if( prevtempswhileadding.GetCount() <= 0 )
			return { false, checkstr };

		tempwhileadding = prevtempswhileadding.Pop();

		checkstr.erase( checkstr.end() - 1 );

		return { tempwhileadding->IsWord(), checkstr };
	}

	void ClearTempWhileAdding()
	{
		tempwhileadding = root;
		checkstr.clear();
	}
};

#endif // SPELLINGTREE_HPP

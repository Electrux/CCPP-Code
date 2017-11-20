//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_HASHKEY_HPP
#define HASHTABLEIMPLEMENTATION_HASHKEY_HPP

#include <string>
#include "Constants.hpp"
#include "TemplateDefs.hpp"

namespace Electrux
{
	// Class definition for Hashkey.
	template < typename T >
	class HashKey
	{
		int table;
		T key;

		// Generate the hash value from the member variable - key.
		void GenHash() { hashval = GetHash( key ) % TABLE_SIZE; }

	public:

		// Member to store the hash value so that it is not needed to find again
		// and again, thereby saving time.
		int hashval;

		// Constructor for setting the default table to -1.
		HashKey() { table = -1; }

		// Constructor which sets the key as wll.
		HashKey( T key )
		{
			table = -1;
			this->key = key;
			this->GenHash();
		}

		// Fetch the key.
		T GetKey() const
		{
			return key;
		}

		// Fetch the table in which this key resides.
		int GetTable() const
		{
			return table;
		}

		// Overloaded operator which returns the hash value.
		// This enables the (semi) Generalization of the HashKey class.
		int operator ()() const
		{
			return hashval;
		}

		// Sets the key.
		void SetKey( T key )
		{
			this->key = key;
			this->GenHash();
		}

		// Set the table of the key instance.
		void SetTable( int table )
		{
			this->table = table;
		}

		// Set the key using assignment operator.
		void operator =( T key )
		{
			this->table = -1;
			this->key = key;
			this->GenHash();
		}
	};
}

#endif //HASHTABLEIMPLEMENTATION_HASHKEY_HPP

//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_HASHTABLE_HPP
#define HASHTABLEIMPLEMENTATION_HASHTABLE_HPP

#include <string>
#include <climits>
#include "Constants.hpp"
#include "Table.hpp"
#include "HashKey.hpp"
#include "Stack.hpp"

namespace Electrux
{
	template < typename T, typename U >
	class HashTable
	{
		// Max values per table.
		COUNTTYPE size;

		Table< U > *tables[ MAX_TABLES ];
		Stack *freespaces;

		COUNTTYPE *lastlocfilled;

		COUNTTYPE ctr;

		size_t netcount;

		T defaulter;

	public:

		HashTable()
		{
			ctr = 0;

			size = TABLE_SIZE;

			tables[ ctr ] = new Table< U >( size );
			lastlocfilled = new COUNTTYPE[ size ];
			freespaces = new Stack[ size ];

			for( COUNTTYPE i = 0; i < size; ++i )
				lastlocfilled[ i ] = -1;

			netcount = 0;
		}

		~HashTable()
		{
			for( COUNTTYPE i = 0; i <= ctr; ++i )
				delete tables[ i ];

			delete[] lastlocfilled;
		}

		bool Insert( HashKey< T > &key, U val )
		{
			COUNTTYPE loc = key();

			if( lastlocfilled[ loc ] == MAX_TABLES - 1 ) {
				return false;
			}

			COUNTTYPE freespace = freespaces[ loc ].Pop();
			if( freespace != -16384 )
			{
				tables[ freespace ]->Insert( loc, val );
				key.SetTable( freespace );
			}
			else
			{
				lastlocfilled[ loc ]++;

				if( lastlocfilled[ loc ] > ctr ) {
					tables[ lastlocfilled[ loc ] ] = new Table< U >( size );
					ctr++;
				}

				tables[ lastlocfilled[ loc ]]->Insert( loc, val );

				key.SetTable( lastlocfilled[ loc ] );
			}

			netcount++;

			return true;
		}

		bool Delete( HashKey< T > &key )
		{
			COUNTTYPE loc = key();

			if( tables[ key.GetTable() ]->Delete( loc ) ) {
				netcount--;
				freespaces[ loc ].Push( key.GetTable() );
				key.SetTable( -1 );

				return true;
			}

			return false;
		}

		const T & Get( const HashKey< T > &key )
		{
			if( key.GetTable() < 0 ) return defaulter;

			return tables[ key.GetTable() ]->Get( key() );
		}

		int GetCount()
		{
			return netcount;
		}

		COUNTTYPE GetCtr()
		{
			return ctr;
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_HASHTABLE_HPP

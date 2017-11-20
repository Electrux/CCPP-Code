//
// Created by Electrux Redsworth on 9/8/17.
//

#ifndef HASHTABLEIMPLEMENTATION_TABLE_HPP
#define HASHTABLEIMPLEMENTATION_TABLE_HPP

#include <string>

namespace Electrux
{
	template < typename T >
	class Table
	{
		// Array of datatype ( T ) which are to be stored.
		T *data;
		int size;
		bool *isfilled;

	public:

		Table( int datasize )
		{
			size = datasize;
			data = new T[datasize];

			// Defaults to zero.Z
			isfilled = new bool[ datasize ];
		}

		~Table()
		{
			delete[] data;
			delete[] isfilled;
		}

		bool Insert( int loc, T data )
		{
			if( loc >= size ) return false;

			if( isfilled[ loc ] ) return false;

			this->data[ loc ] = data;

			return true;
		}

		bool Delete( int loc )
		{
			if( loc >= size ) return false;
			if( !isfilled[ loc ] ) return false;

			data[ loc ].clear();

			return true;
		}

		const T &Get( int loc )
		{
			if( loc >= size ) return T();
			if( !isfilled[ loc ] ) return T();

			return data[ loc ];
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_TABLE_HPP

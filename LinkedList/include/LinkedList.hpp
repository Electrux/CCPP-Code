#include <iostream>

template < typename T >
struct Node
{
	T data;

	Node< T > *next,
		*prev;
};

template < typename T >
class LinkedList
{
	size_t count;

	Node< T > *begin,
		*end;

public:

	LinkedList()
	{
		begin = end = nullptr;

		count = 0;
	}

	~LinkedList()
	{
		for( size_t i = 0; i < count; ++i )
			this->DeleteLast();
	}

	bool Insert( T value )
	{
		Node< T > *temp = this->CreateNewNode( value );

		if( temp == nullptr )
			return false;
		
		if( begin == nullptr ) {
			begin = end = temp;
		}
		else {
			end->next = temp;

			temp->prev = end;
			
			end = end->next;
		}

		begin->prev = end;
		end->next = begin;

		count++;

		return true;
	}

	bool Delete( T value )
	{
		if( begin == nullptr )
			return false;

		Node< T > *temp = begin;

		if( count == 1 ) {
			if( temp->data == value ) {
				delete temp;

				begin = end = nullptr;

				count--;
				
				return true;
			}

			return false;
		}
		
		for( size_t i = 0; i < count; ++i ) {

			if( temp->data == value ) {
				
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				
				if( temp == begin )
					begin = temp->next;

				if( temp == end )
					end = temp->prev;
				
				delete temp;

				count--;

				return true;
			}
			
			temp = temp->next;
		}

		return false;
	}

	bool DeleteLast()
	{
		if( begin == nullptr )
			return false;

		Node< T > *temp = end;

		temp->prev->next = end->next;
		temp->next->prev = end->prev;

		end = end->prev;

		count--;

		delete temp;

		return true;
	}

	bool DeleteFirst()
	{
		if( begin == nullptr )
			return false;

		Node< T > *temp = begin;

		temp->prev->next = begin->next;
		temp->next->prev = begin->prev;

		begin = begin->next;

		count--;
		
		delete temp;

		return true;
	}

	Node< T > *CreateNewNode( int value = 0 )
	{
		Node< T > *temp = new Node< T >;

		if( temp == nullptr ) return temp;
		
		temp->data = value;

		temp->next = temp->prev = nullptr;

		return temp;
	}

	void Display()
	{
		Node< T > *temp = begin;
		
		for( size_t i = 0; i < count; ++i ) {
			std::cout << temp->data << "->";
			temp = temp->next;
		}

		if( count > 0 )
			std::cout << "\b\b  ";
	}
};

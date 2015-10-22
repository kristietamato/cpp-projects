// LinkedList.h

#include<string>
using namespace std;

#ifndef LINKED_LIST
#define LINKED_LIST

namespace linked_list
{
	class Node
	{
	public:
		typedef int value_type;
		Node( int i_data = 0, Node *i_next = NULL )
			: data(i_data), next(i_next)
		{}
		value_type data;
		Node *next;
	};

	class LinkedList
	{
	public:
		typedef Node::value_type value_type;
		typedef Node *node_ptr;

		LinkedList(void) : head(NULL) {}
		LinkedList(const LinkedList &source);
		~LinkedList();

		void push( Node::value_type value );
		Node::value_type pop(void);
        bool sortedPush( int value );
        bool sortedPush( int value, node_ptr &pp, node_ptr &np );

		Node::value_type operator[]( size_t index );

		bool isIn( int value );
		bool kill( int value );

		bool isEmpty(void) { return head == NULL; }
		size_t size(void);

	private:
		Node *head;

		bool kill( int value, node_ptr &np );

		void killList( Node *listHead );
		size_t size( Node *listHead );
	};
}

#endif
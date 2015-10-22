// Jim Hester
// A simple container with a statistic method

#ifndef INT_COLLECTION
#define INT_COLLECTION

#include "linked-list.h"
using namespace std;

namespace CollectionSpace
{
    class intCollection
    {
    public:
        typedef int value_type;

        // constructors
        intCollection(void);
        intCollection(const intCollection &source );
        intCollection(bool isSorted);

        // destructor
        ~intCollection(){data.~LinkedList();}

        // modifiers
        void insert( linked_list::Node::value_type newItem );
        value_type extract(void);

        // status
        size_t size(void);
        bool isSorted(void);
        bool isEmpty(void);

    private:
        linked_list::LinkedList data;
        bool sorted;
    };
}

#endif
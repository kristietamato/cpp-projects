// Jim Hester
// A simple container with a statistic method

#include"int-Collection.h"
#include<cassert>
#include<cmath>
using namespace std;

namespace CollectionSpace
{
    intCollection::intCollection(void)
    {
        sorted = false;
    }
    intCollection::intCollection(bool shouldSort)
    {
        sorted = shouldSort;
    }
    intCollection::intCollection( const intCollection &source )
    : data(source.data)
    {
    }
    
    void intCollection::insert( linked_list::Node::value_type newItem )
    {
        if(sorted)
        {
            //insert in a sorted fasion
            data.sortedPush(newItem);
        }
        else
        {
            // un-sorted list
            data.push(newItem);
        }
    }
    
    //getter for if the internal list is sorted
    bool intCollection::isSorted()
    {
        return sorted;
    }
    
    //getter to check if the internal list is empty
    bool intCollection::isEmpty()
    {
        return data.isEmpty();
    }
    
    // remove the smallest value in the container and return the value
    intCollection::value_type intCollection::extract()
    {
        //intCollection.extract()
        int lowestValue = data[0];
        if(!sorted)
        {
            //unsorted List
            //this will "sort" the list in order to output a sorted element
            //i.e. this checks all elements in list "data" before determinig what is the lowest value
            for(int i=1; i < data.size(); i++)
            {
                if(data[i] < lowestValue)
                {
                    lowestValue = data[i];
                }
            }
        }
        //lowestValue contains the lowest value
        //delete the value
        data.kill(lowestValue);
        return lowestValue;
    }
    
    // get the size of the data vector
    size_t intCollection::size(void)
    {
        return data.size();
    }
}

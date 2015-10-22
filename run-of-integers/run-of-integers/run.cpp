//  run.cpp

#include "run.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Run operator+(const Run &run1, const Run &run2)
{
    // Create a copy of list1 & list 2 so we're not modifying the original list
    vector<int> list1(run1.nList);
    vector<int> list2(run2.nList);

    // New list to store the sorted data
    vector<int> list3;
    
    while(!list1.empty() || !list2.empty() ) // List 1 has elements OR list 2 has elements
    {
        if(!list1.empty() && !list2.empty()) // List 1 has elements, list 2 has elements
        {
            if(list1.front() < list2.front())
            {
                list3.push_back(list1.front()); // Put the first element of list 1 into list3
                list1.erase(list1.begin()); // Delete the first element in list 1
            }
            else
            {
                list3.push_back(list2.front());
                list2.erase(list2.begin());
            }
        }
        else if(list2.empty()) // List 1 has elements, list 2 is empty
        {
            list3.push_back(list1.front());
            list1.erase(list1.begin());
        }
        else // List 2 has elements, list 1 is empty
        {
            list3.push_back(list2.front());
            list2.erase(list2.begin());
        }
    }
    
    Run sortedList (list3);
    return sortedList;
}

vector<int> Run::getList() {
    return nList;
}

// this function is not used
Run Run::mergedRun(Run run)
{
    Run mergedRun;
    mergedRun = mergedRun + run;
    return mergedRun;
}

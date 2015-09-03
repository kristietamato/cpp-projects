//  floatCollection.cpp

#include "floatCollection.h"
#include <string>
#include <iostream>
using namespace std;

floatCollection::floatCollection(float theFloat)
{
    // Allocate memory for the pointer
    floatPointer = new float;
    *floatPointer = theFloat;
}

floatCollection::floatCollection(const floatCollection &average)
{
    // Allocate pointer and copy the value
    floatPointer = new float;
    *floatPointer = *average.floatPointer;
}

float floatCollection::getAverage(void)
{
    return *floatPointer;
}

void insertFloat()
{
    
}

void displayAverage(floatCollection average)
{
    cout << "The nearest value to the average is " << average.getAverage() << endl;
}

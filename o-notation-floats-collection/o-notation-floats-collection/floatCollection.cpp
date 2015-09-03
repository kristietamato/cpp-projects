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

floatCollection::~floatCollection(void)
{
    // Delete object
    delete floatPointer;
}

float floatCollection::getFloatAverage(void)
{
    return *floatPointer;
}

void displayAverage(floatCollection average)
{
    cout << "The average is " << average.getFloatAverage() << endl;
}

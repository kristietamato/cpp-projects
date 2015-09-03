// floatCollection.cpp

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

float floatCollection::getAverage(int arraySize)
{
    float sum;
    for(int counter = 0; counter < arraySize; counter++)
    {
        sum = sum + insertFloat(counter, arraySize);
    }
    return sum/arraySize;
}

// O(n)
float floatCollection::insertFloat(float value, int arraySize)
{
    for(int counter = arraySize; counter < arraySize + 1; counter++)
    {
        floatsArray[counter] = value;
        cout << floatsArray[counter];
    }
    value = *floatPointer;

    return *floatPointer;
}

void displayAverage(floatCollection average, int arraySize)
{
    cout << "The average is " << average.getAverage(arraySize) << endl;
}

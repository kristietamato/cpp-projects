// floatCollection.cpp

#include "floatCollection.h"
#include <string>
#include <iostream>
#include <vector>
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
}

float floatCollection::getAverage(int arraySize)
{
    float sum = 0;
    for(int counter = 0; counter < arraySize + 1; counter++)
    {
        sum = sum + floatsArray[counter];
    }
    return (sum/arraySize);
}

// O(n)
void floatCollection::insertFloat(float value, int arraySize)
{
    size_t size = 100;
    vector<float> floatsArray(size);
    for(int counter = 0; counter < arraySize; counter++)
    {
        floatsArray[counter] = counter;
        floatsArray.push_back(value);
    }
}

void floatCollection::displayAverage(int arraySize)
{
    cout << "The nearest average is " << getAverage(arraySize) << endl;
}

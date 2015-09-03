// floatCollection.h

#include <string>
#include <iostream>
using namespace std;

#ifndef FLOAT_COLLECTION
#define FLOAT_COLLECTION

const int CAPACITY = 1000;

class floatCollection
{
    public:
        floatCollection(float theFloat); // Simple constructor
        floatCollection(const floatCollection &average); // Copy constructor
        float insertFloat(float value, int arraySize);
        float getAverage(int arraySize);
    
    private:
        float *floatPointer;
        float floatsArray[CAPACITY];
};

void displayAverage(floatCollection average, int arraySize);

#endif

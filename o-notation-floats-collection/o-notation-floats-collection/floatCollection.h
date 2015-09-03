// floatCollection.h

#include <string>
#include <iostream>
using namespace std;

#ifndef FLOAT_COLLECTION
#define FLOAT_COLLECTION

class floatCollection
{
    public:
        floatCollection(float theFloat); // Simple constructor
        floatCollection(const floatCollection &average); // Copy constructor
        void insertFloat(float value, int arraySize);
        float getAverage(int arraySize);
        void displayAverage(int arraySize);
    
    private:
        float *floatPointer;
        float floatsArray[];
};

#endif

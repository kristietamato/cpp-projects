//  floatCollection.h

#include <string>
#include <iostream>
using namespace std;

#ifndef FLOAT_COLLECTION
#define FLOAT_COLLECTION

class floatCollection
{
    public:
        float getFloatAverage(void);
        floatCollection(float theFloat); // Simple constructor
        floatCollection(const floatCollection &average); // Copy constructor
        ~floatCollection(); // Destructor
    
    private:
        float *floatPointer;
};

void displayAverage(floatCollection average);

#endif

//  main.cpp
//  Created by Kristie Nguyen on 9/15.
//  o-notation-floats-collection

#include <iostream>
#include <string>
#include "tools.h"
using namespace std;

int main(void)
{
    try
    {
        
    }
    catch (exception e)
    {
        cout << "Error" << endl;
    }
    return 0;
}

class floatCollection
{
    public:
        float getFloat( void );
        floatCollection( float theFloat );
        floatCollection( const floatCollection &obj);
        ~floatCollection();
    
    private:
    float *floatPointer;

};
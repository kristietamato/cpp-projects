//  main.cpp
//  Created by Kristie Nguyen on 9/15.

#include <iostream>
#include <string>
#include "tools.h"
#include "floatCollection.h"
using namespace std;

int main(void)
{
    try
    {
        floatCollection floatCollection(19);
        displayAverage(floatCollection);
    }
    catch (exception e)
    {
        cout << "Error" << endl;
    }
    return 0;
}
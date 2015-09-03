//  main.cpp
//  Created by Kristie Nguyen on 9/15.

#include <iostream>
#include <string>
#include "tools.h"
#include "floatCollection.h"
using namespace std;
using namespace tools;

int main(void)
{
    try
    {
        floatCollection floatCollection1(10);

        if(getBool("Do you want to enter data? "))
        {
            bool finishedInput = false;
            int value;
            do
            {
                value = getBoundedInt("Enter a data item, or 0 if you may be finished: ", 0, 100);
                if(value != 0)
                {
                    // Insert value
                }
                else
                {
                    // Ask if it's a value to be included
                    if(getBool("Do you want to add 0 to the collection? "))
                    {
                        // Insert value
                        cout << "Value included." << endl;
                    }
                    else
                    {
                        finishedInput = true;
                    }
                }
            }
            while(!finishedInput);

            displayAverage(floatCollection1);
        }
    }
    catch (exception e)
    {
        cout << "Error" << endl;
        pause("Press ENTER to close...");
    }

    pause("Press ENTER to close...");
    return 0;
}
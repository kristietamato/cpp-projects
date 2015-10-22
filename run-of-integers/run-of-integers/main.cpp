//  main.cpp
//  Created by Kristie Nguyen on 9/15.
//  A program that sorts a list of integer values from a txt file and outputs them as a txt file.

#include <iostream>
#include "tools.h"
#include "run.h"
using namespace std;
using namespace tools;

Run compactRuns(vector<Run> runs);

int main()
{
    vector<Run> myRuns;

    // read and insert at least 1 data item from file
    while(true)
    {
        // open the txt with data
        ifstream infile;
        openFStream(infile, "Enter name of file containing integer data: ");
        
        // process all data items from a file
        while(true)
        {
            int newData;
            infile >> newData;
            if(!infile) break;
            
            // create a Run for the data
            Run myRun(newData);
            
            // add the new Run to myRuns vector
            myRuns.push_back(myRun);
        }
        if(!myRuns.empty()) break;
        cout << "No data in file: Try again." << endl;
    }
    
    // myRuns now contains data from the txt file
    
    // Compact myRuns via log_2(n)
    Run result(compactRuns(myRuns));
    
    //resultList is the vector of "sorted" integers
    vector<int> resultList(result.getList());
    
    // get the output txt file
    ofstream outfile;
    openFStream(outfile, "Enter name of file to output integer data: ");
    
    // run through resultList and print the sorted vector of Runs to the txt file
    int counter = 1;
    for(int data : resultList)
    {
        if(counter%10 == 0) { // output new line every 10th element
            outfile << data << endl;
        }
        else
        {
            outfile << data << " ";
        }
        counter++;
    }
    
    pause("The file has been created. Press ENTER to close...");
    return 0;
}

Run compactRuns(vector<Run> runs)
{
    vector<Run> newRuns;
    
    // compact run pairs while there is data in runs
    while(!runs.empty())
    {
        if(runs.size() > 1) // there's at least two elements so summing pairs
        {
            Run run1(runs.back()); // get the last element and put in run1
            runs.pop_back(); // delete the last element from runs
            Run run2(runs.back()); // get the last element and put in run2
            runs.pop_back();
            newRuns.push_back(run1 + run2); // use the + friend operator to merge the runs
        }
        // there's one last element
        else
        {
            // can't sum a single element, so just append it to newRuns
            Run run(runs.back());
            runs.pop_back();
            newRuns.push_back(run);
        }
    }
    // newRuns is now ~half the size of runs
    
    // recurse or return single Run if only 1 element in vector
    if(newRuns.size() > 1)
    {
        return compactRuns(newRuns);
    }
    else
    {
        // newRuns now only has 1 element with all the data so return it
        return newRuns.front();
    }
}
//  main.cpp
//  Created by Kristie Nguyen on 9/19/15.
//

#include"linked-list.h"
#include"tools.h"
#include"int-collection.h"
#include<iostream>
#include<fstream>

using namespace std;
using namespace tools;
using namespace linked_list;
using namespace CollectionSpace;

void printList(Node *np);
void firstFunction(void);
void loadFile(intCollection &collection);
void outputFile(intCollection &collection);

int main(void)
{
    // order or un-odered?
    intCollection collection (getBool("Do you want the list to be ordered? "));
    
    // get file
    loadFile( collection );
    
    // output file
    outputFile(collection);

    cout << endl;
    pause("Press ENTER to finish...");
    return 0;
}

void loadFile( intCollection &collection )
{
    // read and insert at least 1 data item from file
    while (true)
    {
        ifstream infile;
        openFStream( infile, "Enter name of data file: " );
        
        // process all data items from a file
        while (true)
        {
            int newData;
            infile >> newData;
            if ( !infile ) break;
            collection.insert( newData );
        }
        if ( collection.size() > 0 ) break;
        cout << "No data in file: Try again." << endl;
    }
}

void outputFile(intCollection &collection )
{
    ofstream sortedDataStream;
    openFStream( sortedDataStream, "Enter name of file for sorted results: " );

    int lineCount = 1;
    //keep extracting elements from the collection until it is empty.
    while(!collection.isEmpty())
    {
        sortedDataStream << collection.extract() << ' ';
        //create a new line every 10th element
        if ( lineCount%10 == 0 )
        {
            sortedDataStream << endl;
        }
        lineCount++;
    }
    
}
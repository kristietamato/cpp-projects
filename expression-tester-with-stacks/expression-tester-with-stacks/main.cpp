//  main.cpp
//  expression-tester-with-stacksn

//  Created by Kristie Nguyen on 10/11/15.

#include<iostream>
#include<string>
#include<algorithm>
#include"tools.h"
#include"expression-tester.h"
using namespace std;
using namespace tools;
using namespace expression_tester;

// test expressions in a file
void testFile();

// test each string expression
void testExpression( string expressionCandidate );

int main(void)
{
    if ( getBool( "Do you want to read the data from a file? " ) )
    {
        testFile( );
    }

    while ( true )
    {
        string expressionCandidate = getLine("Enter a line to test or enter nothing to quit: ");

        testExpression( expressionCandidate );
        
        if ( expressionCandidate == "" && getBool("Do you want to quit? ") ) break;
    }
    
    return 0;
}

void testFile()
{
    // read and insert at least 1 data item from file
    while (true)
    {
        bool data_in_file=false;
        ifstream infile;
        openFStream( infile, "Enter name of data file: " );

        // process all data items from a file
        while (true)
        {
            string expression;
            infile >> expression;
            if ( !infile ) break;
            if(!data_in_file) data_in_file=true;
            cout << "Testing: \"" << expression << "\":" << endl;
            
            testExpression( expression );
        }
        if (!data_in_file)
        {
            cout << "No data in file: Try again." << endl;
        }
        else
        {
            break;
        }
    }
}

void testExpression( string expressionCandidate )
{
    if ( isExpression( expressionCandidate ) )
    {
        cout << "That is a WFF." << endl;
    }
    else
    {
        cout << "That is not a WFF." << endl;
    }
    
    cout << endl;
}
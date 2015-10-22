// Jim Hester
// Some usefull tools

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

#ifndef TOOLS
#define TOOLS

namespace tools
{
    extern const string WHITESPACE;
    
    void pause( string prompt = "Press ENTER to continue..." );
    void flushInput(void);
    
    char	lowerCase( char c );
    string	lowerCase( string s );
    
    bool isIn			( string pattern, string source );
    bool isInCaseless	( string pattern, string source );
    bool isWhitespace	( char c );
    bool isEmpty		( string s );
    
    void	chomp		( string &s );
    string	swab		( char c, int length );
    string	extractWord	( string &source );
    string	substitute	( string source, string pattern, string replacement );
    string	pluralize	( int count, string singular, string plural );
    
    void swap( int &a, int &b );
    int numberWidth( int n );
    int randomInt( int lowerBound, int upperBound );
    
    string	getLine				( string prompt );
    bool	getBool				( string prompt );
    int		getNonNegativeInt	( string prompt );
    int		getBoundedInt		( string prompt, int lowerBound, int upperBound );
    int		getPercent			( string prompt );
    int getBoundedIntWithErrorMessage( string prompt, int lowerBound, int upperBound, string errorMessage );
    
    template<class T>
    T getValue ( string prompt )
    {
        do
        {
            istringstream inputLine( getLine( prompt ) );
            T userInput;
            inputLine >> userInput;
            if ( inputLine.fail() )
            {
                cout << "Input format error: please try again." << endl;
                continue;
            }
            char junk;
            inputLine >> junk;
            if ( !inputLine.fail() )
            {
                cout << "Input format error: please try again." << endl;
                continue;
            }
            return userInput;
        }
        while ( true );
    }
    
    template<class T>
    void openFStream( T &FStream, string prompt )
    {
        do
        {
            FStream.open( getLine( prompt ) );
            if ( !FStream.fail() ) break;
            cout << "File Open Failure." << endl;
            FStream.clear();
        } while (true);
    }
}

#endif


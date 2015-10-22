//  Position.h
//  knights-trip-with-queues

#ifndef POSITION_LOCK
#define POSITION_LOCK

#include <string>
#include <iostream>
#include <stdexcept>
#include <ctype.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// represents the position of the Knight on the chess board e.g. "a1" "c7" etc.
class Position
{
public:
    // the x-axis is represented by letters 'a' through 'h'
    typedef char Horizontal;
    
	// the y-axis is represented by numbers 1 through 8 and stored as characters
    typedef char Vertical;

    // the Track type is used to represent a move from  position
    // can be a positive or negative offset for horizontal and vertical
    struct Track
    {
        Track( int horizontalOffset, int verticalOffset ) : horizontal(horizontalOffset), vertical(verticalOffset) {}
        int horizontal;
        int vertical;
    };
    
	// define the min and max dimension of the chess board
    static const Horizontal minHorizontal = 'a';
    static const Horizontal maxHorizontal = 'h';
    static const Vertical minVertical = '1';
    static const Vertical maxVertical = '8';
    
	// default constructor initializes Position to "a1"
    Position() : m_horizontal(minHorizontal), m_vertical(minVertical) {}
    
	// constructor to form 2-char string from input representing position on the chess board
	// uppercase is converted to lowercase
    Position( const char* strPos  );
    
	// check if the move is valid
    bool isValidMove( const Track& track ) const;

    // move by the supplied track
    Position& move( const Track& track );
    
    // accessors for horizontal
    Horizontal getHorizontal() const;

    // accessors for vertical
    Vertical getVertical() const;
    
	// equality operator to determine when we reached the goal
    bool operator==(const Position &pos) const;
	// inequality operator
    bool operator!=(const Position &pos) const;

    // compound addition operator for moving positions by Tracks
    Position& operator+=( const Track &track );
	// addition operator that returns a const Position so result can be used as value
    const Position operator+( const Track& track ) const;
    
    // output operator that can display our positions
    friend ostream& operator<< (ostream& stream, const Position& pos );

    // input operator that can read positions from standard input
    friend istream& operator>> (istream& stream, Position& pos );

private:
    // range check horizontal
    bool isValidHorizontal( Horizontal x ) const;

    // range check vertical
    bool isValidVertical( Vertical y ) const;
    
    Horizontal m_horizontal;
    Vertical m_vertical;
};

#endif
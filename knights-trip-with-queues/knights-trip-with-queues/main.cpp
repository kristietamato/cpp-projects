//  main.cpp
//  knights-trip-with-queues
//  Created by Kristie Nguyen on 10/20/15.
//  A program that finds the shortest path for a Knight to travel on a chessboard using a queue data structure.

#include "KnightsTripHelper.h"
#include "Tools.h"

using namespace tools;

void solveKnightsTrip( const Position& start, const Position& goal)
{
    Position posStart(start), posGoal(goal);
    KnightsTripHelper helper(posGoal);
    
    Search<Position> solver( posStart, helper );
    
    Search<Position>::States result = solver.findShortestPathToGoal();
    
    for(Search<Position>::States::const_iterator i = result.begin(); i != result.end(); i++)
    {
        cout << *i;
        if( i < result.end() - 1 )
        {
            cout << ", ";
        }
    }
    
    cout << endl << endl;
}

int main()
{
    Position start, goal;
    
    try
    {
        int sizeOfBoard = getBoundedInt( "Enter size of board: ", 4, 26 );
        cout << endl;
        
        cout << "Enter starting cell (example b2): ";
        cin >> start;

        cout << "Enter goal cell:                  ";
        cin >> goal;
        cout << endl;

        solveKnightsTrip( start, goal );
    }
    catch( exception& ex)
    {
        // something bad happened - probably invalid arguments
        cout << "Error: " << ex.what() << endl;
        flushInput();
        pause("Press ENTER to finish...");
        return 1;
    }
    
    flushInput();
    pause();
    return 0;
}
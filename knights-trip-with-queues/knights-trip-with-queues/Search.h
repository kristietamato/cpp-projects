//  Search.h
//  knights-trip-with-queues
//  Class to find shortest path to goal

#ifndef SEARCH_LOCK
#define SEARCH_LOCK

#include "ChessPiece.h"

template<class State>
class Search
{
    
public:
    // represents the paths to our goal
    typedef vector<State> States;
    
    // helps find the next state for the path and tests the goal
    class SearchHelper
    {
        
    public:
        // override this function to return true if we have reached the goal
        virtual bool isGoal( const State& s) const = 0;
        
        // override this function to return a list of successor states from the current state
        virtual States getSuccessors( const State& s ) const = 0;
    };
    
    // constructor that takes the start state and a helper object
    Search( const State& start, const SearchHelper& helper ) : m_start(start), m_helper(helper) {}
    
    // find the shortest path to the goal state.
    // if no path is found then return an empty list
    States findShortestPathToGoal()
    {
        // an ordered list of possible paths to use from shortest to longest
        typedef queue<States> OrderedPaths;
        
        // keep track of states which have already been visited.
        typedef vector<State> Visited;
        
        // first check if we are already at the goal. If so we're done
        if( m_helper.isGoal(m_start))
        {
            States result;
            result.push_back(m_start);
            return result;
        }

        // set of states we have visited so far
        Visited visited;
        
        // ordered list of paths which have already been gone through.
        // Start with the path containing the start state only.
        OrderedPaths orderedPaths;
        States initialPath;
        initialPath.push_back( m_start );
        orderedPaths.push(initialPath);
        
        // keep going while there are still uncompleted paths
        while( !orderedPaths.empty() )
        {
            // expand the shortest path in the frontier first
            States path = orderedPaths.front();
            orderedPaths.pop();
            State s = path.back();
            
            // now iterate through the successor states
            States successors = m_helper.getSuccessors( s );
            for( typename States::const_iterator i = successors.begin(); i != successors.end(); i++)
            {
                const State& state = *i;

                // has this state been visited already?
                if( find( visited.begin(), visited.end(), state ) == visited.end() )
                {
                    // no... mark it as visited
                    visited.push_back(state);

                    // construct a new path with the current state at the end
                    States visitedPath(path);
                    visitedPath.push_back(state);
                    if( m_helper.isGoal(state))
                    {
                        // return the path to the goal
                        return visitedPath;
                    }
                    else
                    {
                        // haven't found the path to the goal yet so add this path to the orderedPaths and keep exploring
                        orderedPaths.push( visitedPath );
                    }
                }
            }
        }
        
        // if we got here we couldn't find a path to the goal
        States emptyPath;
        return emptyPath;
    }
    
private:
    // start state
    State m_start;

    // search helper
    const SearchHelper& m_helper;
};

#endif
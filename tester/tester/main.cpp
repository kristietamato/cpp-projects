#include <string>
#include <iostream>
#include <stdexcept>
#include <ctype.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//
// represents the position of a chess piece on a chess board in algebraic notation.
//
class Position
{
public:
    //
    // horizontal positions are known as rank and represented by letters A through H
    // internally stored as capital letters, but we convert from lowercase if that was passed in the constructor
    //
    typedef char Rank;
    
    //
    // vertical postion or file represented by numbers 1 through 8
    // (actually stored as ascii values).
    //
    typedef char File;
    
    //
    // the Delta type is used to represent a move from  position
    // can be a positive or negative offset for rank and file
    //
    struct Delta
    {
        Delta( int rankOffset, int fileOffset ) : rank(rankOffset), file(fileOffset) {}
        int rank;
        int file;
    };
    
    //
    // define maximum and minimum values for dimension of chessboard.
    // we don't have to actually model a chessboard to solve this problem,
    // however if we needed to deal with other pieces on the chessboard it might be useful to do so
    //
    static const Rank minRank = 'A';
    static const Rank maxRank = 'H';
    static const File minFile = '1';
    static const File maxFile = '8';
    
    //
    // default constructor initializes to "A1"
    //
    Position() : m_rank(minRank), m_file(minFile) {}
    
    //
    // construct from a string as read from input
    // PRECONDITION: pos is a 2 character string representing an chess position in algebraic notation
    // may be uppercase or lowercase
    //
    Position( const char* strPos  )
    {
        if(!strPos)
            throw std::invalid_argument( "strPos must point to a 2 character string in algebraic chess notaion" );
        
        Rank r = toupper(strPos[0]);
        File f = strPos[1];
        
        if( isValidFile(f) && isValidRank(r) )
        {
            m_rank = r;
            m_file = f;
        }
        else
        {
            throw std::invalid_argument( "rank and/or file are out of range" );
        }
    }
    
    //
    // return true if its a legal move, ie: within the bounds of the chessboard
    //
    bool isValidMove( const Delta& delta ) const
    {
        return isValidRank( m_rank + delta.rank ) && isValidFile( m_file + delta.file);
    }
    
    //
    // move by the supplied delta
    //
    Position& move( const Delta& delta )
    {
        if ( isValidMove( delta) )
        {
            //
            // we are relying on the property that ascii values are consecutive
            // for consecutive numbers and letters, which makes the move calculation
            // nice and easy
            //
            m_rank += delta.rank;
            m_file += delta.file;
        }
        else
        {
            throw std::invalid_argument( "move is out of range" );
        }
        
        return *this;
    }
    
    //
    // accessors for rank
    //
    Rank getRank() const
    {
        return m_rank;
    }
    
    //
    // accessors for file
    //
    File getFile() const
    {
        return m_file;
    }
    
    //
    // define equality operator which will be useful for determining when we have reached the goal
    //
    bool operator==(const Position &rhs) const
    {
        return m_rank == rhs.m_rank && m_file == rhs.m_file;
    }
    
    //
    // for completeness, define inequality operator
    //
    bool operator!=(const Position &rhs) const
    {
        //
        // use equality relationship to avoid duplicating code
        //
        return !( (*this) == rhs);
    }
    
    //
    // and why not an compound addition operator for moving positions by Deltas
    //
    Position& operator+=( const Delta &delta )
    {
        return move( delta );
    }
    
    //
    // once again for completeness we can define and addition operator using the above += definition
    // returns a const Position so result cant be used as an lvalue
    //
    const Position operator+( const Delta& delta ) const
    {
        Position newPos = *this;
        newPos += delta;
        return newPos;
    }
    
    //
    // so we can display our positions
    //
    friend std::ostream& operator<< (std::ostream& stream, const Position& pos )
    {
        stream << pos.m_rank << pos.m_file;
        return stream;
    }
    
    //
    // so we can read positions from standard input
    //
    friend std::istream& operator>> (std::istream& stream, Position& pos )
    {
        string strPos;
        stream >> strPos;
        Position tempPos( strPos.data() );
        pos = tempPos;
        
        return stream;
    }
    
private:
    
    //
    // range check rank
    //
    bool isValidRank( Rank r ) const
    {
        return r <= maxRank && r >= minRank;
    }
    
    //
    // range check file
    //
    bool isValidFile( File f ) const
    {
        return f <= maxFile && f >= minFile;
    }
    
    Rank m_rank;
    File m_file;
    
};

namespace ChessPiece {

//
// base class representing chess pieces basic functionality
//
class ChessPiece
{
    
protected:
    
    //
    // we don't want anyone instantiating this class directly,
    // they must derived from it and call initDeltas() to setup
    // the allowable moves for the piece
    //
    ChessPiece( const Position& pos ) : m_currentPos(pos)
    {}
    
public:
    
    //
    // list of Deltas representing the directions and distances this piece is allowed to move
    //
    typedef vector<Position::Delta> Deltas;
    
    //
    // return the rank and file offsets determining this pieces relative movements
    //
    const Deltas& getDeltas() const
    {
        return m_deltas;
    }
    
    //
    // list of positions used to represent where this piece can move to
    //
    typedef vector<Position> Moves;
    
    //
    // returns a list of valid moves from the current position
    //
    Moves& getValidMoves()
    {
        if( !m_validMoves.size() )
        {
            //
            // lazily calculate valid moves from current position
            //
            Deltas deltas = getDeltas();
            for( Deltas::const_iterator i = getDeltas().begin(); i != getDeltas().end(); i++ )
            {
                const Position::Delta& delta = *i;
                if( m_currentPos.isValidMove( delta ) )
                {
                    Position newPos = m_currentPos + delta;
                    m_validMoves.push_back( newPos );
                }
            }
        }
        return m_validMoves;
    }
    
    //
    // return current position
    //
    const Position& getPosition() const
    {
        return m_currentPos;
    }
    
protected:
    
    //
    // helper so derived classes can initialize m_deltas from a
    // plain old c style array
    //
    void initDeltas( const Position::Delta * d, size_t numberOfDeltas)
    {
        m_deltas = Deltas( d, d + numberOfDeltas );
    }
    
    //
    // current position
    //
    Position m_currentPos;
    
    //
    // list of directions and distances the chess piece can move.
    // Should be initialized by any derived classes
    //
    Deltas m_deltas;
    
    //
    // all the moves in relation to the current position.
    // it is defined as mutable to allow for lazy evaluation
    //
    Moves m_validMoves;
};

//
// all valid moves for a knight
//
static Position::Delta deltas[] = {
    Position::Delta(1,2), Position::Delta(2,1),
    Position::Delta(2,-1), Position::Delta(1,-2),
    Position::Delta(-2,-1), Position::Delta(-1,-2),
    Position::Delta(-2,1), Position::Delta(-1,2)
};

//
// Knight is an instance of ChessPiece with movement deltas which allow it to move
// 2 squares horizontaly and 1 square vertically and vice versa
//
class Knight : public ChessPiece
{
    
public:
    
    Knight( const Position& pos) : ChessPiece(pos)
    {
        //
        // setup the valid moves
        //
        initDeltas( deltas ,  sizeof(deltas)/sizeof(deltas[0]) );
    }
    
};
    
}


//
// utility class for finding shortest path to goal utilizing Uniform Cost Search,
// also known as Least Cost Search, a variation of Bredth First Search.
// template argument must support operator= otherwise it wont compile ;)
//
template<class State>
class UniformCostSearch
{
public:
    
    //
    // path to our goal state is represented as a list of states
    //
    typedef vector<State> States;
    
    //
    // abstract helper class which provide goal test function and
    // successor states for the search
    //
    class SearchHelper
    {
    public:
        
        //
        // override this function to return true if we have reached the goal
        //
        virtual bool isGoal( const State& s) const = 0;
        
        //
        // override this function to return a list of successor states from the current state
        //
        virtual States getSuccessors( const State& s ) const = 0;
        
    };
    
    //
    // constructor takes the start state and a helper function object
    //
    UniformCostSearch( const State& start, const SearchHelper& helper ) : m_start(start), m_helper(helper) {}
    
    //
    // initiates a uniform cost search to find the shortest path to the goal state.
    // if no path is found then it returns an empty list
    //
    States findShortestPathToGoal()
    {
        
        //
        // the frontier is an ordered list of paths we have blazed fro mthe start state (from shortest to longest),
        // since every action has the same cost there is no need to use a priority queue
        //
        typedef queue<States> Frontier;
        
        //
        // keep track of states which have already been explored.
        // for larger searches a set would be better, but it requires State to support
        // operator< so lets use a list even though search time is linear
        //
        typedef vector<State> Explored;
        
        //
        // first check if we are already at the goal. If so we're done
        //
        if( m_helper.isGoal(m_start))
        {
            States result;
            result.push_back(m_start);
            return result;
        }
        
        //
        // set of states we have visited so far
        //
        Explored explored;
        
        //
        // ordered list of paths which have already been blazed.
        // Start with the path containing the start state only.
        //
        Frontier frontier;
        States initialPath;
        initialPath.push_back( m_start );
        frontier.push(initialPath);
        
        //
        // keep going whilst there are still unexplored paths
        //
        while( !frontier.empty() )
        {
            //
            // expand the shortest path in the frontier first
            //
            States path = frontier.front();
            frontier.pop();
            State s = path.back();
            
            //
            // now explore the successor states
            //
            States successors = m_helper.getSuccessors( s );
            for( typename States::const_iterator i = successors.begin(); i != successors.end(); i++)
            {
                const State& state = *i;
                
                //
                // has this state been explored already?
                //
                if( find( explored.begin(), explored.end(), state ) == explored.end() )
                {
                    //
                    // no... mark it as explored
                    //
                    explored.push_back(state);
                    //
                    // construct a new path with the current state at the end
                    //
                    States exploredPath(path);
                    exploredPath.push_back(state);
                    if( m_helper.isGoal(state))
                    {
                        //
                        // return the path to the goal
                        //
                        return exploredPath;
                    }
                    else
                    {
                        //
                        // haven't found the path to the goal yet so add this path to the frontier and keep exploring
                        //
                        frontier.push( exploredPath );
                    }
                }
            }
        }
        
        //
        // if we got here we couldn't find a path to the goal
        //
        States emptyPath;
        return emptyPath;
    }
    
private:
    
    //
    // start state
    //
    State m_start;
    
    //
    // search helper
    //
    const SearchHelper& m_helper;
    
};

//
// this helper class is used to determine when we have reached the goal and also
// generate the successor positions
//
class KnightsTravailHelper : public UniformCostSearch<Position>::SearchHelper
{
public:
    KnightsTravailHelper( const Position& goal) : m_goal(goal) {}
    
    virtual bool isGoal( const Position& s) const
    {
        return s == m_goal;
    }
    
    virtual UniformCostSearch<Position>::States getSuccessors( const Position& s ) const
    {
        ChessPiece::Knight theKnight(s);
        return theKnight.getValidMoves();
    }
    
private:
    Position m_goal;
};

void solveKnightsTravail( const Position& start, const Position& end)
{
    Position posStart(start), posEnd(end);
    KnightsTravailHelper helper(posEnd);
    
    UniformCostSearch<Position> solver( posStart, helper );
    
    UniformCostSearch<Position>::States result = solver.findShortestPathToGoal();
    
    for(UniformCostSearch<Position>::States::const_iterator i = result.begin(); i != result.end(); i++)
    {
        cout << *i << ", ";
    }
    
    cout << endl;
}

int main()
{
    Position start, end;
    
    try
    {
        cin >> start >> end;
        solveKnightsTravail( start, end );
    }
    catch( exception& ex)
    {
        ///
        // something bad happened - probably invalid arguments
        //
        cout << "error: " << ex.what() << endl;
        return 1;
    }
    
    return 0;
}
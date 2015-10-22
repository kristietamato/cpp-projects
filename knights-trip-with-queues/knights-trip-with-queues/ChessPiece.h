// A chess piece namespace with Knight class

#ifndef NAMESPACE_CHESS_PIECE_LOCK
#define NAMESPACE_CHESS_PIECE_LOCK

#include "Position.h"

// represents chess pieces basic functions
namespace namespaceChessPiece
{
    // represents chess pieces basic functions
    class ChessPiece
    {

    public:

        // list of Tracks representing the directions and distances this piece is allowed to move
        typedef vector<Position::Track> Tracks;

        // list of positions used to represent where the piece can move to
        typedef vector<Position> Moves;

        // return the horizontal and vertical offsets determining this pieces relative movements
        const Tracks& getTracks() const;
        
        // returns a list of valid moves from the current position
        Moves& getValidMoves();
        
        // return current position
        const Position& getPosition() const;
    
    protected:
        // current position
        Position m_currentPos;

        // list of directions and distances the chess piece can move.
        Tracks m_tracks;

        // all the moves in relation to the current position.
        Moves m_validMoves;

        // constructor to instantiate the class
        ChessPiece( const Position& pos ) : m_currentPos(pos) {}
        
        // initialize moves from an array
        void initTracks( const Position::Track *d, size_t numberOfTracks);
    };

    // all valid moves for a knight
    static Position::Track tracks[] =
    {
        Position::Track(1,2), Position::Track(2,1),
        Position::Track(2,-1), Position::Track(1,-2),
        Position::Track(-2,-1), Position::Track(-1,-2),
        Position::Track(-2,1), Position::Track(-1,2)
    };

    // Knight is an instance of ChessPiece with movement tracks which allow it to move
    // 2 squares horizontaly and 1 square vertically and vice versa
    class Knight : public ChessPiece
    {
        
    public:  
        Knight( const Position& pos) : ChessPiece(pos)
        {
            // setup the valid moves
            initTracks( tracks , sizeof(tracks)/sizeof(tracks[0]) );
        }
    };
}
#endif
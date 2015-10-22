//  ChessPiece.cpp
//  knights-trip-with-queues

#include "ChessPiece.h"

namespace namespaceChessPiece
{
    const ChessPiece::Tracks& ChessPiece::getTracks() const
    {
        return m_tracks;
    }
    
    ChessPiece::Moves& ChessPiece::getValidMoves()
    {
        if( !m_validMoves.size() )
        {
            // calculate valid moves from current position
            Tracks tracks = getTracks();
            for( Tracks::const_iterator i = getTracks().begin(); i != getTracks().end(); i++ )
            {
                const Position::Track& track = *i;
                if( m_currentPos.isValidMove( track ) )
                {
                    Position newPos = m_currentPos + track;
                    m_validMoves.push_back( newPos );
                }
            }
        }
        return m_validMoves;
    }
    
    const Position& ChessPiece::getPosition() const
    {
        return m_currentPos;
    }
    
    void ChessPiece::initTracks( const Position::Track * d, size_t numberOfTracks)
    {
        m_tracks = Tracks( d, d + numberOfTracks );
    }
    
}
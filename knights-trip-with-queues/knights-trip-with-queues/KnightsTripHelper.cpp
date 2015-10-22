//  KnightsTripHelper.cpp
//  knights-trip-with-queues

#include "KnightsTripHelper.h"

bool KnightsTripHelper::isGoal( const Position& s) const
{
    return s == m_goal;
}

Search<Position>::States KnightsTripHelper::getSuccessors( const Position& s ) const
{
    Knight::Knight theKnight(s);
    return theKnight.getValidMoves();
}
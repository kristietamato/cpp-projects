//  Position.cpp
//  knights-trip-with-queues

#include "Position.h"

Position::Position( const char* strPos  )
{
    if(!strPos)
        throw invalid_argument( "Invalid data format, please try again." );
    
    Horizontal r = tolower(strPos[0]);
    Vertical f = strPos[1];
    
    if( isValidVertical(f) && isValidHorizontal(r) )
    {
        m_horizontal = r;
        m_vertical = f;
    }
    else
    {
        throw invalid_argument( "Invalid data format, please try again." );
    }
}

bool Position::isValidMove( const Track& track ) const
{
    return isValidHorizontal( m_horizontal + track.horizontal ) && isValidVertical( m_vertical + track.vertical);
}

Position& Position::move( const Track& track )
{
    if ( isValidMove( track) )
    {
        // increase of ASCII characters one at a time is equivalent to moving one space
        m_horizontal += track.horizontal;
        m_vertical += track.vertical;
    }
    else
    {
        throw invalid_argument( "Move is out of range." );
    }
    
    return *this;
}

Position::Horizontal Position::getHorizontal() const
{
    return m_horizontal;
}

Position::Vertical Position::getVertical() const
{
    return m_vertical;
}

bool Position::operator==( const Position &pos ) const
{
    return m_horizontal == pos.m_horizontal && m_vertical == pos.m_vertical;
}

bool Position::operator!=( const Position &pos ) const
{
    return !( (*this) == pos );
}

Position& Position::operator+=( const Track &track )
{
    return move( track );
}

const Position Position::operator+( const Track& track ) const
{
    Position newPos = *this;
    newPos += track;
    return newPos;
}

ostream& operator<< (ostream& stream, const Position& pos )
{
    stream << pos.m_horizontal << pos.m_vertical;
    return stream;
}

istream& operator>> (istream& stream, Position& pos )
{
    string strPos;
    stream >> strPos;
    Position tempPos( strPos.data() );
    pos = tempPos;
    
    return stream;
}

bool Position::isValidHorizontal( Horizontal x ) const
{
    return x <= maxHorizontal && x >= minHorizontal;
}

bool Position::isValidVertical( Vertical y ) const
{
    return y <= maxVertical && y >= minVertical;
}



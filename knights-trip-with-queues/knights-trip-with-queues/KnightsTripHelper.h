//
//  KnightsTripHelper.h
//  knights-trip-with-queues
//
//  Created by Kristie Nguyen on 10/20/15.
//  Copyright (c) 2015 Kristie Nguyen. All rights reserved.
//

#ifndef KNIGHTS_TRIP_HELPER_LOCK
#define KNIGHTS_TRIP_HELPER_LOCK

#include "Search.h"

using namespace namespaceChessPiece;

// this helper class is used to determine when we have reached the goal and also
// generate the successor positions
class KnightsTripHelper : public Search<Position>::SearchHelper
{
public:
    KnightsTripHelper( const Position& goal) : m_goal(goal) {}
    
    virtual bool isGoal( const Position& s) const;
    virtual Search<Position>::States getSuccessors( const Position& s ) const;

private:
    Position m_goal;
};

#endif

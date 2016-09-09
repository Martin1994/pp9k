//
//  ChessRook.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ChessRook__
#define __pp9k__ChessRook__

#include "Chess.h"

namespace pp9k
{
    class Player;
    
    class ChessRook : public Chess
    {
        
    private:
        bool Moved;
        void AddMove(Board* board, Moves* moves, int direction_x, int direction_y, bool only_capture);
        
    public:
        ChessRook(pp9k::Player* player, int x, int y);
        ChessRook(pp9k::Player* player, int x, int y, bool moved);
        void GetAvailableMoves(Board* board, Moves* moves, bool only_capture);
        ChessType GetChessType();
        Chess* Clone();
        bool HasMoved();
        
    };
}

#endif /* defined(__pp9k__ChessRook__) */

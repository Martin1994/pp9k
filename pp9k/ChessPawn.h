//
//  ChessPawn.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ChessPawn__
#define __pp9k__ChessPawn__

#include "Chess.h"

namespace pp9k
{
    class Player;
    
    class ChessPawn : public Chess
    {
        
    private:
        bool Moved;
        bool MovedTwice;
        
    public:
        ChessPawn(pp9k::Player* player, int x, int y);
        ChessPawn(pp9k::Player* player, int x, int y, bool moved, bool moved_twice);
        void GetAvailableMoves(Board* board, Moves* moves, bool only_capture);
        ChessType GetChessType();
        Chess* Clone();
        
    };
}

#endif /* defined(__pp9k__ChessPawn__) */

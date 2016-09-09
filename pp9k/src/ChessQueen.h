//
//  ChessQueen.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ChessQueen__
#define __pp9k__ChessQueen__

#include "Chess.h"

namespace pp9k
{
    class Player;
    
    class ChessQueen : public Chess
    {
        
    private:
        void AddMove(Board* board, Moves* moves, int direction_x, int direction_y, bool only_capture);
        
    public:
        ChessQueen(pp9k::Player* player, int x, int y);
        void GetAvailableMoves(Board* board, Moves* moves, bool only_capture);
        ChessType GetChessType();
        Chess* Clone();
        
    };
}

#endif /* defined(__pp9k__ChessQueen__) */

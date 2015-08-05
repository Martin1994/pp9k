//
//  ChessKnight.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ChessKnight__
#define __pp9k__ChessKnight__

#include "Chess.h"

namespace pp9k
{
    class Player;
    
    class ChessKnight : public Chess
    {
    private:
        void AddMove(Board* board, Moves* moves, int relative_x, int relative_y, bool only_capture);
        
    public:
        ChessKnight(pp9k::Player* player, int x, int y);
        void GetAvailableMoves(Board* board, Moves* moves, bool only_capture);
        ChessType GetChessType();
        Chess* Clone();
        
    };
}

#endif /* defined(__pp9k__ChessKnight__) */

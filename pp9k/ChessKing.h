//
//  ChessKing.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ChessKing__
#define __pp9k__ChessKing__

#include "Chess.h"

namespace pp9k
{
    class Player;
    
    class ChessKing : public Chess
    {
        
    private:
        bool Moved;
        void AddMove(Board* board, Moves* moves, int relative_x, int relative_y);
        
    public:
        ChessKing(pp9k::Player* player, int x, int y);
        ChessKing(pp9k::Player* player, int x, int y, bool moved);
        void GetAvailableMoves(Board* board, Moves* moves);
        ChessType GetChessType();
        Chess* Clone();
        
    };
}

#endif /* defined(__pp9k__ChessKing__) */

//
//  Move.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Move__
#define __pp9k__Move__

#include "Chess.h"

namespace pp9k
{
    class Chess;
    
    class Move
    {
        
    private:
        Chess* ChessBeforeMove;
        Chess* ChessAfterMove;
        Chess* ChessCaptured;
        Move* SubMove;
        
    public:
        Move(Chess* before, Chess* after, Chess* captured = NULL, Move* submove = NULL);
        ~Move();
        Move* Clone();
        Chess* GetChessBeforeMove();
        Chess* GetChessAfterMove();
        Chess* GetChessCaptured();
        Move* GetSubMove();
        
    };
    
    class Moves
    {
        
    private:
        int Capacity;
        int Length;
        Move** MoveList;
        bool Confirmed;
        
    public:
        Moves();
        ~Moves();
        void AddMove(Move* move);
        void Confirm();
        Move* GetMove(int cursor);
        int GetLength();
        
    };
}

#endif /* defined(__pp9k__Move__) */

//
//  Chess.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Chess__
#define __pp9k__Chess__

#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Enumerations.h"

namespace pp9k
{
    class Player;
    class Board;
    class Move;
    class Moves;
    
    class Chess
    {
    private:
        class Player* Player;
        int X;
        int Y;
        
    public:
        
        Chess(pp9k::Player* player, int x, int y);
        virtual ~Chess();
        virtual Chess* Clone() = 0;
        Chess* ReplacePlayer(pp9k::Player* new_player);
        
        pp9k::Player* GetPlayer();
        
        /**
         * Get all possible moves of this piece
         * Note: this method won't check if this move will make one's own king being checked.
         */
        Moves* GetAvailableMoves(Board* board);
        virtual void GetAvailableMoves(Board* board, Moves* moves) = 0;
        
        int GetX();
        int GetY();
        virtual ChessType GetChessType() = 0;

        static bool ConvertCharToField(char ch, ChessType* type, Color* side);
        
    };
}

#endif /* defined(__pp9k__Chess__) */

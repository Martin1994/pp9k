//
//  Board.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Board__
#define __pp9k__Board__

#include "Chess.h"
#include "Move.h"
#include "View.h"
#include "Player.h"

namespace pp9k
{
    const int BoardSize = 8;
    
    class Player;
    class Chess;
    class Move;
    class Moves;
    
    class Board
    {
    private:
        Chess* Chesses[BoardSize * BoardSize];
        Chess* LastMovedChess;
        bool Confirmed;
        Color Turn;
        void AddStandardPiece(int x, int y, ChessType type, Player* player);
        void RemoveInvalidMoves(Moves** moves);
        
    public:
        static Board* CreateStandardBoard(Player* player1, Player* player2);
        
        Board();
        ~Board();
        Board* ReplacePlayers(Player* player1, Player* player2);
        Moves* GetAllAvailableMoves(Color side);
        Moves* GetAvailableMoves(int x, int y);
        Board* ApplyMove(Move* move);
        void SetTurn(Color side);
        Color GetTurn();
        void SetChess(Chess* chess);
        void UnsetChess(int x, int y);
        Chess* GetChess(int x, int y);
        Chess* GetLastMovedChess();
        void Confirm();
        bool IsValid();
        bool IsCheck(Color side);
        bool IsCheckmate(Color side);
        bool HasMove(Color side);
    };
}

#endif /* defined(__pp9k__Board__) */

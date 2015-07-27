//
//  ChessKnight.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessKnight.h"

using namespace pp9k;

ChessKnight::ChessKnight(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    
}

void ChessKnight::GetAvailableMoves(Board* board, Moves* moves)
{
    this->AddMove(board, moves,  1,  2);
    this->AddMove(board, moves, -1,  2);
    this->AddMove(board, moves,  1, -2);
    this->AddMove(board, moves, -1, -2);
    this->AddMove(board, moves,  2,  1);
    this->AddMove(board, moves, -2,  1);
    this->AddMove(board, moves,  2, -1);
    this->AddMove(board, moves, -2, -1);
}

ChessType ChessKnight::GetChessType()
{
    return Knight;
}

void ChessKnight::AddMove(Board* board, Moves* moves, int relative_x, int relative_y)
{
    int new_x = this->GetX() + relative_x;
    int new_y = this->GetY() + relative_y;
    Chess* before;
    Chess* after;
    Chess* captured;
    Move* move;
    
    // Out of board?
    if (new_x < 0 || new_x >= pp9k::BoardSize || new_y < 0 || new_y >= pp9k::BoardSize)
    {
        return;
    }
    
    // Create new move
    after = new ChessKnight(this->GetPlayer(), new_x, new_y);
    captured = board->GetChess(new_x, new_y);
    
    if (captured != NULL)
    {
        if (captured->GetPlayer() == this->GetPlayer())
        {
            return;
        }
        captured = captured->Clone();
    }
    
    before = this->Clone();
    
    move = new Move(before, after, captured);
    moves->AddMove(move);
}

Chess* ChessKnight::Clone()
{
    return new ChessKnight(this->GetPlayer(), this->GetX(), this->GetY());
}

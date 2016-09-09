//
//  ChessBishop.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessBishop.h"

using namespace pp9k;

ChessBishop::ChessBishop(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    
}

void ChessBishop::GetAvailableMoves(Board* board, Moves* moves, bool only_capture)
{
    
    this->AddMove(board, moves,  1,  1, only_capture);
    this->AddMove(board, moves, -1,  1, only_capture);
    this->AddMove(board, moves,  1, -1, only_capture);
    this->AddMove(board, moves, -1, -1, only_capture);
}

void ChessBishop::AddMove(Board* board, Moves* moves, int direction_x, int direction_y, bool only_capture)
{
    int new_x;
    int new_y;
    Chess* before;
    Chess* after;
    Chess* captured;
    
    // Forward
    new_x = this->GetX();
    new_y = this->GetY();
    while
        (
         new_x += direction_x, new_y += direction_y,
         captured = board->GetChess(new_x, new_y),
         new_x >= 0 && new_x < pp9k::BoardSize &&
         new_y >= 0 && new_y < pp9k::BoardSize &&
         captured == NULL
         )
    {
        if (!only_capture)
        {
            before = this->Clone();
            after = new ChessBishop(this->GetPlayer(), new_x, new_y);
            moves->AddMove(new Move(before, after));
        }
    }
    if (new_x >= 0 && new_x < pp9k::BoardSize &&
        new_y >= 0 && new_y < pp9k::BoardSize &&
        captured != NULL && captured->GetPlayer() != this->GetPlayer())
    {
        before = this->Clone();
        after = new ChessBishop(this->GetPlayer(), new_x, new_y);
        captured = captured->Clone();
        moves->AddMove(new Move(before, after, captured));
    }
}

ChessType ChessBishop::GetChessType()
{
    return Bishop;
}

Chess* ChessBishop::Clone()
{
    return new ChessBishop(this->GetPlayer(), this->GetX(), this->GetY());
}

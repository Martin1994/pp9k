//
//  ChessQueen.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessQueen.h"

using namespace pp9k;

ChessQueen::ChessQueen(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    
}

void ChessQueen::GetAvailableMoves(Board* board, Moves* moves, bool only_capture)
{
    this->AddMove(board, moves,  1,  0, only_capture);
    this->AddMove(board, moves,  0,  1, only_capture);
    this->AddMove(board, moves, -1,  0, only_capture);
    this->AddMove(board, moves,  0, -1, only_capture);
    this->AddMove(board, moves,  1,  1, only_capture);
    this->AddMove(board, moves, -1,  1, only_capture);
    this->AddMove(board, moves,  1, -1, only_capture);
    this->AddMove(board, moves, -1, -1, only_capture);
}

void ChessQueen::AddMove(Board* board, Moves* moves, int direction_x, int direction_y, bool only_capture)
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
            after = new ChessQueen(this->GetPlayer(), new_x, new_y);
            moves->AddMove(new Move(before, after));
        }
    }
    if (new_x >= 0 && new_x < pp9k::BoardSize &&
        new_y >= 0 && new_y < pp9k::BoardSize &&
        captured != NULL && captured->GetPlayer() != this->GetPlayer())
    {
        before = this->Clone();
        after = new ChessQueen(this->GetPlayer(), new_x, new_y);
        captured = captured->Clone();
        moves->AddMove(new Move(before, after, captured));
    }
}

ChessType ChessQueen::GetChessType()
{
    return Queen;
}

Chess* ChessQueen::Clone()
{
    return new ChessQueen(this->GetPlayer(), this->GetX(), this->GetY());
}

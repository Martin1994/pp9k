//
//  ChessRook.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessRook.h"

using namespace pp9k;

ChessRook::ChessRook(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    if (player->GetSide() == White)
    {
        this->Moved = y != 0 && x != 0 && x != pp9k::BoardSize - 1;
    }
    else
    {
        this->Moved = y != pp9k::BoardSize - 1 && x != 0 && x != pp9k::BoardSize - 1;
    }
}

ChessRook::ChessRook(pp9k::Player* player, int x, int y, bool moved) : Chess(player, x, y)
{
    this->Moved = moved;
}

void ChessRook::GetAvailableMoves(Board* board, Moves* moves)
{
    this->AddMove(board, moves,  1,  0);
    this->AddMove(board, moves,  0,  1);
    this->AddMove(board, moves, -1,  0);
    this->AddMove(board, moves,  0, -1);
}

void ChessRook::AddMove(Board* board, Moves* moves, int direction_x, int direction_y)
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
        before = this->Clone();
        after = new ChessRook(this->GetPlayer(), new_x, new_y, true);
        moves->AddMove(new Move(before, after));
    }
    if (new_x >= 0 && new_x < pp9k::BoardSize &&
        new_y >= 0 && new_y < pp9k::BoardSize &&
        captured != NULL && captured->GetPlayer() != this->GetPlayer())
    {
        before = this->Clone();
        after = new ChessRook(this->GetPlayer(), new_x, new_y, true);
        captured = captured->Clone();
        moves->AddMove(new Move(before, after, captured));
    }
}

ChessType ChessRook::GetChessType()
{
    return Rook;
}

Chess* ChessRook::Clone()
{
    return new ChessRook(this->GetPlayer(), this->GetX(), this->GetY(), this->Moved);
}

bool ChessRook::HasMoved()
{
    return this->Moved;
}

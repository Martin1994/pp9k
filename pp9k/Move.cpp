//
//  Move.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Move.h"

using namespace pp9k;

Move::Move(Chess* before, Chess* after, Chess* captured, Move* submove)
{
    this->ChessBeforeMove = before;
    this->ChessAfterMove = after;
    this->ChessCaptured = captured;
    this->SubMove = submove;
}

Move::~Move()
{
    delete this->ChessBeforeMove;
    delete this->ChessAfterMove;
    delete this->ChessCaptured;
    delete this->SubMove;
}

Move* Move::Clone()
{
    return new Move(this->ChessBeforeMove->Clone(),
                    this->ChessAfterMove->Clone(),
                    this->ChessCaptured == NULL ? NULL : this->ChessCaptured->Clone(),
                    this->SubMove == NULL ? NULL : this->SubMove->Clone());
}

Chess* Move::GetChessBeforeMove()
{
    return this->ChessBeforeMove;
}

Chess* Move::GetChessAfterMove()
{
    return this->ChessAfterMove;
}

Chess* Move::GetChessCaptured()
{
    return this->ChessCaptured;
}

Move* Move::GetSubMove()
{
    return this->SubMove;
}

Moves::Moves()
{
    this->Capacity = 1;
    this->Length = 0;
    this->MoveList = new Move*[this->Capacity];
    this->Confirmed = false;
}

Moves::~Moves()
{
    for (int i = 0; i < this->Length; i++)
    {
        delete this->MoveList[i];
    }
    delete[] this->MoveList;
}

void Moves::AddMove(Move* move)
{
    if (this->Confirmed)
    {
        return;
    }
    
    if (this->Length == this->Capacity)
    {
        this->Capacity *= 2;
        Move** old_list = this->MoveList;
        this->MoveList = new Move*[this->Capacity];
        for (int i = 0; i < this->Length; i++)
        {
            this->MoveList[i] = old_list[i];
        }
        delete[] old_list;
    }
    this->MoveList[this->Length] = move;
    this->Length += 1;
}

void Moves::Confirm()
{
    this->Confirmed = true;
}

Move* Moves::GetMove(int cursor)
{
    if (cursor < 0 || cursor >= this->Length)
    {
        return NULL;
    }
    
    return this->MoveList[cursor];
}

int Moves::GetLength()
{
    return this->Length;
}

//
//  BoardHistory.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "BoardHistory.h"

using namespace pp9k;

BoardHistory::BoardHistory()
{
    this->Capacity = 1;
    this->Length = 0;
    this->Boards = new Board*[this->Capacity];
}

BoardHistory::~BoardHistory()
{
    for (int i = 0; i < this->Length; i++)
    {
        delete this->Boards[i];
    }
    delete this->Boards;
}

void BoardHistory::PushBoard(Board* board)
{
    if (this->Length == Capacity)
    {
        Board** old_heap = this->Boards;
        this->Capacity *= 2;
        this->Boards = new Board*[this->Capacity];
        for (int i = 0; i < this->Length; i++)
        {
            this->Boards[i] = old_heap[i];
        }
        delete[] old_heap;
    }
    
    this->Boards[this->Length] = board;
    this->Length += 1;
}

Board* BoardHistory::PopBoard()
{
    this->Length --;
    Board* board = this->Boards[this->Length];
    this->Boards[this->Length] = NULL;
    return board;
}

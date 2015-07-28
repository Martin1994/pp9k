//
//  PlayerAI4.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include "PlayerAI4.h"
#include "Move.h"
#include "Board.h"

using namespace pp9k;

PlayerAI4::PlayerAI4(pp9k::Game* game, pp9k::Color side) : PlayerAI(game, side)
{

}

int PlayerAI4::TypeToRank(ChessType type)
{
    switch (type)
    {
    case King:
        return 10;

    case Queen:
        return 8;

    case Rook:
        return 6;

    case Bishop:
        return 4;

    case Knight:
        return 2;

    case Pawn:
        return 0;
    }
}

void PlayerAI4::RequestMove()
{
    Moves* moves = this->Game->CurrentBoard->GetAllAvailableMoves(this->Side);

    // Prefer avoid capture
    Moves* prefered_moves = new Moves();

    Color opponent = this->GetSide() == White ? Black : White;

    int bottom_rank = 12;
    for (int i = 0; i < moves->GetLength(); i++)
    {
        Board* board = this->Game->CurrentBoard->ApplyMove(moves->GetMove(i));

        Moves* oppo_moves = board->GetAllAvailableMoves(opponent);

        int capture = -1;
        for (int j = 0; j < oppo_moves->GetLength(); j++)
        {
            if (oppo_moves->GetMove(j)->GetChessCaptured() != NULL)
            {
                int rank = TypeToRank(oppo_moves->GetMove(j)->GetChessCaptured()->GetChessType());
                capture = capture > rank ? capture : rank;
            }
        }

        if (capture < bottom_rank)
        {
            bottom_rank = capture;
            delete prefered_moves;
            prefered_moves = new Moves();
        }

        if (capture == bottom_rank)
        {
            prefered_moves->AddMove(moves->GetMove(i)->Clone());
        }

        delete oppo_moves;

        delete board;
    }

    prefered_moves->Confirm();

    if (prefered_moves->GetLength() > 0)
    {
        delete moves;
        moves = prefered_moves;
    }
    else
    {
        delete prefered_moves;
    }

    // Prefer capture
    prefered_moves = new Moves();

    int top_rank = -1;
    for (int i = 0; i < moves->GetLength(); i++)
    {
        if (moves->GetMove(i)->GetChessCaptured() != NULL)
        {
            int capture = TypeToRank(moves->GetMove(i)->GetChessCaptured()->GetChessType());

            if (capture > top_rank)
            {
                top_rank = capture;
                delete prefered_moves;
                prefered_moves = new Moves();
            }

            if (capture == top_rank)
            {
                prefered_moves->AddMove(moves->GetMove(i)->Clone());
            }
        }
    }

    prefered_moves->Confirm();

    if (prefered_moves->GetLength() > 0)
    {
        delete moves;
        moves = prefered_moves;
    }
    else
    {
        delete prefered_moves;
    }

    // Random select one move
    srand(time(NULL));
    int index = rand() % moves->GetLength();

    Move* move = moves->GetMove(index);
    Chess* before = move->GetChessBeforeMove();
    Chess* after = move->GetChessAfterMove();

    this->Game->MakeMove(before->GetX(), before->GetY(), after->GetX(), after->GetY(), after->GetChessType());

    delete moves;

    CheckDraw();
}

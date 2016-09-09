//
//  PlayerAI3.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include "PlayerAI3.h"
#include "Move.h"
#include "Board.h"

using namespace pp9k;

PlayerAI3::PlayerAI3(pp9k::Game* game, pp9k::Color side) : PlayerAI(game, side)
{

}

void PlayerAI3::RequestMove()
{
    Moves* moves = this->Game->CurrentBoard->GetAllAvailableMoves(this->Side);

    Moves* prefered_moves = new Moves();

    Color opponent = this->GetSide() == White ? Black : White;

    for (int i = 0; i < moves->GetLength(); i++)
    {
        Board* board = this->Game->CurrentBoard->ApplyMove(moves->GetMove(i));

        Moves* oppo_moves = board->GetAllAvailableMoves(opponent);

        bool capture = false;
        for (int j = 0; j < oppo_moves->GetLength(); j++)
        {
            if (oppo_moves->GetMove(j)->GetChessCaptured() != NULL)
            {
                capture = true;
                break;
            }
        }

        if (!capture)
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

    srand(time(NULL));
    int index = rand() % moves->GetLength();

    Move* move = moves->GetMove(index);
    Chess* before = move->GetChessBeforeMove();
    Chess* after = move->GetChessAfterMove();

    this->Game->MakeMove(before->GetX(), before->GetY(), after->GetX(), after->GetY(), after->GetChessType());

    delete moves;

    CheckDraw();
}

//
//  PlayerAI2.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include "PlayerAI2.h"
#include "Move.h"

using namespace pp9k;

PlayerAI2::PlayerAI2(pp9k::Game* game, pp9k::Color side) : PlayerAI(game, side)
{

}

void PlayerAI2::RequestMove()
{
    Moves* moves = this->Game->CurrentBoard->GetAllAvailableMoves(this->Side);

    Moves* prefered_moves = new Moves();

    for (int i = 0; i < moves->GetLength(); i++)
    {
        if (moves->GetMove(i)->GetChessCaptured() != NULL)
        {
            prefered_moves->AddMove(moves->GetMove(i)->Clone());
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

    srand(time(NULL));
    int index = rand() % moves->GetLength();

    Move* move = moves->GetMove(index);
    Chess* before = move->GetChessBeforeMove();
    Chess* after = move->GetChessAfterMove();

    this->Game->MakeMove(before->GetX(), before->GetY(), after->GetX(), after->GetY(), after->GetChessType());

    delete moves;

    CheckDraw();
}

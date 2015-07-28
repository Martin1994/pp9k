//
//  PlayerAI.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "PlayerAI.h"

using namespace pp9k;

PlayerAI::PlayerAI(pp9k::Game* game, pp9k::Color side) : Player(game, side)
{
    
}

void PlayerAI::CheckDraw()
{
    if (this->Game->GetStatus() != Start)
        return;

    int num = 0;
    int self_num = 0;
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            Chess* piece = this->Game->CurrentBoard->GetChess(i, j);
            if (piece != NULL)
            {
                num += 1;
                if (piece->GetPlayer() == this)
                {
                    self_num += 1;
                }
            }
        }
    }

    if (num == 2 || self_num == 2 && num == 3)
    {
        this->Game->Stalemate();
    }
}

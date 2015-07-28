//
//  PlayerAI1.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include "PlayerAI1.h"
#include "Move.h"

using namespace pp9k;

PlayerAI1::PlayerAI1(pp9k::Game* game, pp9k::Color side) : PlayerAI(game, side)
{

}

void PlayerAI1::RequestMove()
{
	Moves* moves = this->Game->CurrentBoard->GetAllAvailableMoves(this->Side);

	srand (time(NULL));
	int index = rand() % moves->GetLength();

	Move* move = moves->GetMove(index);
	Chess* before = move->GetChessBeforeMove();
	Chess* after = move->GetChessAfterMove();

	this->Game->MakeMove(before->GetX(), before->GetY(), after->GetX(), after->GetY(), after->GetChessType());

	delete moves;
}

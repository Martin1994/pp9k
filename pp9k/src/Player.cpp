//
//  Player.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Player.h"

using namespace pp9k;

Player::Player(pp9k::Game* game, Color side)
{
    this->Game = game;
    this->Side = side;
}

Player::~Player()
{
    
}

Color Player::GetSide()
{
    return this->Side;
}

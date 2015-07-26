//
//  Player.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Player__
#define __pp9k__Player__

#include "Game.h"
#include "Enumerations.h"

namespace pp9k
{
    class Game;
    
    class Player
    {
    protected:
        Game* Game;
        Color Side;
        
    public:
        Player(pp9k::Game* game, Color side);
        virtual ~Player();
        virtual void RequestMove() = 0;
        Color GetSide();
    };
}

#endif /* defined(__pp9k__Player__) */

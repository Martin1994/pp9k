//
//  PlayerHuman.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__PlayerHuman__
#define __pp9k__PlayerHuman__

#include "Player.h"

namespace pp9k
{
    class PlayerHuman : public Player
    {
    public:
        PlayerHuman(pp9k::Game* game, pp9k::Color side);
        ~PlayerHuman();
        void RequestMove();
    };
}

#endif /* defined(__pp9k__PlayerHuman__) */

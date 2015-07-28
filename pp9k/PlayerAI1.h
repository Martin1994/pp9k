//
//  PlayerAI1.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__PlayerAI1__
#define __pp9k__PlayerAI1__

#include "PlayerAI.h"

namespace pp9k
{
    class PlayerAI1 : public PlayerAI
    {
    public:
        PlayerAI1(pp9k::Game* game, pp9k::Color side);
        void RequestMove();
    };
}

#endif /* defined(__pp9k__PlayerAI1__) */

//
//  PlayerAI.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__PlayerAI__
#define __pp9k__PlayerAI__

#include "Player.h"

namespace pp9k
{
    class PlayerAI : public Player
    {
    public:
		PlayerAI(pp9k::Game* game, pp9k::Color side);
    };
}

#endif /* defined(__pp9k__PlayerAI__) */

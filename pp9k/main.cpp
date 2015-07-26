//
//  main.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Game.h"
#include "ViewCLI.h"
#include "Controller.h"

int main(int argc, const char * argv[])
{
    pp9k::Game* game = new pp9k::Game();
    pp9k::Controller* controller = new pp9k::Controller();
    pp9k::View* view = new pp9k::ViewCLI();
    
    game->SetView(view);
    view->SetController(controller);
    controller->SetGame(game);
    
    view->GetCommand();
    
    return 0;
}

//
//  main.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#if defined(_MSC_VER)
    #if defined(_DEBUG)
        #include <stdlib.h>
        #include <crtdbg.h>
        
        #ifndef DBG_NEW
            #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
            #define new DBG_NEW
        #endif
        
    #endif
#endif

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

	delete game;
	delete view;
	delete controller;

	#if defined(_MSC_VER)
	    #if defined(_DEBUG)
	        _CrtDumpMemoryLeaks();
	    #endif
	#endif

    return 0;
}

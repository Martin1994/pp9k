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

#include <string>
#include <fstream>

#include "Game.h"
#include "Controller.h"

#include "ViewCLI.h"
#if !defined(_MSC_VER)
#include "ViewGUI.h"
#endif

int main(int argc, const char * argv[])
{
    bool graphics = true;
    bool board_print = true;
    std::ifstream* is = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == '-')
        {
            std::string cmd(argv[i] + 2);
            if (cmd == "nographics")
                graphics = false;
            else if (cmd == "nocliboard")
                board_print = false;
        }
        else
        {
            is = new std::ifstream(argv[i]);
            if (!is->is_open())
            {
                delete is;
                is = NULL;
            }
        }
    }

    pp9k::Game* game = new pp9k::Game();
    pp9k::Controller* controller = new pp9k::Controller();
    #if defined(_MSC_VER)
    pp9k::View* view = new pp9k::ViewCLI();
    #else
    pp9k::View* view = graphics ? new pp9k::ViewGUI(board_print) : new pp9k::ViewCLI();
    #endif
    
    game->SetView(view);
    view->SetController(controller);
    controller->SetGame(game);

    if (is != NULL)
    {
        controller->LoadBoard(is);
        delete is;
    }
    
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

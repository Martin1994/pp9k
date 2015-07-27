//
//  Controller.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Controller__
#define __pp9k__Controller__

#include <string>
#include "Game.h"
#include "View.h"
#include "Enumerations.h"

namespace pp9k
{
    class Game;
    
    class Controller
    {
    private:
        Game* Game;
        
    public:
        Controller();
        ~Controller();
        void SetGame(pp9k::Game* game);
        bool MakeMove(int original_x, int original_y, int target_x, int target_y);
        bool Undo();
        bool Resign();
        bool StartGame(std::string player1, std::string player2);
        bool Setup(int x, int y, ChessType type, Color side = White);
        bool InitializeComplete();
        bool InitializeGame();
        bool SetTurn(Color side);
		bool RefreshBoard();
        bool Exit();
        
    };
}

#endif /* defined(__pp9k__Controller__) */

//
//  View.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__View__
#define __pp9k__View__

#include "Controller.h"
#include "Enumerations.h"

namespace pp9k
{
    class Controller;
    
    class View
    {
    protected:
        class Controller* Controller;
        
    public:
        
        View();
        ~View();
        void SetController(pp9k::Controller* controller);
        virtual void ChangeBoard(int x, int y, ChessType type, Color side = White) = 0;
        virtual void FlushBoard() = 0;
        virtual void GetCommand() = 0;
        virtual void Win(Color side, bool checkmate) = 0;
        virtual void Draw() = 0;
        virtual void ShowScore(double score1, double score2) = 0;
        virtual void ChangeTurn(Color side) = 0;
        virtual void RequestMove(Color side) = 0;
    };
    
    
}

#endif /* defined(__pp9k__View__) */

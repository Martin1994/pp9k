//
//  ViewWrapper.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ViewWrapper__
#define __pp9k__ViewWrapper__


#include "View.h"

namespace pp9k
{
    class ViewWrapper : public View
    {
        
    public:
        typedef void (*ChangeBoardFunc)(int x, int y, int type, int side);
        ChangeBoardFunc ChangeBoardHandler;
        
        typedef void (*FlushBoardFunc)();
        FlushBoardFunc FlushBoardHandler;
        
        typedef void (*WinFunc)(int side, bool checkmate);
        WinFunc WinHandler;
        
        typedef void (*DrawFunc)();
        DrawFunc DrawHandler;
        
        typedef void (*ShowScoreFunc)(double score1, double score2);
        ShowScoreFunc ShowScoreHandler;

		typedef void(*ChangeTurnFunc)(int side);
		ChangeTurnFunc ChangeTurnHandler;
        
        ViewWrapper();
        ~ViewWrapper();
        
        void ChangeBoard(int x, int y, ChessType type, Color side);
        void FlushBoard();
        void GetCommand();
        void Win(Color side, bool checkmate);
        void Draw();
        void ShowScore(double score1, double score2);
		void ChangeTurn(Color side);
		void RequestMove(Color side);
        
    };
}

#endif /* defined(__pp9k__ViewWrapper__) */

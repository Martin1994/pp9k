//
//  ViewCLI.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ViewCLI__
#define __pp9k__ViewCLI__

#include "View.h"

namespace pp9k
{
    class ViewCLI : public View
    {
    private:
        char BoardContent[pp9k::BoardSize * pp9k::BoardSize];
        
    public:
        
        ViewCLI();
        ~ViewCLI();
        
        void ChangeBoard(int x, int y, ChessType type, Color side);
        void FlushBoard();
        void GetCommand();
        void Win(Color side, bool checkmate);
        void Draw();
        void ShowScore(double score1, double score2);
		void ChangeTurn(Color side);
        
    };
}

#endif /* defined(__pp9k__ViewCLI__) */

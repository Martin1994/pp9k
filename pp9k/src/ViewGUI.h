//
//  ViewGUI.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__ViewGUI__
#define __pp9k__ViewGUI__

#include "ViewCLI.h"
#include "window.h"

namespace pp9k
{
    class ViewGUI : public ViewCLI
    {
    protected:
		bool PrintBoard;
		Xwindow* Window;
        static const int GridWidth = 50;
        void FillGrid(int x, int y);
        void Message(std::string msg);
        
    public:

		ViewGUI(bool print_board);
        ~ViewGUI();
        
        void ChangeBoard(int x, int y, ChessType type, Color side);
        void FlushBoard();
        void Win(Color side, bool checkmate);
        void Draw();
        void ShowScore(double score1, double score2);
		void ChangeTurn(Color side);
        
    };
}

#endif /* defined(__pp9k__ViewGUI__) */

//
//  ViewGUI.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cctype>
#include "ViewGUI.h"
#include "Version.h"

using namespace pp9k;

ViewGUI::ViewGUI(bool print_board) : ViewCLI()
{
	this->PrintBoard = print_board;
	this->Window = new Xwindow();
}

ViewGUI::~ViewGUI()
{
	delete this->Window;
}

void ViewGUI::ChangeBoard(int x, int y, ChessType type, Color side)
{
	ViewCLI::ChangeBoard(x, y, type, side);


}

void ViewGUI::FlushBoard()
{
	if (this->PrintBoard)
		ViewCLI::FlushBoard();
}

void ViewGUI::Win(Color side, bool checkmate)
{
	if (this->PrintBoard)
		ViewCLI::Win(side, checkmate);


}

void ViewGUI::Draw()
{
	if (this->PrintBoard)
		ViewCLI::Draw();


}

void ViewGUI::ShowScore(double score1, double score2)
{
	ViewCLI::ShowScore(score1, score2);
}

void ViewGUI::ChangeTurn(Color side)
{
	ViewCLI::ChangeTurn(side);
}

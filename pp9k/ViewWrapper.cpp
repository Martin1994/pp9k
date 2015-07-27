//
//  ViewWrapper.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ViewWrapper.h"

using namespace pp9k;

ViewWrapper::ViewWrapper()
{
    this->ChangeBoardHandler = NULL;
    this->FlushBoardHandler = NULL;
    this->DrawHandler = NULL;
    this->WinHandler = NULL;
    this->ShowScoreHandler = NULL;
	this->ChangeTurnHandler = NULL;
}

ViewWrapper::~ViewWrapper()
{
    
}

void ViewWrapper::ChangeBoard(int x, int y, ChessType type, Color side)
{
    if (this->ChangeBoardHandler != NULL)
        ChangeBoardHandler(x, y, static_cast<int>(type), static_cast<int>(side));
}

void ViewWrapper::FlushBoard()
{
    if (this->FlushBoardHandler != NULL)
        FlushBoardHandler();
}

void ViewWrapper::GetCommand()
{

}

void ViewWrapper::Win(Color side, bool checkmate)
{
    if (this->WinHandler != NULL)
        WinHandler(static_cast<int>(side), checkmate);
}

void ViewWrapper::Draw()
{
    if (this->DrawHandler != NULL)
        DrawHandler();
}

void ViewWrapper::ShowScore(double score1, double score2)
{
    if (this->ShowScoreHandler != NULL)
        ShowScoreHandler(score1, score2);
}

void ViewWrapper::ChangeTurn(Color side)
{
	if (this->ChangeTurnHandler != NULL)
		ChangeTurnHandler(static_cast<int>(side));
}

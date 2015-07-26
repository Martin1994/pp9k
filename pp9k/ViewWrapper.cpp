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
}

ViewWrapper::~ViewWrapper()
{
    
}

void ViewWrapper::ChangeBoard(int x, int y, ChessType type, Color side)
{
    if (this->ChangeBoardHandler != NULL)
        ChangeBoardHandler(x, y, type, side);
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
        WinHandler(side, checkmate);
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

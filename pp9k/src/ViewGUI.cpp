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

using namespace pp9k;

ViewGUI::ViewGUI(bool print_board) : ViewCLI()
{
    this->PrintBoard = print_board;
    
    int board_size = pp9k::BoardSize * GridWidth;
    
    int width = 100 + board_size;
    int height = 200 + board_size;
    
    std::string title = "ChloroPawnPush9000";
    this->Window = new Xwindow(width, height, 0x333333, 0xCCCCCC, title.c_str());
    
    this->Window->fillRectangleRGB(45, 45, board_size + 10, board_size + 10, 0x555555);
    
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            this->FillGrid(i, j);
        }
    }
    
    std::string str;
    int color = 0x333333;
    char ch;
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        ch = (char)((int)'0' + 1);
        str = std::string(&ch, 1);
        this->Window->drawBigString(
            60 - GridWidth,
            35 + (pp9k::BoardSize - i) * GridWidth,
            str, color);
    }
    
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        ch = (char)(i + (int)'a');
        str = std::string(&ch, 1);
        this->Window->drawBigString(
            60 + i * GridWidth,
            35 + (pp9k::BoardSize + 1) * GridWidth,
            str, color);
    }
    
    this->Window->drawString(width / 2 - 25, height - 80, "Next", 0x333333);
    this->Window->fillRectangleRGB(width / 2 - 30, height - 75, GridWidth + 10, GridWidth + 10, 0x555555);
    this->ChangeTurn(White);
}

ViewGUI::~ViewGUI()
{
    delete this->Window;
}

void ViewGUI::FillGrid(int x, int y)
{
    int color = (x & 1) == (y & 1) ? 0x333333 : 0xCCCCCC;
    this->Window->fillRectangleRGB(
        50 + x * GridWidth,
        50 + (pp9k::BoardSize - y - 1) * GridWidth,
        GridWidth, GridWidth, color);
}

void ViewGUI::Message(std::string msg)
{
    this->Window->fillRectangleRGB(50, pp9k::BoardSize / 2 * GridWidth - 50,
        pp9k::BoardSize * GridWidth, 100, 0x333333);
    this->Window->drawBigString(50, pp9k::BoardSize / 2 * GridWidth + 20,
        msg, 0xCCCCCC);
}

void ViewGUI::ChangeBoard(int x, int y, ChessType type, Color side)
{
    ViewCLI::ChangeBoard(x, y, type, side);
    
    FillGrid(x, y);
    
    int color = side == White ? 0xCCCCCC : 0x333333;
    int color_stroke = side == Black ? 0xCCCCCC : 0x333333;
    std::string type_str;
    switch (type)
    {
        case King:
            type_str = "K";
            break;
            
        case Queen:
            type_str = "Q";
            break;
            
        case Bishop:
            type_str = "B";
            break;
            
        case Rook:
            type_str = "R";
            break;
            
        case Knight:
            type_str = "K";
            break;
            
        case Pawn:
            type_str = "P";
            break;
            
        case Blank:
        default:
            return;
            
    }
    
    this->Window->drawBigString(
        61 + x * GridWidth,
        36 + (pp9k::BoardSize - y) * GridWidth,
        type_str, color_stroke);
    this->Window->drawBigString(
        61 + x * GridWidth,
        34 + (pp9k::BoardSize - y) * GridWidth,
        type_str, color_stroke);
    this->Window->drawBigString(
        59 + x * GridWidth,
        36 + (pp9k::BoardSize - y) * GridWidth,
        type_str, color_stroke);
    this->Window->drawBigString(
        59 + x * GridWidth,
        34 + (pp9k::BoardSize - y) * GridWidth,
        type_str, color_stroke);
    this->Window->drawBigString(
        60 + x * GridWidth,
        35 + (pp9k::BoardSize - y) * GridWidth,
        type_str, color);
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

    Message((checkmate ? std::string("Checkmate - ") : std::string("")) + (side == White ? "White" : "Black") + (checkmate ? std::string("") : std::string(" wins!")));
}

void ViewGUI::Draw()
{
    if (this->PrintBoard)
        ViewCLI::Draw();

    Message("Stalemate!");
}

void ViewGUI::ShowScore(double score1, double score2)
{
    ViewCLI::ShowScore(score1, score2);
}

void ViewGUI::ChangeTurn(Color side)
{
    ViewCLI::ChangeTurn(side);
    
    int board_size = pp9k::BoardSize * GridWidth;
    
    int width = 100 + board_size;
    int height = 200 + board_size;
    
    this->Window->fillRectangleRGB(width / 2 - 25, height - 70, GridWidth, GridWidth, side == White ? 0xCCCCCC : 0x333333);
}

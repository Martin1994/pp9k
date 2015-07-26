//
//  ViewCLI.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "ViewCLI.h"
#include "Version.h"

using namespace pp9k;

ViewCLI::ViewCLI()
{
    for (int i = 0; i < pp9k::BoardSize * pp9k::BoardSize; i++)
    {
        this->BoardContent[i] = 0;
    }
    
    // Welcome message
    std::cout << "Welcome to ChloroPawnPusher9000 v"
             << pp9k::Version[0] << '.' << pp9k::Version[1]
             << " (CLI mode) !" << std::endl
             << "To enable GUI, add \"--graphics\"." << std::endl
             << "To get command list, type \"help\"." << std::endl;
}

ViewCLI::~ViewCLI()
{
    
}

void ViewCLI::ChangeBoard(int x, int y, ChessType type, Color side)
{
    char content;
    
    switch (type)
    {
        case King:
            content = side == White ? 'K' : 'k';
            break;
            
        case Queen:
            content = side == White ? 'Q' : 'q';
            break;
            
        case Bishop:
            content = side == White ? 'B' : 'b';
            break;
            
        case Rook:
            content = side == White ? 'R' : 'r';
            break;
            
        case Knight:
            content = side == White ? 'N' : 'n';
            break;
            
        case Pawn:
            content = side == White ? 'P' : 'p';
            break;
            
        case Blank:
        default:
            content = 0;
            break;
    }
    
    this->BoardContent[x + y * pp9k::BoardSize] = content;
}

void ViewCLI::FlushBoard()
{
    char content;
    
    for (int j = pp9k::BoardSize - 1; j >= 0; j--)
    {
        std::cout << j + 1 << ' ';
        for (int i = 0; i < pp9k::BoardSize; i++)
        {
            content = this->BoardContent[i + j * pp9k::BoardSize];
            if (content == 0)
            {
                if ((i & 1) == (j & 1))
                {
                    // Draw black blank
                    std::cout << '_';
                }
                else
                {
                    // Draw white blank
                    std::cout << ' ';
                }
            }
            else
            {
                std::cout << content;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << ' ' << ' ';
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        std::cout << (char)('a' + (char)i);
    }
    std::cout << std::endl;
}

void ViewCLI::GetCommand()
{
    std::string cmd;
    
    while (true)
    {
        std::cin >> cmd;
        
        if (std::cin.fail())
        {
            if (std::cin.eof())
            {
                // Print score
                this->Controller->Exit();
                break;
            }
            // TODO: error
        }
        else if (cmd == "game")
        {
            std::string player1_arg;
            std::string player2_arg;
            
            std::cin >> player1_arg >> player2_arg;
            
            if (std::cin.fail())
            {
                std::cout << "Invalid input." << std::endl;
                continue;
            }
            
            bool succeed = this->Controller->StartGame(player1_arg, player2_arg);
            
            if (!succeed)
            {
                std::cout << "Failed to start game. Have you already started the game?" << std::endl;
            }
        }
        else if (cmd == "resign")
        {
            bool succeed = this->Controller->Resign();
            
            if (!succeed)
            {
                std::cout << "Failed to resign. Did you start the game?" << std::endl;
            }
        }
        else if (cmd == "undo")
        {
            bool succeed = this->Controller->Undo();
            
            if (!succeed)
            {
                std::cout << "Failed to undo. Did you start the game?" << std::endl;
            }
        }
        else if (cmd == "move")
        {
            
            std::cin >> cmd;
            int original_x = (int)cmd.at(0) - (int)'a';
            int original_y = (int)cmd.at(1) - (int)'1';
            
            std::cin >> cmd;
            int target_x = (int)cmd.at(0) - (int)'a';
            int target_y = (int)cmd.at(1) - (int)'1';
            
            bool succeed = this->Controller->MakeMove(original_x, original_y, target_x,target_y);
            
            if (!succeed)
            {
                std::cout << "Failed to move. Did you give a valid position? Did you start the game?" << std::endl;
            }
        }
        else if (cmd == "setup")
        {
            bool succeed = this->Controller->InitializeGame();
            
            if (!succeed)
            {
                std::cout << "Failed to setup. Have you ended the previous game?" << std::endl;
                continue;
            }
            
            std::cout << "You are now in setup mode." << std::endl;
            
            while (!std::cin.eof())
            {
                std::cin >> cmd;
                if (cmd == "done")
                {
                    succeed = this->Controller->InitializeComplete();
                    if (succeed)
                    {
                        std::cout << "You have left setup mode." << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid board. There must be exactly 1 white King and 1 black King, and they must not be checked." << std::endl;
                    }
                }
                else if (cmd == "+")
                {
                    std::cin >> cmd;
                    
                    ChessType type = Blank;
                    Color side = White;
                    
                    succeed = true;
                    switch (cmd.at(0))
                    {
                        case 'K':
                            type = King;
                            side = White;
                            break;
                            
                        case 'k':
                            type = King;
                            side = Black;
                            break;
                            
                        case 'Q':
                            type = Queen;
                            side = White;
                            break;
                            
                        case 'q':
                            type = Queen;
                            side = Black;
                            break;
                            
                        case 'B':
                            type = Bishop;
                            side = White;
                            break;
                            
                        case 'b':
                            type = Bishop;
                            side = Black;
                            break;
                            
                        case 'R':
                            type = Rook;
                            side = White;
                            break;
                            
                        case 'r':
                            type = Rook;
                            side = Black;
                            break;
                            
                        case 'N':
                            type = Knight;
                            side = White;
                            break;
                            
                        case 'n':
                            type = Knight;
                            side = Black;
                            break;
                            
                        case 'P':
                            type = Pawn;
                            side = White;
                            break;
                            
                        case 'p':
                            type = Pawn;
                            side = Black;
                            break;
                            
                        default:
                            std::cout << "Invalid piece type \"" << cmd.at(0) << std::endl;
                            succeed = false;
                            break;
                    }
                    
                    if (!succeed)
                    {
                        continue;
                    }
                    
                    std::cin >> cmd;
                    int x = (int)cmd.at(0) - (int)'a';
                    int y = (int)cmd.at(1) - (int)'1';
                    
                    succeed = this->Controller->Setup(x, y, type, side);
                    if (!succeed)
                    {
                        std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
                    }
                }
                else if (cmd == "-")
                {
                    std::cin >> cmd;
                    int x = (int)cmd.at(0) - (int)'a';
                    int y = (int)cmd.at(1) - (int)'1';
                    
                    succeed = this->Controller->Setup(x, y, Blank);
                    if (!succeed)
                    {
                        std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
                    }
                }
                else if (cmd == "=")
                {
                    std::cin >> cmd;
                    if (cmd == "White")
                    {
                        this->Controller->SetTurn(White);
                        std::cout << "Now it's white's turn." << std::endl;
                    }
                    else if (cmd == "Black")
                    {
                        this->Controller->SetTurn(Black);
                        std::cout << "Now it's black's turn." << std::endl;
                    }
                    else
                    {
                        std::cout << "Invalid player color \"" << cmd << "\"." << std::endl;
                    }
                }
            }
        }
        else if (cmd == "help")
        {
            // TODO
            std::cout << "Some help." << std::endl;
        }
        else
        {
            std::cout << "Unknown command \"" << cmd << "\"." << std::endl;
        }
    }
}

void ViewCLI::Win(Color side, bool checkmate)
{
    if (checkmate)
        std::cout << "Checkmate! ";
    
    if (side == White)
    {
        std::cout << "White";
    }
    else
    {
        std::cout << "Black";
    }
    
    std::cout << " wins!" << std::endl;
}

void ViewCLI::Draw()
{
    std::cout << "Stalemate!" << std::endl;
}

void ViewCLI::ShowScore(double score1, double score2)
{
    std::cout << "Score:" << std::endl;
    std::cout << "White: " << score1 << std::endl;
    std::cout << "Black: " << score2 << std::endl;
}

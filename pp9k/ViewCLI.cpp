//
//  ViewCLI.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cctype>
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
    std::cout
        << "Welcome to ChloroPawnPusher9000 v"
        << pp9k::Version[0] << '.' << pp9k::Version[1]
        << " (CLI mode) !" << std::endl
        #ifndef _MSC_VER
        << "To disable GUI, add \"--nographics\"." << std::endl
        << "To disable CLI board, add \"--nocliboard\"." << std::endl
        #endif
        << "To get command list, type \"help\"." << std::endl
        << "To load a game board, add the file name as parameter." << std::endl;

    this->Turn = White;
    this->MoveRequested = false;
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
        if (this->MoveRequested)
        {
            this->MoveRequested = false;

            this->Controller->AIMove();

            continue;
        }

        std::cin >> cmd;
        
        if (std::cin.eof() || cmd == "exit")
        {
            // Print score
            this->Controller->Exit();
            break;
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
            if (cmd.length() < 2)
            {
                std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
            }
            int original_x = (int)cmd.at(0) - (int)'a';
            int original_y = (int)cmd.at(1) - (int)'1';
            
            std::cin >> cmd;
            if (cmd.length() < 2)
            {
                std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
            }
            int target_x = (int)cmd.at(0) - (int)'a';
            int target_y = (int)cmd.at(1) - (int)'1';

            ChessType prefer = Queen;
            if (cmd.length() > 2)
            {
                switch ((char)tolower(cmd.at(2)))
                {
                    case 'q':
                        prefer = Queen;
                        break;

                    case 'r':
                        prefer = Rook;
                        break;

                    case 'b':
                        prefer = Bishop;
                        break;

                    case 'n':
                        prefer = Knight;
                        break;
                }
            }
            
            bool succeed = this->Controller->MakeMove(original_x, original_y, target_x, target_y, prefer);
            
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

                    if (cmd.length() < 1)
                    {
                        std::cout << "Invalid piece type \"" << cmd << "\"." << std::endl;
                    }
                    
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
                    if (cmd.length() < 2)
                    {
                        std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
                    }
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
                    if (cmd.length() < 2)
                    {
                        std::cout << "Invalid position \"" << cmd << "\"." << std::endl;
                    }
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
            std::cout
                << "Color is either \"White\" or \"Black\"." << std::endl
                << "Player is one of \"human\" \"computer1\" \"computer2\" \"computer3\" \"computer4\"" << std::endl
                << "Position is a combination of two characters: a lowercase letter and a number. e.g. e3 represents the coordination (5, 3)." << std::endl
                << "Type is an upper case letter. K: King; Q: Queen; B: Bishop; R: Rook; N: Knight; P: Pawn" << std::endl
                << std::endl
                << "exit" << std::endl
                << "    Exit this program and show score board." << std::endl
                << std::endl
                << "game [Player] [Player]" << std::endl
                << "    Start game. First player is white." << std::endl
                << std::endl
                << "help" << std::endl
                << "    Print command help." << std::endl
                << std::endl
                << "move [Position] [Position]*" << std::endl
                << "    Move from the first position to the second position." << std::endl
                << "    To specify a promotion of a pawn, you can add a [Type] next to the second position. e.g. move e7 e8Q" << std::endl
                << "    If you don't specify a type, it will become a queen." << std::endl
                << std::endl
                << "resign" << std::endl
                << "    Resign the game." << std::endl
                << std::endl
                << "setup" << std::endl
                << "    Enter setup mode. Setup the game board before game started. You can use the following commands during this mode:" << std::endl
                << "    + [Type] [Position]" << std::endl
                << "        Add a piece" << std::endl
                << "    - [Position]" << std::endl
                << "        Remove a piece" << std::endl
                << "    = [Color]" << std::endl
                << "        Let [Color] be the first player to move." << std::endl
                << "    done" << std::endl
                << "        Exit setup mode." << std::endl
                << std::endl
                << "undo" << std::endl
                << "    Undo the previous step. (*NOT IMPLEMENTED*)" << std::endl;
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

void ViewCLI::ChangeTurn(Color side)
{

}

void ViewCLI::RequestMove(Color side)
{
    this->MoveRequested = true;
}

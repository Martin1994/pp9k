//
//  Controller.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include <string>
#include <sstream>

#include "Controller.h"
#include "ChessKing.h"
#include "ChessQueen.h"
#include "ChessBishop.h"
#include "ChessKnight.h"
#include "ChessRook.h"
#include "ChessPawn.h"
#include "PlayerHuman.h"
#include "PlayerAI1.h"
#include "PlayerAI2.h"
#include "PlayerAI3.h"
#include "PlayerAI4.h"

using namespace pp9k;

Controller::Controller()
{
    
}

Controller::~Controller()
{
    
}

void Controller::SetGame(pp9k::Game* game)
{
    this->Game = game;
}

bool Controller::MakeMove(int original_x, int original_y, int target_x, int target_y, ChessType prefer)
{
    return this->Game->MakeMove(original_x, original_y, target_x, target_y, prefer);
}

bool pp9k::Controller::AIMove()
{
    if (this->Game->GetStatus() == Start)
        this->Game->GetPlayer(this->Game->GetTurn())->RequestMove();

    return true;
}

bool Controller::Undo()
{
    return this->Game->Undo();
}

bool Controller::Resign()
{
    return this->Game->Resign();
}

bool Controller::InitializeGame()
{
    return this->Game->Initialize();
}

bool Controller::InitializeComplete()
{
    return this->Game->InitializeComplete();
}

bool Controller::Setup(int x, int y, ChessType type, Color side)
{
    Chess* piece;
    Player* player = this->Game->GetPlayer(side);
    
    switch (type)
    {
        case King:
            piece = new ChessKing(player, x, y);
            break;
            
        case Queen:
            piece = new ChessQueen(player, x, y);
            break;
            
        case Bishop:
            piece = new ChessBishop(player, x, y);
            break;
            
        case Rook:
            piece = new ChessRook(player, x, y);
            break;
            
        case Knight:
            piece = new ChessKnight(player, x, y);
            break;
            
        case Pawn:
            piece = new ChessPawn(player, x, y);
            break;
            
        case Blank:
        default:
            piece = NULL;
    }
    
    if (piece == NULL)
    {
        return this->Game->RemovePiece(x, y);
    }
    else
    {
        return this->Game->AddPiece(piece);
    }
}

bool Controller::StartGame(std::string player1, std::string player2)
{
    Player* player_ins1;
    Player* player_ins2;
    
    if (player1 == "human")
        player_ins1 = new PlayerHuman(this->Game, White);
    else if (player1 == "computer1")
        player_ins1 = new PlayerAI1(this->Game, White);
    else
        return false;

    if (player2 == "human")
        player_ins2 = new PlayerHuman(this->Game, Black);
    else if (player2 == "computer1")
        player_ins2 = new PlayerAI1(this->Game, Black);
    else
        return false;
    
    return this->Game->Start(player_ins1, player_ins2);
}

bool Controller::SetTurn(Color side)
{
    return this->Game->SetTurn(side);
}

bool Controller::RefreshBoard()
{
    return this->Game->RefreshBoard();
}

bool Controller::Exit()
{
    this->Game->Exit();
    return true;
}

void Controller::LoadBoard(std::istream* is)
{
    if (is == NULL || this->Game->CurrentBoard != NULL)
        return;

    this->InitializeGame();

    int x = 0;
    int y = pp9k::BoardSize - 1;
    while (!is->eof() && y >= 0)
    {
        x = 0;
        std::string line;
        std::getline(*is, line);
        std::stringstream ss(line);
        while (!ss.eof() && x < pp9k::BoardSize)
        {
            char ch;
            ss >> ch;
            ChessType type;
            Color side;
            if (ch == '_')
            {
                this->Setup(x, y, Blank, White);
            }
            else
            {
                Chess::ConvertCharToField(ch, &type, &side);
                this->Setup(x, y, type, side);
            }
            x += 1;
        }

        y -= 1;

        if (y < 0)
        {
            char first;
            (*is) >> first;
            if (!is->fail())
            {
                this->SetTurn(first == 'W' ? White : Black);
            }
        }
    }

    this->InitializeComplete();
}

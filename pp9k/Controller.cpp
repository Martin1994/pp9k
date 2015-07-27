//
//  Controller.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Controller.h"
#include "ChessKing.h"
#include "ChessQueen.h"
#include "ChessBishop.h"
#include "ChessKnight.h"
#include "ChessRook.h"
#include "ChessPawn.h"
#include "PlayerHuman.h"

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

bool Controller::MakeMove(int original_x, int original_y, int target_x, int target_y)
{
    return this->Game->MakeMove(original_x, original_y, target_x, target_y);
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
	
    // TODO
    player_ins1 = new PlayerHuman(this->Game, White);
    player_ins2 = new PlayerHuman(this->Game, Black);
	
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

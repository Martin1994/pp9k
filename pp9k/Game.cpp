//
//  Game.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Game.h"
#include "PlayerHuman.h"
#include "BoardHistory.h"

using namespace pp9k;

Game::Game()
{
    this->Status = End;
    this->CurrentBoard = NULL;
    this->Boards = NULL;
    this->Players[0] = new PlayerHuman(this, White);
    this->Players[1] = new PlayerHuman(this, White);
    this->Score[0] = 0;
    this->Score[1] = 0;
}

Game::~Game()
{
    
}

void Game::SetView(pp9k::View* view)
{
    this->View = view;
}

pp9k::View* Game::GetView()
{
    return this->View;
}

Player* Game::GetPlayer(pp9k::Color side)
{
    if (side == White)
    {
        return this->Players[0];
    }
    else
    {
        return this->Players[1];
    }
}

bool Game::SetTurn(Color side)
{
    if (this->Status != Setup)
    {
        return false;
    }
    
    this->CurrentBoard->SetTurn(side);
	this->View->ChangeTurn(this->GetTurn());
    
    return true;
}

Color Game::GetTurn()
{
	return this->CurrentBoard->GetTurn();
}

double Game::GetScore(Color side)
{
    return (double)(this->Score[side == White ? 0 : 1]) / 2.0;
}

bool Game::Start(Player* player1, Player* player2)
{
    if (this->Status != End)
    {
        // error to view
        return false;
    }
	
    if (this->CurrentBoard == NULL)
    {
        this->CurrentBoard = Board::CreateStandardBoard(player1, player2);
    }
    else
    {
        Board* new_board = this->CurrentBoard->ReplacePlayers(player1, player2);
        delete this->CurrentBoard;
        this->CurrentBoard = new_board;
    }
	
    // Update view
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            Chess* piece = this->CurrentBoard->GetChess(i, j);
            if (piece == NULL)
            {
                this->View->ChangeBoard(i, j, Blank);
            }
			else
			{
				this->View->ChangeBoard(i, j, piece->GetChessType(), piece->GetPlayer()->GetSide());
            }
        }
    }
    this->View->FlushBoard();
	this->View->ChangeTurn(this->GetTurn());
	
    delete this->Boards;
    this->Boards = new BoardHistory();
	
    delete this->Players[0];
    this->Players[0] = player1;
    delete this->Players[1];
    this->Players[1] = player2;
	
    this->Status = pp9k::Start;
    
    return true;
}

bool Game::Initialize()
{
    if (this->Status != End)
    {
        // error to view
        return false;
    }
    
    this->Status = Setup;
    
    delete this->CurrentBoard;
    
    this->CurrentBoard = new Board();
    
    // Clear board in view
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            this->View->ChangeBoard(i, j, Blank);
        }
    }
    this->View->FlushBoard();
	this->View->ChangeTurn(this->GetTurn());
    
    return true;
}

bool Game::InitializeComplete()
{
    if (this->Status != Setup)
    {
        // error to view
        return false;
    }
    
    if (!this->CurrentBoard->IsValid())
    {
        // error to view
        return false;
    }
    
    this->Status = End;
    
    this->CurrentBoard->Confirm();
    
    return true;
}

bool Game::AddPiece(Chess* piece)
{
    int x = piece->GetX();
    int y = piece->GetY();
    
    if (x < 0 || x >= pp9k::BoardSize || y < 0 || y >= pp9k::BoardSize)
    {
        // error on view
        return false;
    }
    
    this->CurrentBoard->SetChess(piece);
    
    this->View->ChangeBoard(x, y, piece->GetChessType(), piece->GetPlayer()->GetSide());
    this->View->FlushBoard();
    
    return true;
}

bool Game::RemovePiece(int x, int y)
{
    if (x < 0 || x >= pp9k::BoardSize || y < 0 || y >= pp9k::BoardSize)
    {
        // error on view
        return false;
    }
    
    this->CurrentBoard->UnsetChess(x, y);
    
    this->View->ChangeBoard(x, y, Blank);
    this->View->FlushBoard();
    
    return true;
}

bool Game::Resign()
{
    if (this->Status != pp9k::Start)
    {
        return false;
    }
    
    this->Win(this->CurrentBoard->GetTurn() == White ? Black : White, false);
    
    return true;
}

bool Game::RequestStalemate()
{
    if (this->Status != pp9k::Start)
    {
        return false;
    }
    
    // TODO double side agree
    
    this->Stalemate();
    
    return true;
}

void Game::Win(Color side, bool checkmate)
{
    this->Status = pp9k::End;
    
    this->View->Win(side, checkmate);
    
    this->Score[this->CurrentBoard->GetTurn() == White ? 0 : 1] += 2;
    
    this->Boards->PushBoard(this->CurrentBoard);
    this->CurrentBoard = NULL;
}

void Game::Stalemate()
{
    
    this->Status = pp9k::End;
    
    this->View->Draw();
    
    this->Boards->PushBoard(this->CurrentBoard);
    this->CurrentBoard = NULL;
    
    this->Score[0] += 1;
    this->Score[1] += 1;
}

bool Game::Undo()
{
    // TODO
    return false;
}

bool Game::MakeMove(int original_x, int original_y, int target_x, int target_y)
{
    // Check boundary
    if (   original_x < 0 || original_x >= pp9k::BoardSize
        || original_y < 0 || original_y >= pp9k::BoardSize
        || target_x < 0 || target_x >= pp9k::BoardSize
        || target_y < 0 || target_y >= pp9k::BoardSize)
    {
        // error on view
        return false;
    }
    
    // Check turn
    Chess* piece = this->CurrentBoard->GetChess(original_x, original_y);
    if (piece == NULL || piece->GetPlayer()->GetSide() != this->CurrentBoard->GetTurn())
    {
        return false;
    }
    
    // Check availablity
    Moves* moves = this->CurrentBoard->GetAvailableMoves(original_x, original_y);
    for (int i = 0; i < moves->GetLength(); i++)
    {
        Move* move = moves->GetMove(i);
        Chess* after = move->GetChessAfterMove();
        if (after->GetX() == target_x && after->GetY() == target_y)
        {
            // Make this move
            this->Boards->PushBoard(this->CurrentBoard);
            this->CurrentBoard = this->CurrentBoard->ApplyMove(move);
            
            // Update view
            while (move != NULL)
            {
                Chess* before = move->GetChessBeforeMove();
                Chess* after = move->GetChessAfterMove();
                Chess* captured = move->GetChessCaptured();
                
                if (captured != NULL)
                {
                    this->View->ChangeBoard(captured->GetX(), captured->GetY(), Blank);
                }
                
                this->View->ChangeBoard(before->GetX(), before->GetY(), Blank);
                this->View->ChangeBoard(after->GetX(), after->GetY(), after->GetChessType(), after->GetPlayer()->GetSide());
                
                move = move->GetSubMove();
            }
            this->View->FlushBoard();
			this->View->ChangeTurn(this->GetTurn());
            
            // Check if this game has ended
            Color opponent = this->CurrentBoard->GetTurn() == White ? Black : White;
            
            if (this->CurrentBoard->IsCheckmate(opponent))
            {
                // Checkmate
                this->Win(opponent, true);
            }
            else if(!this->CurrentBoard->HasMove(this->CurrentBoard->GetTurn()))
            {
                // No available moves
                this->Stalemate();
            }
            else
            {
                // Request move
                this->Players[this->CurrentBoard->GetTurn() == White ? 0 : 1]->RequestMove();
            }
            
            delete moves;
            
            return true;
        }
    }
    
    delete moves;
    
    return false;
}

bool Game::RefreshBoard()
{
	this->View->FlushBoard();
	this->View->ChangeTurn(this->GetTurn());
	return true;
}

bool Game::Exit()
{
    this->View->ShowScore(this->GetScore(White), this->GetScore(Black));
    return true;
}

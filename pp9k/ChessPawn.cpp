//
//  ChessPawn.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessPawn.h"
#include "ChessQueen.h"
#include "ChessBishop.h"
#include "ChessRook.h"
#include "ChessKnight.h"

using namespace pp9k;

ChessPawn::ChessPawn(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    if (player->GetSide() == White)
    {
        this->Moved = this->MovedTwice = y != 1;
    }
    else
    {
        this->Moved = this->MovedTwice = y != pp9k::BoardSize - 2;
    }
}

ChessPawn::ChessPawn(pp9k::Player* player, int x, int y, bool moved, bool moved_twice) : Chess(player, x, y)
{
    this->Moved = moved;
    this->MovedTwice = moved_twice;
}

void ChessPawn::GetAvailableMoves(Board* board, Moves* moves, bool only_capture)
{
    Move* move;
    Chess* after;
    int direction;
    
    // Get direction
    if (this->GetPlayer()->GetSide() == White)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }
    
    int new_x;
    int new_y;
    pp9k::Player* player = this->GetPlayer();
    
    new_y = this->GetY() + direction;
    new_x = this->GetX();
    
    if (!only_capture)
    {
        // Blocked?
        if (board->GetChess(new_x, new_y) == NULL)
        {
            if (new_y == pp9k::BoardSize - 1 || new_y == 0)
            {
                // Promotion
                after = new ChessQueen(player, new_x, new_y);
                move = new Move(this->Clone(), after);
                moves->AddMove(move);
                after = new ChessKnight(player, new_x, new_y);
                move = new Move(this->Clone(), after);
                moves->AddMove(move);
                after = new ChessRook(player, new_x, new_y, true);
                move = new Move(this->Clone(), after);
                moves->AddMove(move);
                after = new ChessBishop(player, new_x, new_y);
                move = new Move(this->Clone(), after);
                moves->AddMove(move);
            }
            else
            {
                // Move
                after = new ChessPawn(player, new_x, new_y, true, true);
                move = new Move(this->Clone(), after);
                moves->AddMove(move);

                // First move
                if (this->Moved == false && board->GetChess(new_x, new_y + direction) == NULL)
                {
                    after = new ChessPawn(player, new_x, new_y + direction, true, false);
                    move = new Move(this->Clone(), after);
                    moves->AddMove(move);
                }
            }
        }
    }
    
    // Capture
    for (new_x = this->GetX() - 1; new_x <= this->GetX() + 1; new_x += 2)
    {
        Chess* captured;
        if (new_x >= 0)
        {
            captured = board->GetChess(new_x, new_y);
            
            Chess* nearby = board->GetChess(new_x, this->GetY());
            // En passant
            if (   captured == NULL
                && nearby != NULL
                && nearby == board->GetLastMovedChess()
                && nearby->GetChessType() == Pawn
                && !((ChessPawn*) nearby)->MovedTwice)
            {
                captured = board->GetLastMovedChess();
            }
            
            if (captured != NULL && captured->GetPlayer() != this->GetPlayer())
            {
                if (new_y == pp9k::BoardSize - 1 || new_y == 0)
                {
                    // Promotion
                    after = new ChessQueen(player, new_x, new_y);
                    move = new Move(this->Clone(), after, captured->Clone());
                    moves->AddMove(move);
                    after = new ChessKnight(player, new_x, new_y);
                    move = new Move(this->Clone(), after, captured->Clone());
                    moves->AddMove(move);
                    after = new ChessRook(player, new_x, new_y, true);
                    move = new Move(this->Clone(), after, captured->Clone());
                    moves->AddMove(move);
                    after = new ChessBishop(player, new_x, new_y);
                    move = new Move(this->Clone(), after, captured->Clone());
                    moves->AddMove(move);
                }
                else
                {
                    // Move
                    after = new ChessPawn(player, new_x, new_y, true, true);
                    move = new Move(this->Clone(), after, captured->Clone());
                    moves->AddMove(move);
                }
            }
        }
    }
}

ChessType ChessPawn::GetChessType()
{
    return Pawn;
}

Chess* ChessPawn::Clone()
{
    return new ChessPawn(this->GetPlayer(), this->GetX(), this->GetY(), this->Moved, this->MovedTwice);
}

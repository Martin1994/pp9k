//
//  ChessKing.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "ChessKing.h"
#include "ChessRook.h"

using namespace pp9k;

ChessKing::ChessKing(pp9k::Player* player, int x, int y) : Chess(player, x, y)
{
    if (player->GetSide() == White)
    {
        this->Moved = y != 0 && x != 4;
    }
    else
    {
        this->Moved = y != pp9k::BoardSize - 1 && x != 4;
    }
}

ChessKing::ChessKing(pp9k::Player* player, int x, int y, bool moved) : Chess(player, x, y)
{
    this->Moved = moved;
}

void ChessKing::GetAvailableMoves(Board* board, Moves* moves)
{
    // Regular move and capture
    this->AddMove(board, moves,  1,  0);
    this->AddMove(board, moves, -1,  0);
    this->AddMove(board, moves,  0,  1);
    this->AddMove(board, moves,  0, -1);
    
    // Castling
    if (!this->Moved)
    {
        int x;
        int y = this->GetY();
        Chess* castle;
        
        // Kingside
        for (x = this->GetX() + 1; x < pp9k::BoardSize; x++)
        {
            castle = board->GetChess(x, y);
            if (   castle != NULL
                && castle->GetChessType() == Rook
                && castle->GetPlayer() == this->GetPlayer())
            {
                if (!((ChessRook*) castle)->HasMoved())
                {
                    Move* rook_move = new Move(castle->Clone(),
                                               new ChessRook(this->GetPlayer(),
                                                             this->GetX() + 1,
                                                             this->GetY(),
                                                             true));
                    
                    Move* king_move = new Move(this->Clone(),
                                               new ChessKing(this->GetPlayer(),
                                                             this->GetX() + 2,
                                                             this->GetY(),
                                                             true),
                                               NULL,
                                               rook_move);
                    
                    moves->AddMove(king_move);
                }
            }
            else if (castle != NULL)
            {
                break;
            }
        }
        
        // Queedside
        for (x = this->GetX() - 1; x >= 0; x--)
        {
            castle = board->GetChess(x, y);
            if (   castle != NULL
                && castle->GetChessType() == Rook
                && castle->GetPlayer() == this->GetPlayer())
            {
                if (!((ChessRook*) castle)->HasMoved())
                {
                    Move* rook_move = new Move(castle->Clone(),
                                               new ChessRook(this->GetPlayer(),
                                                             this->GetX() - 1,
                                                             this->GetY(),
                                                             true));
                    
                    Move* king_move = new Move(this->Clone(),
                                               new ChessKing(this->GetPlayer(),
                                                             this->GetX() - 2,
                                                             this->GetY(),
                                                             true),
                                               NULL,
                                               rook_move);
                    
                    moves->AddMove(king_move);
                }
            }
            else if (castle != NULL)
            {
                break;
            }
        }
    }
}

ChessType ChessKing::GetChessType()
{
    return King;
}

Chess* ChessKing::Clone()
{
    return new ChessKing(this->GetPlayer(), this->GetX(), this->GetY(), this->Moved);
}

void ChessKing::AddMove(Board* board, Moves* moves, int relative_x, int relative_y)
{
    int new_x = this->GetX() + relative_x;
    int new_y = this->GetY() + relative_y;
    
    if (new_x < 0 || new_x >= pp9k::BoardSize || new_y < 0 || new_y >= pp9k::BoardSize)
    {
        return;
    }
    
    Chess* before = this->Clone();
    Chess* after = new ChessKing(this->GetPlayer(), this->GetX(), this->GetY(), true);
    Chess* captured = board->GetChess(new_x, new_y);
    
    if (captured != NULL)
        captured = captured->Clone();
    
    moves->AddMove(new Move(before, after, captured));
}

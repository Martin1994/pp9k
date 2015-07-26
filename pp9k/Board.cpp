//
//  Board.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Board.h"
#include "ChessKing.h"
#include "ChessQueen.h"
#include "ChessBishop.h"
#include "ChessRook.h"
#include "ChessKnight.h"
#include "ChessPawn.h"

using namespace pp9k;

Board::Board()
{
    this->Confirmed = false;
    
    this->LastMovedChess = NULL;
    
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            this->Chesses[i + j * pp9k::BoardSize] = NULL;
        }
    }
    
    this->Turn = White;
}

Board::~Board()
{
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            delete this->Chesses[i + j * pp9k::BoardSize];
        }
    }
}

void Board::SetTurn(Color side)
{
    this->Turn = side;
}

Color Board::GetTurn()
{
    return this->Turn;
}

Moves* Board::GetAllAvailableMoves(Color side)
{
    Moves* moves = new Moves();
    
    for (int i = 0; i < BoardSize * BoardSize; i++)
    {
        if (this->Chesses[i] != NULL && this->Chesses[i]->GetPlayer()->GetSide() == side)
            this->Chesses[i]->GetAvailableMoves(this, moves);
    }
    
    if (side == this->Turn)
        this->RemoveInvalidMoves(&moves);
    
    return moves;
}

Moves* Board::GetAvailableMoves(int x, int y)
{
    Moves* moves = this->GetChess(x, y)->GetAvailableMoves(this);
    
    this->RemoveInvalidMoves(&moves);
    
    return moves;
}

void Board::RemoveInvalidMoves(Moves** moves)
{
    Moves* available_moves = new Moves();
    Color opponent = this->Turn == White ? Black : White;
    
    for (int i = 0; i < (*moves)->GetLength(); i++)
    {
        Board* board = this->ApplyMove((*moves)->GetMove(i));
        
        if (!board->IsCheck(opponent))
        {
            available_moves->AddMove((*moves)->GetMove(i)->Clone());
        }
        
        delete board;
    }
    
    available_moves->Confirm();
    
    delete *moves;
    
    *moves = available_moves;
}

Board* Board::ApplyMove(Move* move)
{
    Board* new_board = new Board();
    
    for (int i = 0; i < BoardSize * BoardSize; i++)
    {
        if (this->Chesses[i] != NULL)
            new_board->Chesses[i] = this->Chesses[i]->Clone();
        else
            new_board->Chesses[i] = NULL;
    }
    
    while (move != NULL)
    {
        Chess* before = move->GetChessBeforeMove();
        Chess* after = move->GetChessAfterMove();
        Chess* captured = move->GetChessCaptured();
        
        if (captured != NULL)
        {
            delete new_board->Chesses[captured->GetX() + captured->GetY() * pp9k::BoardSize];
            new_board->Chesses[captured->GetX() + captured->GetY() * pp9k::BoardSize] = NULL;
        }
        
        delete new_board->Chesses[before->GetX() + before->GetY() * pp9k::BoardSize];
        new_board->Chesses[before->GetX() + before->GetY() * pp9k::BoardSize] = NULL;
        
        new_board->Chesses[after->GetX() + after->GetY() * pp9k::BoardSize] = after->Clone();
        new_board->LastMovedChess = new_board->Chesses[after->GetX() + after->GetY() * pp9k::BoardSize];
        
        move = move->GetSubMove();
    }
    
    new_board->Turn = this->Turn == White ? Black : White;
    
    new_board->Confirm();
    
    return new_board;
}

void Board::SetChess(Chess* chess)
{
    if (this->Confirmed)
    {
        return;
    }
    
    int x = chess->GetX();
    int y = chess->GetY();
    this->Chesses[x + y * BoardSize] = chess;
}

void Board::UnsetChess(int x, int y)
{
    delete this->Chesses[x + y * BoardSize];
    this->Chesses[x + y * BoardSize] = NULL;
}

Chess* Board::GetChess(int x, int y)
{
    if (x < 0 || x >= pp9k::BoardSize || y < 0 || y >= pp9k::BoardSize)
    {
        return NULL;
    }
    return this->Chesses[x + y * BoardSize];
}

Chess* Board::GetLastMovedChess()
{
    return this->LastMovedChess;
}

void Board::Confirm()
{
    this->Confirmed = true;
}

bool Board::IsValid()
{
    if (this->IsCheck(this->Turn))
    {
        return false;
    }
    
    int white_king = 0;
    int black_king = 0;
    for (int i = 0; i < pp9k::BoardSize * pp9k::BoardSize; i++)
    {
        if (this->Chesses[i]->GetChessType())
        {
            if (this->Chesses[i]->GetPlayer()->GetSide() == White)
            {
                white_king += 1;
            }
            else
            {
                black_king += 1;
            }
        }
    }
    
    return black_king == 1 && white_king == 1;
}

bool Board::IsCheck(Color side)
{
    Moves* moves = new Moves();
    
    int j =0;
    for (int i = 0; i < BoardSize * BoardSize; i++)
    {
        if (this->Chesses[i] != NULL && this->Chesses[i]->GetPlayer()->GetSide() == side)
            this->Chesses[i]->GetAvailableMoves(this, moves);
        for (; j < moves->GetLength(); j++)
        {
            Move* move = moves->GetMove(j);
            Chess* captured = move->GetChessCaptured();
            if (captured != NULL && captured->GetChessType() == King)
            {
                delete moves;
                
                return true;
            }
        }
    }
    delete moves;
    
    return false;
}

bool Board::IsCheckmate(Color side)
{
    if (!this->IsCheck(side))
    {
        return false;
    }
    
    Color opponent = side == White ? Black : White;
    Moves* moves = this->GetAllAvailableMoves(opponent);
    
    bool checkmate = moves->GetLength() == 0;
    
    delete moves;
    
    return checkmate;
}

bool Board::HasMove(Color side)
{
    Moves* moves = this->GetAllAvailableMoves(side);
    
    bool has_move = moves->GetLength() > 0;
    
    delete moves;
    
    return has_move;
}

void Board::AddStandardPiece(int x, int y, ChessType type, Player* player)
{
    Chess* piece;
    switch (type)
    {
        case King:
            piece = new ChessKing(player, x, y, false);
            break;
            
        case Queen:
            piece = new ChessQueen(player, x, y);
            break;
            
        case Bishop:
            piece = new ChessBishop(player, x, y);
            break;
            
        case Rook:
            piece = new ChessRook(player, x, y, false);
            break;
            
        case Knight:
            piece = new ChessKnight(player, x, y);
            break;
            
        case Pawn:
            piece = new ChessPawn(player, x, y, false, false);
            break;
            
        case Blank:
        default:
            piece = NULL;
            break;
    }
    Chesses[x + y * pp9k::BoardSize] = piece;
}

Board* Board::CreateStandardBoard(Player* player1, Player* player2)
{
    Board* board = new Board();
    
    board->Turn = White;
    
    board->AddStandardPiece(0, 0, Rook, player1);
    board->AddStandardPiece(1, 0, Knight, player1);
    board->AddStandardPiece(2, 0, Bishop, player1);
    board->AddStandardPiece(3, 0, Queen, player1);
    board->AddStandardPiece(4, 0, King, player1);
    board->AddStandardPiece(5, 0, Bishop, player1);
    board->AddStandardPiece(6, 0, Knight, player1);
    board->AddStandardPiece(7, 0, Rook, player1);
    
    board->AddStandardPiece(0, 1, Pawn, player1);
    board->AddStandardPiece(1, 1, Pawn, player1);
    board->AddStandardPiece(2, 1, Pawn, player1);
    board->AddStandardPiece(3, 1, Pawn, player1);
    board->AddStandardPiece(4, 1, Pawn, player1);
    board->AddStandardPiece(5, 1, Pawn, player1);
    board->AddStandardPiece(6, 1, Pawn, player1);
    board->AddStandardPiece(7, 1, Pawn, player1);
    
    board->AddStandardPiece(0, pp9k::BoardSize - 1, Rook, player2);
    board->AddStandardPiece(1, pp9k::BoardSize - 1, Knight, player2);
    board->AddStandardPiece(2, pp9k::BoardSize - 1, Bishop, player2);
    board->AddStandardPiece(3, pp9k::BoardSize - 1, Queen, player2);
    board->AddStandardPiece(4, pp9k::BoardSize - 1, King, player2);
    board->AddStandardPiece(5, pp9k::BoardSize - 1, Bishop, player2);
    board->AddStandardPiece(6, pp9k::BoardSize - 1, Knight, player2);
    board->AddStandardPiece(7, pp9k::BoardSize - 1, Rook, player2);
    
    board->AddStandardPiece(0, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(1, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(2, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(3, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(4, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(5, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(6, pp9k::BoardSize - 2, Pawn, player2);
    board->AddStandardPiece(7, pp9k::BoardSize - 2, Pawn, player2);
    
    board->Confirmed = true;
    
    return board;
}

Board* Board::ReplacePlayers(Player* player1, Player* player2)
{
    Board* board = new Board();
    Chess* piece;
    Player* player;
    
    for (int i = 0; i < pp9k::BoardSize; i++)
    {
        for (int j = 0; j < pp9k::BoardSize; j++)
        {
            piece = this->Chesses[i + j * pp9k::BoardSize];
            if (piece == NULL)
            {
                board->Chesses[i + j * pp9k::BoardSize] = NULL;
            }
            else
            {
                player = piece->GetPlayer()->GetSide() == White ? player1 : player2;
                board->Chesses[i + j * pp9k::BoardSize] = piece->ReplacePlayer(player);
            }
        }
    }
    
    board->Confirmed = this->Confirmed;
    board->Turn = this->Turn;
    
    return board;
}

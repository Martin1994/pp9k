//
//  Chess.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Chess.h"

using namespace pp9k;

Chess::Chess(pp9k::Player* player, int x, int y)
{
    this->Player = player;
    this->X = x;
    this->Y = y;
}

Chess::~Chess()
{
    
}

Chess* Chess::ReplacePlayer(pp9k::Player* new_player)
{
    Chess* new_chess = this->Clone();
    new_chess->Player = new_player;
    return new_chess;
}

pp9k::Player* Chess::GetPlayer()
{
    return this->Player;
}

Moves* Chess::GetAvailableMoves(Board* board)
{
    Moves* moves = new Moves();
    
    this->GetAvailableMoves(board, moves);
    
    return moves;
}

int Chess::GetX()
{
    return this->X;
}

int Chess::GetY()
{
    return this->Y;
}

bool Chess::ConvertCharToField(char ch, ChessType* type, Color* side)
{

    switch (ch)
    {
        case 'K':
            *type = King;
            *side = White;
            break;

        case 'k':
            *type = King;
            *side = Black;
            break;

        case 'Q':
            *type = Queen;
            *side = White;
            break;

        case 'q':
            *type = Queen;
            *side = Black;
            break;

        case 'B':
            *type = Bishop;
            *side = White;
            break;

        case 'b':
            *type = Bishop;
            *side = Black;
            break;

        case 'R':
            *type = Rook;
            *side = White;
            break;

        case 'r':
            *type = Rook;
            *side = Black;
            break;

        case 'N':
            *type = Knight;
            *side = White;
            break;

        case 'n':
            *type = Knight;
            *side = Black;
            break;

        case 'P':
            *type = Pawn;
            *side = White;
            break;

        case 'p':
            *type = Pawn;
            *side = Black;
            break;

        default:
            return false;
    }

    return true;
}

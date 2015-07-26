//
//  Enumerations.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef pp9k_Enumerations_h
#define pp9k_Enumerations_h

namespace pp9k
{
    enum Color
    {
        White = 0,
        Black
    };
    
    enum ChessType
    {
        Blank = 0,
        King,
        Queen,
        Bishop,
        Rook,
        Knight,
        Pawn
    };
    
    enum GameStatus
    {
        End = 0,
        Setup,
        Start
    };
}

#endif

//
//  BoardHistory.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__BoardHistory__
#define __pp9k__BoardHistory__

#include "Board.h"

namespace pp9k
{
    class Board;
    
    class BoardHistory
    {
    private:
        int Capacity;
        int Length;
        Board** Boards;
        
    public:
        BoardHistory();
        ~BoardHistory();
        void PushBoard(Board* board);
        Board* PopBoard();
    };
}

#endif /* defined(__pp9k__BoardHistory__) */

//
//  Game.h
//  pp9k
//
//  Created by Martin Wang on 2015-07-20.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#ifndef __pp9k__Game__
#define __pp9k__Game__

#include "View.h"
#include "Board.h"
#include "Chess.h"
#include "Enumerations.h"

namespace pp9k
{
    class View;
    class Board;
    class BoardHistory;
    class Player;
    class Chess;
    
    class Game
    {
    private:
        Player* Players[2];
        GameStatus Status;
        int Score[2];
        
        void Stalemate();
        void Win(Color side, bool checkmate);
        
    public:
        class View* View;
        Board* CurrentBoard;
        BoardHistory* Boards;
        
        Game();
        ~Game();
        
        void SetView(pp9k::View* view);
        
        pp9k::View* GetView();

		GameStatus GetStatus();
        
        Player* GetPlayer(pp9k::Color side);
        
        bool SetTurn(Color side);
        Color GetTurn();
        
        double GetScore(Color side);
        
        /**
         * Start a new game and set players
         */
        bool Start(Player* player1, Player* player2);
        
        /**
         * Enter setup mode
         */
        bool Initialize();
        
        /**
         * Exit setup mode
         */
        bool InitializeComplete();
        
        bool AddPiece(Chess* piece);
        
        bool RemovePiece(int x, int y);
        
        bool MakeMove(int original_x, int original_y, int target_x, int target_y, ChessType prefer);
        
        bool Resign();
        
        bool RequestStalemate();
        
        bool Undo();

		bool RefreshBoard();
        
        bool Exit();
        
    };
}

#endif /* defined(__pp9k__Game__) */

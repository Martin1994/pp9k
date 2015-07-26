//
//  libchloropp9k.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#include "Game.h"
#include "ViewWrapper.h"
#include "Controller.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    struct pp9k_wrapper
    {
        pp9k::Controller* controller;
        pp9k::Game* game;
        pp9k::ViewWrapper* view;
        
        pp9k_wrapper()
        {
            controller = new pp9k::Controller();
            game = new pp9k::Game();
            view = new pp9k::ViewWrapper();
            
            controller->SetGame(game);
            game->SetView(view);
            view->SetController(controller);
        }
        
        ~pp9k_wrapper()
        {
            delete controller;
            delete game;
            delete view;
        }
    };
    
    int pp9k_color_white() { return pp9k::White; }
    int pp9k_color_black() { return pp9k::Black; }
    int pp9k_type_blank() { return pp9k::Blank; }
    int pp9k_type_king() { return pp9k::King; }
    int pp9k_type_queen() { return pp9k::Queen; }
    int pp9k_type_bishop() { return pp9k::Bishop ;}
    int pp9k_type_rook() { return pp9k::Rook; }
    int pp9k_type_knight() { return pp9k::Knight; }
    int pp9k_type_pawn() { return pp9k::Pawn; }
    
    void* create_pp9k()
    {
        return new pp9k_wrapper;
    }
    
    void destroy_pp9k(void* wrapper)
    {
        delete (pp9k_wrapper*) wrapper;
    }
    
    bool make_move(void* wrapper, int original_x, int original_y, int target_x, int target_y)
    {
        return ((pp9k_wrapper*) wrapper)->controller->MakeMove(original_x, original_y, target_x, target_y);
    }
    
    bool undo(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Undo();
    }
    
    bool resign(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Resign();
    }
    
    bool start_game(void* wrapper, char* player1, char* player2)
    {
        std::string p1s(player1);
        std::string p2s(player2);
        return ((pp9k_wrapper*) wrapper)->controller->StartGame(p1s, p2s);
    }
    
    bool setup(void* wrapper, int x, int y, pp9k::ChessType type, pp9k::Color side = pp9k::White)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Setup(x, y, type, side);
    }
    
    bool initialize_complete(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->InitializeComplete();
    }
    
    bool initialize_game(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->InitializeGame();
    }
    
    bool set_turn(void* wrapper, pp9k::Color side)
    {
        return ((pp9k_wrapper*) wrapper)->controller->SetTurn(side);
    }
    
    bool exit_game(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Exit();
    }
    
    bool set_change_board_handler(void* wrapper, pp9k::ViewWrapper::ChangeBoardFunc handler)
    {
        return ((pp9k_wrapper*) wrapper)->view->ChangeBoardHandler = handler;
    }
    
    bool set_flush_board_handler(void* wrapper, pp9k::ViewWrapper::FlushBoardFunc handler)
    {
        return ((pp9k_wrapper*) wrapper)->view->FlushBoardHandler = handler;
    }
    
    bool set_win_handler(void* wrapper, pp9k::ViewWrapper::WinFunc handler)
    {
        return ((pp9k_wrapper*) wrapper)->view->WinHandler = handler;
    }
    
    bool set_draw_handler(void* wrapper, pp9k::ViewWrapper::DrawFunc handler)
    {
        return ((pp9k_wrapper*) wrapper)->view->DrawHandler = handler;
    }
    
    bool set_show_score_handler(void* wrapper, pp9k::ViewWrapper::ShowScoreFunc handler)
    {
        return ((pp9k_wrapper*) wrapper)->view->ShowScoreHandler = handler;
    }
    
    
#ifdef __cplusplus
}
#endif

//
//  libchloropp9k.cpp
//  pp9k
//
//  Created by Martin Wang on 2015-07-25.
//  Copyright (c) 2015 Martin Chloride. All rights reserved.
//

#if defined(_MSC_VER)
//  Microsoft 
#define EXPORT __declspec(dllexport)
#elif defined(_GCC)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#else
//  do nothing and hope for the best?
#define EXPORT
#endif

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
    
    EXPORT int pp9k_color_white() { return pp9k::White; }
    EXPORT int pp9k_color_black() { return pp9k::Black; }
    EXPORT int pp9k_type_blank() { return pp9k::Blank; }
    EXPORT int pp9k_type_king() { return pp9k::King; }
    EXPORT int pp9k_type_queen() { return pp9k::Queen; }
    EXPORT int pp9k_type_bishop() { return pp9k::Bishop ;}
    EXPORT int pp9k_type_rook() { return pp9k::Rook; }
    EXPORT int pp9k_type_knight() { return pp9k::Knight; }
    EXPORT int pp9k_type_pawn() { return pp9k::Pawn; }
    
	EXPORT void* create_pp9k()
    {
        return new pp9k_wrapper;
    }
    
	EXPORT void destroy_pp9k(void* wrapper)
    {
        delete (pp9k_wrapper*) wrapper;
    }
    
	EXPORT bool make_move(void* wrapper, int original_x, int original_y, int target_x, int target_y)
    {
        return ((pp9k_wrapper*) wrapper)->controller->MakeMove(original_x, original_y, target_x, target_y);
    }
    
	EXPORT bool undo(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Undo();
    }
    
	EXPORT bool resign(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Resign();
    }
    
	EXPORT bool start_game(void* wrapper, char* player1, char* player2)
    {
        std::string p1s(player1);
        std::string p2s(player2);
        return ((pp9k_wrapper*) wrapper)->controller->StartGame(p1s, p2s);
    }
    
	EXPORT bool setup(void* wrapper, int x, int y, pp9k::ChessType type, pp9k::Color side = pp9k::White)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Setup(x, y, type, side);
    }
    
	EXPORT bool initialize_complete(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->InitializeComplete();
    }
    
	EXPORT bool initialize_game(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->InitializeGame();
    }
    
	EXPORT bool set_turn(void* wrapper, pp9k::Color side)
    {
        return ((pp9k_wrapper*) wrapper)->controller->SetTurn(side);
    }
    
	EXPORT bool exit_game(void* wrapper)
    {
        return ((pp9k_wrapper*) wrapper)->controller->Exit();
    }
    
	EXPORT void set_change_board_handler(void* wrapper, pp9k::ViewWrapper::ChangeBoardFunc handler)
    {
        ((pp9k_wrapper*) wrapper)->view->ChangeBoardHandler = handler;
    }
    
	EXPORT void set_flush_board_handler(void* wrapper, pp9k::ViewWrapper::FlushBoardFunc handler)
    {
        ((pp9k_wrapper*) wrapper)->view->FlushBoardHandler = handler;
    }
    
	EXPORT void set_win_handler(void* wrapper, pp9k::ViewWrapper::WinFunc handler)
    {
        ((pp9k_wrapper*) wrapper)->view->WinHandler = handler;
    }
    
	EXPORT void set_draw_handler(void* wrapper, pp9k::ViewWrapper::DrawFunc handler)
    {
        ((pp9k_wrapper*) wrapper)->view->DrawHandler = handler;
    }
    
	EXPORT void set_show_score_handler(void* wrapper, pp9k::ViewWrapper::ShowScoreFunc handler)
    {
        ((pp9k_wrapper*) wrapper)->view->ShowScoreHandler = handler;
    }
    
    
#ifdef __cplusplus
}
#endif

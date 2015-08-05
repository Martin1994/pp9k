FLAG=-std=c++03 -fPIC

pp9k: main.cpp Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	g++ $(FLAG) -o pp9k main.cpp Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o -lX11

libchloropp9k.so: libchloropp9k.cpp Game.o Controller.o View.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	g++ $(FLAG) -shared -o libchloropp9k.so libchloropp9k.cpp Game.o Controller.o View.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

Game.o: Game.cpp Game.h
	g++ $(FLAG) -c -o Game.o Game.cpp

Controller.o: Controller.cpp Controller.h
	g++ $(FLAG) -c -o Controller.o Controller.cpp

Xwindow.o: window.cc window.h
	g++ $(FLAG) -c -o Xwindow.o window.cc

View.o: View.cpp View.h
	g++ $(FLAG) -c -o View.o View.cpp

ViewCLI.o: ViewCLI.cpp ViewCLI.h
	g++ $(FLAG) -c -o ViewCLI.o ViewCLI.cpp

ViewGUI.o: ViewGUI.cpp ViewGUI.h
	g++ $(FLAG) -c -o ViewGUI.o ViewGUI.cpp

ViewWrapper.o: ViewWrapper.cpp ViewWrapper.h
	g++ $(FLAG) -c -o ViewWrapper.o ViewWrapper.cpp

Player.o: Player.cpp Player.h
	g++ $(FLAG) -c -o Player.o Player.cpp

PlayerHuman.o: PlayerHuman.cpp PlayerHuman.h
	g++ $(FLAG) -c -o PlayerHuman.o PlayerHuman.cpp

PlayerAI.o: PlayerAI.cpp PlayerAI.h
	g++ $(FLAG) -c -o PlayerAI.o PlayerAI.cpp

PlayerAI1.o: PlayerAI1.cpp PlayerAI1.h
	g++ $(FLAG) -c -o PlayerAI1.o PlayerAI1.cpp

PlayerAI2.o: PlayerAI2.cpp PlayerAI2.h
	g++ $(FLAG) -c -o PlayerAI2.o PlayerAI2.cpp

PlayerAI3.o: PlayerAI3.cpp PlayerAI3.h
	g++ $(FLAG) -c -o PlayerAI3.o PlayerAI3.cpp

PlayerAI4.o: PlayerAI4.cpp PlayerAI4.h
	g++ $(FLAG) -c -o PlayerAI4.o PlayerAI4.cpp

Board.o: Board.cpp Board.h
	g++ $(FLAG) -c -o Board.o Board.cpp

BoardHistory.o: BoardHistory.cpp BoardHistory.h
	g++ $(FLAG) -c -o BoardHistory.o BoardHistory.cpp

Move.o: Move.cpp Move.h
	g++ $(FLAG) -c -o Move.o Move.cpp

Chess.o: Chess.cpp Chess.h
	g++ $(FLAG) -c -o Chess.o Chess.cpp

ChessKing.o: ChessKing.cpp ChessKing.h
	g++ $(FLAG) -c -o ChessKing.o ChessKing.cpp

ChessQueen.o: ChessQueen.cpp ChessQueen.h
	g++ $(FLAG) -c -o ChessQueen.o ChessQueen.cpp

ChessBishop.o: ChessBishop.cpp ChessBishop.h
	g++ $(FLAG) -c -o ChessBishop.o ChessBishop.cpp

ChessRook.o: ChessRook.cpp ChessRook.h
	g++ $(FLAG) -c -o ChessRook.o ChessRook.cpp

ChessKnight.o: ChessKnight.cpp ChessKnight.h
	g++ $(FLAG) -c -o ChessKnight.o ChessKnight.cpp

ChessPawn.o: ChessPawn.cpp ChessPawn.h
	g++ $(FLAG) -c -o ChessPawn.o ChessPawn.cpp

clean:
	rm Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

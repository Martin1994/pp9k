CXXFLAG ?= -std=c++03 -fPIC -g
CXX ?= g++
OUT_EXEC ?= pp9k

pp9k: main.cpp Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	$(CXX) $(CXXFLAG) -o $(OUT_EXEC) main.cpp Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o -lX11

libchloropp9k.so: libchloropp9k.cpp Game.o Controller.o View.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	$(CXX) $(CXXFLAG) -shared -o libchloropp9k.so libchloropp9k.cpp Game.o Controller.o View.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

pp9k-cli: main.cpp Game.o Controller.o View.o ViewCLI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	$(CXX) $(CXXFLAG) -DNO_GUI -o $(OUT_EXEC) main.cpp Game.o Controller.o View.o ViewCLI.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAG) -c -o Game.o Game.cpp

Controller.o: Controller.cpp Controller.h
	$(CXX) $(CXXFLAG) -c -o Controller.o Controller.cpp

Xwindow.o: window.cc window.h
	$(CXX) $(CXXFLAG) -c -o Xwindow.o window.cc

View.o: View.cpp View.h
	$(CXX) $(CXXFLAG) -c -o View.o View.cpp

ViewCLI.o: ViewCLI.cpp ViewCLI.h
	$(CXX) $(CXXFLAG) -c -o ViewCLI.o ViewCLI.cpp

ViewGUI.o: ViewGUI.cpp ViewGUI.h
	$(CXX) $(CXXFLAG) -c -o ViewGUI.o ViewGUI.cpp

ViewWrapper.o: ViewWrapper.cpp ViewWrapper.h
	$(CXX) $(CXXFLAG) -c -o ViewWrapper.o ViewWrapper.cpp

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAG) -c -o Player.o Player.cpp

PlayerHuman.o: PlayerHuman.cpp PlayerHuman.h
	$(CXX) $(CXXFLAG) -c -o PlayerHuman.o PlayerHuman.cpp

PlayerAI.o: PlayerAI.cpp PlayerAI.h
	$(CXX) $(CXXFLAG) -c -o PlayerAI.o PlayerAI.cpp

PlayerAI1.o: PlayerAI1.cpp PlayerAI1.h
	$(CXX) $(CXXFLAG) -c -o PlayerAI1.o PlayerAI1.cpp

PlayerAI2.o: PlayerAI2.cpp PlayerAI2.h
	$(CXX) $(CXXFLAG) -c -o PlayerAI2.o PlayerAI2.cpp

PlayerAI3.o: PlayerAI3.cpp PlayerAI3.h
	$(CXX) $(CXXFLAG) -c -o PlayerAI3.o PlayerAI3.cpp

PlayerAI4.o: PlayerAI4.cpp PlayerAI4.h
	$(CXX) $(CXXFLAG) -c -o PlayerAI4.o PlayerAI4.cpp

Board.o: Board.cpp Board.h
	$(CXX) $(CXXFLAG) -c -o Board.o Board.cpp

BoardHistory.o: BoardHistory.cpp BoardHistory.h
	$(CXX) $(CXXFLAG) -c -o BoardHistory.o BoardHistory.cpp

Move.o: Move.cpp Move.h
	$(CXX) $(CXXFLAG) -c -o Move.o Move.cpp

Chess.o: Chess.cpp Chess.h
	$(CXX) $(CXXFLAG) -c -o Chess.o Chess.cpp

ChessKing.o: ChessKing.cpp ChessKing.h
	$(CXX) $(CXXFLAG) -c -o ChessKing.o ChessKing.cpp

ChessQueen.o: ChessQueen.cpp ChessQueen.h
	$(CXX) $(CXXFLAG) -c -o ChessQueen.o ChessQueen.cpp

ChessBishop.o: ChessBishop.cpp ChessBishop.h
	$(CXX) $(CXXFLAG) -c -o ChessBishop.o ChessBishop.cpp

ChessRook.o: ChessRook.cpp ChessRook.h
	$(CXX) $(CXXFLAG) -c -o ChessRook.o ChessRook.cpp

ChessKnight.o: ChessKnight.cpp ChessKnight.h
	$(CXX) $(CXXFLAG) -c -o ChessKnight.o ChessKnight.cpp

ChessPawn.o: ChessPawn.cpp ChessPawn.h
	$(CXX) $(CXXFLAG) -c -o ChessPawn.o ChessPawn.cpp

clean:
	rm Game.o Controller.o Xwindow.o View.o ViewCLI.o ViewGUI.o ViewWrapper.o Player.o PlayerHuman.o PlayerAI.o PlayerAI1.o PlayerAI2.o PlayerAI3.o PlayerAI4.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

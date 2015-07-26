pp9k: main.cpp Game.o Controller.o View.o ViewCLI.o ViewWrapper.o Player.o PlayerHuman.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	g++ -o pp9k main.cpp Game.o Controller.o View.o ViewCLI.o ViewWrapper.o Player.o PlayerHuman.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

libchloropp9k.so: libchloropp9k.cpp Game.o Controller.o View.o ViewCLI.o ViewWrapper.o Player.o PlayerHuman.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o
	g++ -fPIC -shared -o libchloropp9k.so libchloropp9k.cpp Game.o Controller.o View.o ViewCLI.o ViewWrapper.o Player.o PlayerHuman.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

Game.o: Game.cpp Game.h
	g++ -c -o Game.o Game.cpp

Controller.o: Controller.cpp Controller.h
	g++ -c -o Controller.o Controller.cpp

View.o: View.cpp View.h
	g++ -c -o View.o View.cpp

ViewCLI.o: ViewCLI.cpp ViewCLI.h
	g++ -c -o ViewCLI.o ViewCLI.cpp

ViewWrapper.o: ViewWrapper.cpp ViewWrapper.h
	g++ -c -o ViewWrapper.o ViewWrapper.cpp

Player.o: Player.cpp Player.h
	g++ -c -o Player.o Player.cpp

PlayerHuman.o: PlayerHuman.cpp PlayerHuman.h
	g++ -c -o PlayerHuman.o PlayerHuman.cpp

Board.o: Board.cpp Board.h
	g++ -c -o Board.o Board.cpp

BoardHistory.o: BoardHistory.cpp BoardHistory.h
	g++ -c -o BoardHistory.o BoardHistory.cpp

Move.o: Move.cpp Move.h
	g++ -c -o Move.o Move.cpp

Chess.o: Chess.cpp Chess.h
	g++ -c -o Chess.o Chess.cpp

ChessKing.o: ChessKing.cpp ChessKing.h
	g++ -c -o ChessKing.o ChessKing.cpp

ChessQueen.o: ChessQueen.cpp ChessQueen.h
	g++ -c -o ChessQueen.o ChessQueen.cpp

ChessBishop.o: ChessBishop.cpp ChessBishop.h
	g++ -c -o ChessBishop.o ChessBishop.cpp

ChessRook.o: ChessRook.cpp ChessRook.h
	g++ -c -o ChessRook.o ChessRook.cpp

ChessKnight.o: ChessKnight.cpp ChessKnight.h
	g++ -c -o ChessKnight.o ChessKnight.cpp

ChessPawn.o: ChessPawn.cpp ChessPawn.h
	g++ -c -o ChessPawn.o ChessPawn.cpp

clean:
	rm Game.o Controller.o View.o ViewCLI.o ViewWrapper.o Player.o PlayerHuman.o Board.o BoardHistory.o Move.o Chess.o ChessKing.o ChessQueen.o ChessBishop.o ChessRook.o ChessKnight.o ChessPawn.o

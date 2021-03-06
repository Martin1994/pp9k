using System;
using System.Runtime.InteropServices;

namespace pp9kNET
{
    public class Chloropp9kNET : IDisposable
    {
        internal const string pp9kDllPath = "Library/libchloropp9k.dll";

        protected readonly IntPtr Wrapper;
        
        protected readonly Object ConcurrentLock = new Object();
        
        public Chloropp9kNET()
        {
            Wrapper = create_pp9k();

            set_change_board_handler(Wrapper, ChangeBoardHandlerWrapper);
            set_flush_board_handler(Wrapper, FlushBoardHandlerWrapper);
            set_win_handler(Wrapper, WinHandlerWrapper);
            set_draw_handler(Wrapper, DrawHandlerWrapper);
            set_show_score_handler(Wrapper, ShowScoreHandlerWrapper);
            set_change_turn_handler(Wrapper, ChangeTurnHandlerWrapper);
        }

        ~Chloropp9kNET()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (Wrapper != IntPtr.Zero)
            {
                destroy_pp9k(Wrapper);
            }
        }

        public bool MakeMove(int from_x, int from_y, int to_x, int to_y, Type prefer = Type.Queen)
        {
            lock (ConcurrentLock)
            {
                return make_move(Wrapper, from_x, from_y, to_x, to_y, prefer.ToInt());
            }
        }

        public bool Undo()
        {
            lock (ConcurrentLock)
            {
                return undo(Wrapper);
            }
        }

        public bool Resign()
        {
            lock (ConcurrentLock)
            {
                return resign(Wrapper);
            }
        }

        public bool StartGame(Player player_1, Player player_2)
        {
            lock (ConcurrentLock)
            {
                return start_game(Wrapper, player_1.ToInt(), player_2.ToInt());
            }
        }

        public bool Setup(int x, int y, Type type, Color side)
        {
            lock (ConcurrentLock)
            {
                return setup(Wrapper, x, y, type.ToInt(), side.ToInt());
            }
        }

        public bool InitializeComplete()
        {
            lock (ConcurrentLock)
            {
                return initialize_complete(Wrapper);
            }
        }

        public bool InitializeGame()
        {
            lock (ConcurrentLock)
            {
                return initialize_game(Wrapper);
            }
        }

        public bool SetTurn(Color side)
        {
            lock (ConcurrentLock)
            {
                return set_turn(Wrapper, side.ToInt());
            }
        }

        public bool Exit()
        {
            lock (ConcurrentLock)
            {
                return exit_game(Wrapper);
            }
        }

        public delegate void ChangeBoardHandler(int x, int y, Type type, Color side);
        public event ChangeBoardHandler BoardChanged;

        private void ChangeBoardHandlerWrapper(int x, int y, int type, int side)
        {
            if (BoardChanged != null)
                BoardChanged(x, y, type.ToType(), side.ToColor());
        }

        public delegate void FlushBoardHandler();
        public event FlushBoardHandler BoardFlushed;

        private void FlushBoardHandlerWrapper()
        {
            if (BoardFlushed != null)
                BoardFlushed();
        }

        public delegate void WinHandler(Color side, bool checkmate);
        public event WinHandler Won;

        private void WinHandlerWrapper(int side, bool checkmate)
        {
            if (Won != null)
                Won(side.ToColor(), checkmate);
        }

        public delegate void DrawHandler();
        public event DrawHandler Drawn;

        private void DrawHandlerWrapper()
        {
            if (Drawn != null)
                Drawn();
        }

        public delegate void ShowScoreHandler(double score_1, double score_2);
        public event ShowScoreHandler ScoreShown;

        private void ShowScoreHandlerWrapper(double score_1, double score_2)
        {
            if (ScoreShown != null)
                ScoreShown(score_1, score_2);
        }

        public delegate void ChangeTurnHandler(Color sude);
        public event ChangeTurnHandler TurnChanged;

        private void ChangeTurnHandlerWrapper(int color)
        {
            if (TurnChanged != null)
                TurnChanged(color.ToColor());
        }

        #region Imported methods

        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr create_pp9k();
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void destroy_pp9k(IntPtr pp9k);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool make_move(IntPtr pp9k, int from_x, int from_y, int to_x, int to_y, int prefer);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool undo(IntPtr pp9k);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool resign(IntPtr pp9k);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool start_game(IntPtr pp9k, int player_1, int player_2);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool setup(IntPtr pp9k, int x, int y, int type, int side);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool initialize_complete(IntPtr pp9k);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool initialize_game(IntPtr pp9k);
        
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_turn(IntPtr pp9k, int side);

        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool refresh_board(IntPtr pp9k);

        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool exit_game(IntPtr pp9k);

        delegate void ChangeBoardFunc(int x, int y, int type, int side);
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_change_board_handler(IntPtr pp9k, ChangeBoardFunc func);

        delegate void FlushBoardFunc();
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_flush_board_handler(IntPtr pp9k, FlushBoardFunc func);

        delegate void WinFunc(int side, bool checkmate);
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_win_handler(IntPtr pp9k, WinFunc func);

        delegate void DrawFunc();
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_draw_handler(IntPtr pp9k, DrawFunc func);

        delegate void ShowScoreFunc(double score_1, double score_2);
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_show_score_handler(IntPtr pp9k, ShowScoreFunc func);

        delegate void ChangeTurnFunc(int side);
        [DllImport(pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool set_change_turn_handler(IntPtr pp9k, ChangeTurnFunc func);

        #endregion

    }

    public enum Type
    {
        Blank = 0,
        King,
        Queen,
        Bishop,
        Rook,
        Knight,
        Pawn
    }

    public enum Color
    {
        White = 0,
        Black
    }

    public enum Player
    {
        Human = 0,
        AI1,
        AI2,
        AI3,
        AI4
    }

    public static class Chloropp9kNETEnumExtensions
    {

        #region Imported enumeration value functions

        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_color_white();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_color_black();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_blank();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_king();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_queen();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_bishop();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_rook();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_knight();
        [DllImport(Chloropp9kNET.pp9kDllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int pp9k_type_pawn();

        #endregion

        #region Imported enumeration values

        private static int TypeBlank;
        private static int TypeKing;
        private static int TypeQueen;
        private static int TypeBishop;
        private static int TypeRook;
        private static int TypeKnight;
        private static int TypePawn;

        private static int ColorWhite;
        private static int ColorBlack;

        #endregion


        static Chloropp9kNETEnumExtensions()
        {
            TypeBlank = pp9k_type_blank();
            TypeKing = pp9k_type_king();
            TypeQueen = pp9k_type_queen();
            TypeBishop = pp9k_type_bishop();
            TypeRook = pp9k_type_rook();
            TypeKnight = pp9k_type_knight();
            TypePawn = pp9k_type_pawn();

            ColorWhite = pp9k_color_white();
            ColorBlack = pp9k_color_black();
        }

        public static int ToInt(this Type type)
        {
            switch (type)
            {
                case Type.King:
                    return TypeKing;

                case Type.Queen:
                    return TypeQueen;

                case Type.Bishop:
                    return TypeBishop;

                case Type.Rook:
                    return TypeRook;

                case Type.Knight:
                    return TypeKnight;

                case Type.Pawn:
                    return TypePawn;

                case Type.Blank:
                    return TypeBlank;

                default:
                    return TypeBlank;
            }
        }

        public static int ToInt(this Color color)
        {
            switch (color)
            {
                case Color.Black:
                    return ColorBlack;

                case Color.White:
                    return ColorWhite;

                default:
                    return pp9k_color_white();
            }
        }

        public static Type ToType(this int type_code)
        {
            if (type_code == TypeKing)
            {
                return Type.King;
            }
            else if (type_code == TypeQueen)
            {
                return Type.Queen;
            }
            else if (type_code == TypeBishop)
            {
                return Type.Bishop;
            }
            else if (type_code == TypeRook)
            {
                return Type.Rook;
            }
            else if (type_code == TypeKnight)
            {
                return Type.Knight;
            }
            else if (type_code == TypePawn)
            {
                return Type.Pawn;
            }
            else
            {
                return Type.Blank;
            }
        }

        public static Color ToColor(this int color_code)
        {
            if(color_code == ColorBlack)
            {
                return Color.Black;
            }
            else if(color_code == ColorWhite)
            {
                return Color.White;
            }
            else
            {
                return Color.White;
            }
        }

        public static int ToInt(this Player player)
        {
            switch (player)
            {
                case Player.AI1:
                    return 1;

                case Player.AI2:
                    return 2;

                case Player.AI3:
                    return 3;

                case Player.AI4:
                    return 4;
                    
                case Player.Human:
                    return 0;

                default:
                    return 0;

            }
        }
    }
}

using System;
using System.Runtime.InteropServices;

namespace Chloropp9k
{
    public class Chloropp9kNET : IDisposable
    {
        private const string pp9kDllPath = "libchloropp9k.so";
        
        private IntPtr Wrapper;
        
        public Chloropp9kNET()
        {
            Wrapper = create_pp9k();
        }

        public void Dispose()
        {
            destroy_pp9k(Wrapper);
        }
        
        #region Import
        
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_color_white();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_color_black();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_blank();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_king();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_queen();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_bishop();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_rook();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_knight();
        [DllImport(pp9kDllPath)]
        private extern static int pp9k_type_pawn();
        
        [DllImport(pp9kDllPath)]
        private extern static IntPtr create_pp9k();
        
        [DllImport(pp9kDllPath)]
        private extern static void destroy_pp9k(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool make_move(IntPtr pp9k, int from_x, int from_y, int to_x, int to_y);
        
        [DllImport(pp9kDllPath)]
        private extern static bool undo(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool resign(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool start_game(IntPtr pp9k, char[] player_1, char[] player_2);
        
        [DllImport(pp9kDllPath)]
        private extern static bool setup(IntPtr pp9k, int x, int y, int type, int side);
        
        [DllImport(pp9kDllPath)]
        private extern static bool initialize_complete(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool initialize_game(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool set_turn(IntPtr pp9k, int side);
        
        [DllImport(pp9kDllPath)]
        private extern static bool exit_game(IntPtr pp9k);
        
        [DllImport(pp9kDllPath)]
        private extern static bool set_change_board_handler(IntPtr pp9k);
        
        #endregion
        
    }
}

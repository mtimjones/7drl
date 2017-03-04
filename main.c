#include "7drltypes.h"

WINDOW *mainwin;

void win_startup( void )
{
   int offsetx, offsety;

   initscr( );
   cbreak( );
   noecho( );
   curs_set( 0 );
   nonl( );

   offsety = ( LINES - NLINES ) / 2;
   offsetx = ( COLS - NCOLS ) / 2;

   mainwin = newwin( NLINES, NCOLS, offsety, offsetx );
   nodelay( mainwin, TRUE );
   keypad( mainwin, TRUE );

   return;
}

void win_update( int Y, int X )
{
   wborder( mainwin, 0, 0, 0, 0, 0, 0, 0, 0 );

   mvwhline( mainwin, ( MAP_NLINES - 1 ), 1, '-', ( MAP_NCOLS - 1 ) );
   mvwvline( mainwin, 1, ( MAP_NCOLS - 1 ), '|', ( MAP_NLINES - 1 ) );

   mvwprintw( mainwin, 1, (MAP_NCOLS), "%3d,%3d", Y, X );

   wrefresh( mainwin );

   return;
}

void win_shutdown( void )
{
   delwin( mainwin );

   endwin( );

   return;
}


int main( int argc, char *argv[] )
{
   int Y, X;

   srand( time( NULL ) );

   Y = getRand( Y_MAP_MAX );
   X = getRand( X_MAP_MAX );

   MapInit( Y, X );

   win_startup( );

   win_update( Y, X );

   while ( 1 )
   {
      get_input( &Y, &X );

      win_map_viewport( Y, X );

      win_update( Y, X );

      wrefresh( mainwin );
   }

   win_shutdown( );

   return 0;
}


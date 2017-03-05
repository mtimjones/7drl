#include "7drltypes.h"

WINDOW *mainwin;

unsigned int GameTime = 0;

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

   mvwhline( mainwin, ( MAP_NLINES - 1 ), 1, '-', ( NCOLS - 2 ) );
   mvwvline( mainwin, 1, ( MAP_NCOLS - 1 ), '|', ( MAP_NLINES - 2 ) );

   win_map_viewport( Y, X );

   mvwprintw( mainwin, 20, (MAP_NCOLS)+1, "Time     %6d", ( GameTime / ( 1000 / MS_PER_FRAME ) ) );
   mvwprintw( mainwin, 21, (MAP_NCOLS)+1, "Location %3d,%3d", Y, X );

   for ( int i = 0 ; i < MAX_MESSAGES ; i++ )
   {
      mvwprintw( mainwin, ( 23 + i ), 1, "%s", get_message( i ) );
   }

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

   init_messages( );

   Y = getRand( Y_MAP_MAX );
   X = getRand( X_MAP_MAX );

   MapInit( Y, X );

   win_startup( );

   // Emit some instructions.
   add_message( "Welcome to The Forest.\0" );
   add_message( "  You're trapped in the forest, but you can escape with enough artifacts.\0" );
   add_message( "  Artifacts are carried by Protectors, which must be killed to attain them.\0" );  
   add_message( "  Once you have 10 artifacts, find the door in the South to escape.\0" );
   add_message( "  Move with hjkl.\0" );

   win_update( Y, X );

   while ( 1 )
   {
      unsigned long long start = getTimestamp( );

      get_input( &Y, &X );

      // Entity system here...

      // Update the window
      win_update( Y, X );

      while ( getTimestamp( ) < start + MS_PER_FRAME );

      GameTime++;
   }

   win_shutdown( );

   return 0;
}



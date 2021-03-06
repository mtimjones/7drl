#include "7drltypes.h"

WINDOW *mainwin;

unsigned int GameTime = 0;
unsigned int GameRunning = 1;

// Offset to center game pane in the available window.
int offsetx, offsety;

void win_startup( void )
{
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

   // mousemask( BUTTON1_CLICKED, NULL );

   return;
}


void win_update( void )
{
   int Y, X;

   extern int exit_y, exit_x;

   wborder( mainwin, 0, 0, 0, 0, 0, 0, 0, 0 );

   mvwhline( mainwin, ( MAP_NLINES - 1 ), 1, '-', ( NCOLS - 2 ) );
   mvwvline( mainwin, 1, ( MAP_NCOLS - 1 ), '|', ( MAP_NLINES - 2 ) );

   Y = GetPlayerLocationY( );
   X = GetPlayerLocationX( );

   win_map_viewport( Y, X );

   mvwprintw( mainwin, 28, (MAP_NCOLS)+1, "Exit     %3d,%3d", exit_y, exit_x );
   mvwprintw( mainwin, 30, (MAP_NCOLS)+1, "Time     %7d", ( GameTime / ( 1000 / MS_PER_FRAME ) ) );
   mvwprintw( mainwin, 31, (MAP_NCOLS)+1, "Location %3d,%3d", Y, X );

   EmitPlayerStats( );

   for ( int i = 0 ; i < MAX_MESSAGES ; i++ )
   {
      mvwprintw( mainwin, ( MAP_NLINES + i ), 1, "%s", get_message( i ) );
   }

   wrefresh( mainwin );

   return;
}


void win_shutdown( void )
{
   delwin( mainwin );

   endwin( );

   // mousemask( 0, NULL );

   return;
}


int main( int argc, char *argv[] )
{
   srand( time( NULL ) );

   init_messages( );

   MapInit( );

   PlayerInit( );

   // Init CES
   InitEntities( );

   win_startup( );

   // Emit some instructions.
   add_message( "Welcome to The Forest.\0" );
   add_message( "  You're trapped in the forest, but you can escape with enough artifacts.\0" );
   add_message( "  Artifacts are carried by Protectors, which must be killed to attain them.\0" );  
   add_message( "  Once you have 10 artifacts, find the door in the South to escape.\0" );
   add_message( "  Move with wasd.\0" );

   win_update( );

   while ( GameRunning )
   {
      unsigned long long start = getTimestamp( );

      PlayerMove( );

      // CES system calls here...
      SystemMovementFunction( );

      // Update the window
      win_update( );

      while ( getTimestamp( ) < start + MS_PER_FRAME );

      GameTime++;
   }

   win_shutdown( );

   PlayerEndGame( );

   return 0;
}



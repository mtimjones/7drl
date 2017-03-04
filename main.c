#include "7drltypes.h"

WINDOW *mainwin;

#define MS_PER_UPDATE  100

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


unsigned long long getTimestamp( void )
{
   struct timeval tv;
   unsigned long long t1;

   gettimeofday( &tv, NULL );

   t1 = ( tv.tv_sec * 1000000 ) + tv.tv_usec;

   // Convert to ms
   t1 = t1 / 1000;

   return t1;
}


int main( int argc, char *argv[] )
{
   int Y, X;
   unsigned long long curTime;

   srand( time( NULL ) );

   Y = getRand( Y_MAP_MAX );
   X = getRand( X_MAP_MAX );

   MapInit( Y, X );

   win_startup( );

   win_update( Y, X );

   curTime = getTimestamp( );

   double previous = getTimestamp( );
   double lag = 0.0;

   while ( 1 )
   {
      double current = getTimestamp( );
      double elapsed = current - previous;

      previous = current;
      lag += elapsed;

      get_input( &Y, &X );

      while ( lag > MS_PER_UPDATE )
      {
         // Update
         win_map_viewport( Y, X );
         win_update( Y, X );
         wrefresh( mainwin );

         lag -= MS_PER_UPDATE;
      }
   }

   win_shutdown( );

   return 0;
}


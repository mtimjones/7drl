#include "7drltypes.h"

void get_input( void )
{
   int c;
   int Y, X;
   int dy=0, dx=0;

   extern WINDOW *mainwin;

   GetPlayerLocation( &Y, &X );

   c = wgetch( mainwin );

   if ( c != ERR )
   {
      if ( (char)c == 'k' )
      {
         dy=-1;
      }
      else if ( (char)c == 'j' )
      {
         dy=1;
      }
      else if ( (char)c == 'h' )
      {
         dx=-1;
      }
      else if ( (char)c == 'l' )
      {
         dx=1;
      }

      if ( map_get_item( Y+dy, X+dx )  == ' ' )
      {
         map_move_item( Y, X, dy, dx );
         Y+=dy; X+=dx;
         SetPlayerLocation( Y, X );
      }
      else
      {
         // @TODO: We're either hitting a wall, mountain, or attacking.
      }
   }

   return;
}


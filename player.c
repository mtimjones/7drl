// Player functions file.

#include "7drltypes.h"

static int Player_Y, Player_X;

void GetPlayerLocation( int *Y, int *X )
{
   *Y = Player_Y;
   *X = Player_X;

   return;
}

void SetPlayerLocation( int Y, int X )
{
   Player_Y = Y;
   Player_X = X;

   return;
}

void PlayerInit( void )
{
   int middleY, middleX;
   const int Ylimit = 40;
   const int Xlimit = 60;

   middleY = ( Y_MAP_MAX / 2 ) - ( Ylimit / 2 );
   middleX = ( X_MAP_MAX / 2 ) - ( Xlimit / 2 );

   do {
      Player_Y = middleY + getRand( Ylimit );
      Player_X = middleX + getRand( Xlimit );
   } while ( !IsAreaClear( Player_Y, Player_X ) );

   map_place_item( Player_Y, Player_X, '@' );

   return;
}

void PlayerAttack( int dy, int dx )
{

   // TODO.

   return;
}

void PlayerMove( void )
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
         PlayerAttack( dy, dx );
      }
   }

   return;
}


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

// Map functions
#include "7drltypes.h"

static char map[ Y_MAP_MAX ][ X_MAP_MAX ];

int IsAreaClear( int centerY, int centerX )
{
   int Y, X;

   for ( Y = ( centerY - 1 ) ; Y <= ( centerY + 1 ) ; Y++ )
   {
      for ( X = ( centerX - 1 ) ; X <= ( centerX + 1 ) ; X++ )
      {
         if ( map_get_item( Y, X ) != SPACE_ICON ) return 0;
      }
   }

   return 1;
}

int ObstacleCreate( void )
{
   int LocX, LocY, X, Y;
   int SizeX, SizeY;
   const int LimitX = 6, LimitY = 3;

   LocX = getRand( ( X_MAP_MAX - 2 - LimitX ) ) + 1;
   LocY = getRand( ( Y_MAP_MAX - 2 - LimitY ) ) + 1;

   SizeX = getRand( LimitX ) + 2;
   SizeY = getRand( LimitY ) + 2;

   for ( Y = 0 ; Y < SizeY ; Y++ )
   {
      for ( X = 0 ; X < SizeX ; X++ )
      {
         map[ Y + LocY ][ X + LocX ] = TREE_ICON;
      }
   }

   return ( SizeY * SizeX );
}

void MapInit( void )
{
   int X, Y;
   int Density = 0;

   for ( Y = 0 ; Y < Y_MAP_MAX ; Y++ )
   {
      for ( X = 0 ; X < X_MAP_MAX ; X++ )
      {
         if ( Y == 0 || X == 0 )
         {
            map[ Y ][ X ] = WALL_ICON;
         }
         else if ( ( Y == ( Y_MAP_MAX - 1 ) ) || ( X == ( X_MAP_MAX - 1 ) ) )
         {
            map[ Y ][ X ] = WALL_ICON;
         }
         else
         {
            map[ Y ][ X ] = SPACE_ICON;
         }
      }
   }

   // Add noise to the map.
   while ( Density < ( ( Y_MAP_MAX * X_MAP_MAX ) / 3 ) )
   {
      Density += ObstacleCreate( );
   }

   return;
}

char vp_map( int y, int x )
{
   if ( ( y < 0 ) || ( x < 0 ) )
   {
      return ABYSS_ICON;
   }
   else if ( ( y >= Y_MAP_MAX ) || ( x >= X_MAP_MAX ) )
   {
      return ABYSS_ICON;
   }
   else
   {
      return map[ y ][ x ];
   }
}

void win_map_viewport( int Y, int X )
{
   int x, y;
   int vp_y;
   int vp_x;

   extern WINDOW *mainwin;

   vp_y = Y - ( ( MAP_NLINES - 2 ) / 2 );

   for ( y = 1 ; y < ( MAP_NLINES - 1 ) ; y++ )
   {
      vp_x = X - ( ( MAP_NCOLS - 2 ) / 2 );
      for ( x = 1 ; x < ( MAP_NCOLS - 1 ) ; x++ )
      {
         mvwprintw( mainwin, y, x, "%c", vp_map( vp_y, vp_x ) );
         vp_x++;
      }
      vp_y++;
   }

   return;
}

char map_get_item( int Y, int X )
{
   return map[ Y ][ X ];
}

void map_move_item( int Y, int X, int dy, int dx )
{
   map[ Y+dy ][ X+dx ] = map[ Y ][ X ];
   map[ Y ][ X ] = SPACE_ICON;

   return;
}

void map_place_item( int Y, int X, char item )
{
   map[ Y ][ X ] = item;

   return;
}


// misc.c -- miscellaneous functions

#include "7drltypes.h"
#include <math.h>

int distance( int y1, int x1, int y2, int x2 )
{
   return ( int ) sqrt( ( double ) ( ( ( x2 - x1 ) * ( x2 - x1 ) ) +
                                     ( ( y2 - y1 ) * ( y2 - y1 ) ) ) );
}


int DistanceToPlayer( int y1, int x1 )
{
   int x, y;

   GetPlayerLocation( &y, &x );

   return distance( y, x, y1, x1 );
}

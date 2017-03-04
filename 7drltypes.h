// Types for the 7drl

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <curses.h>

#define MAP_NLINES      23
#define MAP_NCOLS       69

#define NLINES      (  7 + MAP_NLINES )
#define NCOLS       ( 20 + MAP_NCOLS )

#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

#define X_MAP_MAX    1000
#define Y_MAP_MAX    500


// Types for the 7drl

#ifndef __7DRLTYPES_H
#define __7DRLTYPES_H

// Common headers used by all source files
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <curses.h>

// Size of the map viewport
#define MAP_NLINES      23
#define MAP_NCOLS       69

// Size of the UI
#define NLINES      (  7 + MAP_NLINES )
#define NCOLS       ( 20 + MAP_NCOLS )

// RNG Functions 
#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

// Size of the physical map
#define X_MAP_MAX    1000
#define Y_MAP_MAX    500

// 20Hz Game Loop
#define MS_PER_UPDATE  50

#endif // __7DRLTYPES_H

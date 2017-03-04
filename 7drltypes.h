// Types for the 7drl

#ifndef __7DRLTYPES_H
#define __7DRLTYPES_H

// Common headers used by all source files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <curses.h>
#include <strings.h>

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

// 50Hz Game Loop (50FPS)
#define MS_PER_FRAME  20

// Max number of window messages
#define MAX_MESSAGES   ( NCOLS - MAP_NCOLS - 2 )

// Function prototypes
void win_map_viewport( int Y, int X );
void init_messages( void );
char *get_message( int pos );
void MapInit( int Py, int Px );
void get_input( int *Y, int *X );
char map_get_item( int Y, int X );
void map_move_item( int Y, int X, int dy, int dx );
unsigned long long getTimestamp( void );

#endif // __7DRLTYPES_H

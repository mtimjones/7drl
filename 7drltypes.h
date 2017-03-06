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
#include <string.h>

#include "ces.h"

// Size of the map viewport
#define MAP_NLINES      33
#define MAP_NCOLS       69

// Size of the UI
#define NLINES      (  7 + MAP_NLINES )
#define NCOLS       ( 20 + MAP_NCOLS )

// RNG Functions 
#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

// Size of the physical map
#define X_MAP_MAX    800
#define Y_MAP_MAX    400

// 50Hz Game Loop (50FPS)
#define MS_PER_FRAME  20

// Max number of window messages
#define MAX_MESSAGES   ( NLINES - MAP_NLINES - 1 )

// Items
#define WALL_ICON         '+'
#define TREE_ICON         '^'
#define PLAYER_ICON       '@'
#define PROTECTOR_ICON    'P'
#define ARTIFACT_ICON     '*'
#define ANIMAL_ICON       'a'
#define SPACE_ICON        ' '
#define ABYSS_ICON        '~'
#define SHOT_ICON         '.'
#define SLING_ICON        '?'

#define SLING_BONUS_ITEMS     20

// Function prototypes
void win_map_viewport( int Y, int X );
void init_messages( void );
char *get_message( int pos );
void MapInit( void );
void get_input( void );
char map_get_item( int Y, int X );
void map_move_item( int Y, int X, int dy, int dx );
void map_place_item( int Y, int X, char item );
unsigned long long getTimestamp( void );
void add_message( char *message );
char *get_message( int pos );
int IsAreaClear( int centerY, int centerX );

void PlayerInit( void );
void GetPlayerLocation( int *Y, int *X );
void SetPlayerLocation( int Y, int X );
void PlayerAttack( int dy, int dx );
void PlayerMove( void );
void EmitPlayerStats( void );

void InitEntities( void );
int  getEntityAt( int Y, int X );
void destroyEntity( unsigned int entity );
unsigned int createAnimal( void );

void SystemMovementFunction( void );

int DistanceToPlayer( int y1, int x1 );

#endif // __7DRLTYPES_H

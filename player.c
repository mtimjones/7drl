// Player functions file.

#include "7drltypes.h"
#include "player.h"

static Player_type player;

void GetPlayerLocation( int *Y, int *X )
{
   *Y = player.LocationY;
   *X = player.LocationX;

   return;
}

void SetPlayerLocation( int Y, int X )
{
   player.LocationY = Y;
   player.LocationX = X;

   return;
}

void PlayerInit( void )
{
   int middleY, middleX;
   const int Ylimit = 40;
   const int Xlimit = 60;

   // Init Player Stats
   player.Level = 1;
   player.XP = 0;
   player.XPToNextLevel = 20;
   player.Health = 20;
   player.MaxHealth = player.Health;
   player.ArtifactsHeld = 0;
   player.Strength = 1;

   middleY = ( Y_MAP_MAX / 2 ) - ( Ylimit / 2 );
   middleX = ( X_MAP_MAX / 2 ) - ( Xlimit / 2 );

   do {
      player.LocationY = middleY + getRand( Ylimit );
      player.LocationX = middleX + getRand( Xlimit );
   } while ( !IsAreaClear( player.LocationY, player.LocationX ) );

   map_place_item( player.LocationY, player.LocationX, PLAYER_ICON );

   return;
}

void EmitPlayerStats( void )
{
   extern WINDOW *mainwin;

   mvwprintw( mainwin,  1, (MAP_NCOLS)+1, "The Forest" );

   mvwprintw( mainwin,  3, (MAP_NCOLS)+1, "Player Stats" );
   mvwprintw( mainwin,  4, (MAP_NCOLS)+1, " Level:        %2d", player.Level );
   mvwprintw( mainwin,  5, (MAP_NCOLS)+1, " XP:          %3d", player.XP );
   mvwprintw( mainwin,  6, (MAP_NCOLS)+1, " XPtoNextLvl: %3d", player.XPToNextLevel );

   mvwprintw( mainwin,  8, (MAP_NCOLS)+1, " Health:      %3d", player.Health );
   mvwprintw( mainwin,  9, (MAP_NCOLS)+1, " Strength:     %2d", player.Strength );

   mvwprintw( mainwin, 11, (MAP_NCOLS)+1, " Artifacts:    %2d", player.ArtifactsHeld );

   return;
}

void PlayerAddXP( int XP )
{
   player.XP += XP;

   if ( player.XP >= player.XPToNextLevel )
   {
      add_message( "Your level has increased.\0" );
      player.Level++;
      player.XPToNextLevel += ( player.XPToNextLevel * 1.1 ); // ????
      player.MaxHealth *= 1.1;
   }

   // @TODO: Provide the player with a small health bonus.

   return;
}


void PlayerAttack( int Y, int X )
{
   char item;
   int  entity;

   extern World world;

   item = map_get_item( Y, X );

   switch( item )
   {
      case ANIMAL_ICON:
         // Get the entity at this location.
         entity = getEntityAt( Y, X );

         // Attack
         world.health[ entity ].Health -= player.Strength;

         // Did we kill it?
         if ( world.health[ entity ].Health <= 0 )
         {
            add_message( "You've killed the animal.\0" );
            PlayerAddXP( world.XPValue[ entity ].XP );
            destroyEntity( entity );
            map_place_item( Y, X, SPACE_ICON );
            createAnimal( );
         }
         break;

      default:
         break;
   }

   return;
}

void PlayerMove( void )
{
   int c;
   int Y, X;
   int dy=0, dx=0;
   int moved = 0;

   extern WINDOW *mainwin;

   GetPlayerLocation( &Y, &X );

   c = wgetch( mainwin );

   if ( c != ERR )
   {
      if ( (char)c == 'w' )
      {
         dy=-1;
         moved = 1;
      }
      else if ( (char)c == 's' )
      {
         dy=1;
         moved = 1;
      }
      else if ( (char)c == 'a' )
      {
         dx=-1;
         moved = 1;
      }
      else if ( (char)c == 'd' )
      {
         dx=1;
         moved = 1;
      }

      if ( moved )
      {
         if ( map_get_item( Y+dy, X+dx )  == SPACE_ICON )
         {
            map_move_item( Y, X, dy, dx );
            Y+=dy; X+=dx;
            SetPlayerLocation( Y, X );
         }
         else
         {
            // @TODO: We're either hitting a wall, mountain, or attacking.
            PlayerAttack( Y+dy, X+dx );
         }
      }
   }

   return;
}


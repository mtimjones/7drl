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

void GetPlayerdYdX( int *dY, int *dX )
{
   *dY = player.dY;
   *dX = player.dX;

   return;
}

void IncrementProjectiles( void )
{
   player.ShotsAvailable++;

   return;
}

int GetShotDistance( void )
{
   return player.SlingRange;
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
   player.SlingRange = 8;
   player.ShotsAvailable = 1;
   player.ShotsActive = 0;

   player.dY = player.dX = 0;

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
   mvwprintw( mainwin,  9, (MAP_NCOLS)+1, " Sling Range:  %2d", player.SlingRange );
   mvwprintw( mainwin, 10, (MAP_NCOLS)+1, " Shots Avail:  %2d", player.ShotsAvailable );

   mvwprintw( mainwin, 12, (MAP_NCOLS)+1, " Artifacts:    %2d", player.ArtifactsHeld );

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
         world.health[ entity ].Health -= player.Level;

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

      case SLING_ICON:
         // Player found a sling bonus.
         if ( getRand( 100 ) > 90 )
         {
            // Got a sling shot bonus.
            player.ShotsAvailable++;
            add_message( "Sling shots has increased." );
         }
         else
         {
            // Got a sling range bonus.
            player.SlingRange++;
            add_message( "Sling range has increased." );
         }
         map_place_item( Y, X, SPACE_ICON );
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
   int moved = 0;

   extern WINDOW *mainwin;

   GetPlayerLocation( &Y, &X );

   c = wgetch( mainwin );

   if ( c != ERR )
   {
      // Key hit
      if ( (char)c == 'w' )
      {
         player.dY = -1; player.dX = 0;
         moved = 1;
      }
      else if ( (char)c == 's' )
      {
         player.dY = 1; player.dX = 0;
         moved = 1;
      }
      else if ( (char)c == 'a' )
      {
         player.dX = -1; player.dY = 0;
         moved = 1;
      }
      else if ( (char)c == 'd' )
      {
         player.dX = 1; player.dY = 0;
         moved = 1;
      }
      else if ( (char)c == ' ' )
      {
         if ( ( player.ShotsAvailable ) && ( player.dY != player.dX ) )
         {
            player.ShotsAvailable--;
            player.ShotsActive++;
            createProjectile( );
         }
      }

      if ( moved )
      {
         if ( map_get_item( Y+player.dY, X+player.dX ) == SPACE_ICON )
         {
            map_move_item( Y, X, player.dY, player.dX );
            Y += player.dY; X += player.dX;
            SetPlayerLocation( Y, X );
         }
         else
         {
            // @TODO: We're either hitting a wall, mountain, or attacking.
            PlayerAttack( Y+player.dY, X+player.dX );
         }
      }
   }

   return;
}


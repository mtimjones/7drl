// Player functions file.

#include "7drltypes.h"
#include "player.h"

static Player_type player;

int GetPlayerLocationY( void )
{
   return player.LocationY;
}

int GetPlayerLocationX( void )
{
   return player.LocationX;
}

void SetPlayerLocation( int Y, int X )
{
   player.LocationY = Y;
   player.LocationX = X;

   return;
}

int GetPlayerLocationdY( void )
{
   return player.dY;
}

int GetPlayerLocationdX( void )
{
   return player.dX;
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

int GetShotPower( void )
{
   return player.SlingPower;
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
   player.SlingPower = 5;
   player.ShotsAvailable = 1;

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
   mvwprintw( mainwin,  9, (MAP_NCOLS)+1, " Max Health:  %3d", player.MaxHealth );

   mvwprintw( mainwin, 11, (MAP_NCOLS)+1, " Shots Avail:  %2d", player.ShotsAvailable );
   mvwprintw( mainwin, 12, (MAP_NCOLS)+1, " Sling Range:  %2d", player.SlingRange );
   mvwprintw( mainwin, 13, (MAP_NCOLS)+1, " Sling Power:  %2d", player.SlingPower );

   mvwprintw( mainwin, 15, (MAP_NCOLS)+1, " Artifacts:    %2d", player.ArtifactsHeld );

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

void PlayerDecreaseHealth( int Health )
{
   player.Health -= Health;
   if ( player.Health <= 0 )
   {
      // You have died.
      // GameEnd = 1;
   }

   return;
}

void PlayerAddHealth( int health )
{
   player.Health += health;
   if (player.Health > player.MaxHealth )
   {
      player.Health = player.MaxHealth;
   }

   return;
}

void Attack( int Attack, int Y, int X, char source )
{
   char item;
   int entity;

   extern World world;

   item = map_get_item( Y, X );

   switch( item )
   {
      case ANIMAL_ICON:
      case PROTECTOR_ICON:
         entity = getEntityAt( Y, X );

         // Attack
         world.health[ entity ].Health -= Attack;

         // Did we kill it?
         if ( world.health[ entity ].Health <= 0 )
         {
            if ( item == ANIMAL_ICON )
            {
               add_message( "You've killed the animal." );
               PlayerAddHealth( ( getRand( 4 ) + 2 ) );
            }
            else if ( item == PROTECTOR_ICON )
            {
               add_message( "You've killed the protector." );
               PlayerAddHealth( ( getRand( 6 ) + 4 ) );
            }

            PlayerAddXP( world.XPValue[ entity ].XP );
            destroyEntity( entity );
            map_place_item( Y, X, SPACE_ICON );
            if ( item == ANIMAL_ICON ) createAnimal( );
         }
         else
         {
            if ( item == ANIMAL_ICON )
            {
               add_message( "You hit the animal." );
            }
            else if ( item == PROTECTOR_ICON )
            {
               add_message( "You hit the protector." );
            }
         }

         break;

      case BERRIES_ICON:
      case SLING_ICON:
         // Destroyed the item.
         map_place_item( Y, X, SPACE_ICON );
         break;

      default:
         // Hit a wall, tree, etc.  No effect.
         break;
   }

   return;
}


void PlayerCollision( int Y, int X )
{
   char item;
   int  entity;

   item = map_get_item( Y, X );

   switch( item )
   {
      case ANIMAL_ICON:
      case PROTECTOR_ICON:
         Attack( player.Level, Y, X, PLAYER_ICON );
         break;

      case SLING_ICON:
         {
            // Player found a sling bonus.
            int bonus = getRand( 100 );
            if ( bonus >= 90 )
            {
               // Got a sling shot bonus.
               player.ShotsAvailable++;
               add_message( "Sling shots has increased." );
            }
            else if ( bonus >= 80 )
            {
               // Got a sling power bonus.
               player.SlingPower++;
               add_message( "Sling power has increased." );
            }
            else
            {
               // Got a sling range bonus.
               player.SlingRange++;
               add_message( "Sling range has increased." );
            }

            map_place_item( Y, X, SPACE_ICON );

         }
         break;

      case BERRIES_ICON:
         PlayerAddHealth( BERRIES_HEALTH );
         add_message( "You eat the berries." );
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

   Y = GetPlayerLocationY( );
   X = GetPlayerLocationX( );

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
            // We're either hitting a wall, mountain, or attacking.
            PlayerCollision( Y+player.dY, X+player.dX );
         }
      }
   }

   return;
}


// Systems for the CES.

#include "7drltypes.h"

void SystemMovementFunction( )
{
   unsigned int entity;
   unsigned int mask;
   int dy, dx;

   extern World world;

   // Animate the projectiles.
   mask =  COMPONENT_MOVEMENT | COMPONENT_TARGET;
   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( ( world.mask[ entity ] & mask ) == mask )
      {
         // If state matches speed, time to move.
         if ( ++world.movement[ entity ].State >= world.movement[ entity ].Speed )
         {
            if ( ++world.target[ entity ].distance >= GetShotDistance( ) )
            {
               map_place_item( world.location[ entity ].Y, world.location[ entity ].X, SPACE_ICON );
               destroyEntity( entity );
               IncrementProjectiles( );
            }
            else
            {
               int y, x;

               // Reset the speed state.
               world.movement[ entity ].State = 0;

               // Next position of the projectile.
               y = world.location[ entity ].Y + world.target[ entity ].dY;
               x = world.location[ entity ].X + world.target[ entity ].dX;

               // If the next location is vacant, move the projectile.
               if ( map_get_item( y, x ) == SPACE_ICON )
               {
                  // Move the projectile.
                  map_move_item( world.location[ entity ].Y, world.location[ entity ].X, 
                                 world.target[ entity ].dY, world.target[ entity ].dX );
                  world.location[ entity ].Y = y;
                  world.location[ entity ].X = x;
               }
               else
               {
                  // Allow the projectile to attack the item on the map.
                  Attack( world.attack[ entity ].Attack, y, x, PROJECTILE_ICON );

                  // Remove the projectile from the map.
                  map_place_item( world.location[ entity ].Y, world.location[ entity ].X, SPACE_ICON );
                  destroyEntity( entity );
                  IncrementProjectiles( );
               }
            }
         }
      }
   }

   // Animate the animals.
   mask = COMPONENT_MOVEMENT | COMPONENT_ANIMAL;
   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( ( world.mask[ entity ] & mask ) == mask )
      {
         if (DistanceToPlayer( world.location[ entity ].Y, 
                               world.location[ entity ].X ) > 50 ) continue;

         // If state matches speed, time to move.
         if ( ++world.movement[ entity ].State >= world.movement[ entity ].Speed )
         {
            // Reset the speed state.
            world.movement[ entity ].State = 0;

            // Animals move randomly.
            dy = ( getRand( 3 ) - 1 );
            dx = ( getRand( 3 ) - 1 );

            if ( map_get_item( ( world.location[ entity ].Y + dy ),
                               ( world.location[ entity ].X + dx ) ) == SPACE_ICON )
            {
               map_move_item( world.location[ entity ].Y,
                              world.location[ entity ].X, dy, dx );

               world.location[ entity ].Y += dy;
               world.location[ entity ].X += dx;
            }
         }
      }

   }

   // Animate the protectors.
   mask = COMPONENT_MOVEMENT | COMPONENT_PROTECTOR;
   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( ( world.mask[ entity ] & mask ) == mask )
      {
         if (DistanceToPlayer( world.location[ entity ].Y, 
                               world.location[ entity ].X ) > 20 ) continue;

         // If state matches speed, time to move.
         if ( ++world.movement[ entity ].State >= world.movement[ entity ].Speed )
         {
            char target;

            // Reset the speed state.
            world.movement[ entity ].State = 0;

            // Note, we build a path from player to protector because it's easier to
            // then figure out the next step for the protector (end of the list).
            MoveTowardsPlayer( 
                               GetPlayerLocationY( ), 
                               GetPlayerLocationX( ), 
                               world.location[ entity ].Y, 
                               world.location[ entity ].X,
                               &dy, &dx );

            target = map_get_item( ( world.location[ entity ].Y + dy ),
                                    ( world.location[ entity ].X + dx ) );

            if ( target == SPACE_ICON )
            {
               map_place_item( world.location[ entity ].Y, world.location[ entity ].X, 
                               SPACE_ICON );

               world.location[ entity ].Y += dy;
               world.location[ entity ].X += dx;

               map_place_item( world.location[ entity ].Y, world.location[ entity ].X, 
                               PROTECTOR_ICON );

            }
            else if ( target == PLAYER_ICON )
            {
               // Attack the player...
               PlayerDecreaseHealth( world.attack[ entity ].Attack );
               add_message( "Protector attacks." );
            }
         }
      }
   }

   return;
}


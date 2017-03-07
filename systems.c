// Systems for the CES.

#include "7drltypes.h"

void SystemMovementFunction( )
{
   unsigned int entity;
   unsigned int mask;
   int dy, dx;

   extern World world;

   // Animate the projectiles.
   mask = COMPONENT_TARGET;
   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      int y, x;

      if ( ( world.mask[ entity ] & mask ) == mask )
      {
         y = world.location[ entity ].Y + world.target[ entity ].dY;
         x = world.location[ entity ].X + world.target[ entity ].dX;
         if ( map_get_item( y, x ) == SPACE_ICON )
         {
            // Move the projectile.
            map_move_item( world.location[ entity ].Y, world.location[ entity ].X,
                           world.target[ entity ].dY, world.target[ entity ].dX );
            world.location[ entity ].Y += world.target[ entity ].dY;
            world.location[ entity ].X += world.target[ entity ].dX;
         }
         else
         {
           // we've hit something, what was it?
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

   return;
}


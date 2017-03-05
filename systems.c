// Systems for the CES.

#include "7drltypes.h"

void SystemMovementFunction( )
{
   unsigned int entity;
   unsigned int mask = COMPONENT_MOVEMENT | COMPONENT_ANIMAL;
   int dy, dx;

   extern World world;

   // Animate the animals first.
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

   return;
}


// ces.c -- Component Entity System implementation.

#include "7drltypes.h"

World world;

unsigned int createEntity( )
{
   unsigned int entity;

   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      if ( world.mask[ entity ] == COMPONENT_NONE )
      {
         return entity;
      }
   }

   return MAX_ENTITIES;
}

void destroyEntity( unsigned int entity )
{
   world.mask[ entity ] = COMPONENT_NONE;

   return;
}

unsigned int createAnimal( )
{
   int entity;
   int y, x;

   entity = createEntity( );

   if ( entity < MAX_ENTITIES )
   {

      world.mask[ entity ] = COMPONENT_LOCATION  |
                             COMPONENT_HEALTH    |
                             COMPONENT_XPVALUE   |
                             COMPONENT_ANIMAL    |
                             COMPONENT_MOVEMENT;

      // Place the animal in the environment.
      do {
         y = getRand( Y_MAP_MAX );
         x = getRand( X_MAP_MAX );
      } while ( !IsAreaClear( y, x ) );

      world.location[ entity ].Y = y;
      world.location[ entity ].X = x;

      world.movement[ entity ].Speed = 10 + getRand( 8 );
      world.movement[ entity ].State = 0;

      world.health[ entity ].Health = 5;
      world.XPValue[ entity].XP = 5;

      map_place_item( y, x, ANIMAL_ICON );
   }

   return entity;
}


unsigned int createProtector( )
{
   int entity;
   int y, x;

   entity = createEntity( );

   if ( entity < MAX_ENTITIES )
   {

      world.mask[ entity ] = COMPONENT_LOCATION  |
                             COMPONENT_HEALTH    |
                             COMPONENT_ATTACK    |
                             COMPONENT_XPVALUE   |
                             COMPONENT_PROTECTOR |
                             COMPONENT_MOVEMENT;

      // Place the animal in the environment.
      do {
         y = getRand( Y_MAP_MAX );
         x = getRand( X_MAP_MAX );
      } while ( !IsAreaClear( y, x ) );

      world.location[ entity ].Y = y;
      world.location[ entity ].X = x;

      world.movement[ entity ].Speed = 3 + getRand( 2 );
      world.movement[ entity ].State = 0;

      world.health[ entity ].Health = 20;
      world.XPValue[ entity].XP = 20;

      map_place_item( y, x, PROTECTOR_ICON );
   }

   return entity;
}

void InitEntities( )
{
   unsigned int entity;

   // Initialize the entities to null
   for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
   {
      destroyEntity( entity );
   }

   // Create some number of animals.
   for ( entity = 0 ; entity < NUMBER_OF_ANIMALS ; entity++ )
   {
      createAnimal( );
   }

   // Create some number of protectors.
   for ( entity = 0 ; entity < NUMBER_OF_PROTECTORS ; entity++ )
   {
      createProtector( );
   }

   return;
}



// ces.c -- Component Entity System implementation.

#include "7drltypes.h"
#include "ces.h"

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

      world.mask[ entity ] = COMPONENT_LOCATION   |
                             COMPONENT_HEALTH     |
                             COMPONENT_MOBILE;

      // Place the animal in the environment.
      do {
         y = getRand( Y_MAP_MAX );
         x = getRand( X_MAP_MAX );
      } while ( !IsAreaClear( y, x ) );

      world.location[ entity ].Y = y;
      world.location[ entity ].X = x;

      world.health[ entity ].Health = 5;
      world.XPValue[ entity].XP = 5;

      map_place_item( y, x, ANIMAL_ICON );
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
   for ( entity = 0 ; entity < 30 ; entity++ )
   {
      createAnimal( );
   }

   // Create some number of protectors.

   return;
}


void SystemAnimateProtectors( void )
{

}

void SystemAnimateAnimals( void )
{

}


// ces.h, Component-Entity-System header

#ifndef __COMPONENT_H
#define __COMPONENT_H

typedef struct ComponentLocation
{
   double Y;
   double X;

} ComponentLocation;

typedef struct ComponentHealth
{
   int Health;

} ComponentHealth;

typedef struct ComponentAttack
{
   int Strength;

} ComponentAttack;

typedef struct ComponentMovement
{
   int Speed;
   int State;

} ComponentMovement;

typedef struct ComponentXPValue
{
   int XP;

} ComponentXPValue;

typedef struct ComponentTarget
{
   int dY;
   int dX;
   int distance;

} ComponentTarget;

typedef enum
{
   COMPONENT_NONE      = 0,
   COMPONENT_LOCATION  = 1 << 1,
   COMPONENT_HEALTH    = 1 << 2,
   COMPONENT_ATTACK    = 1 << 3,
   COMPONENT_MOVEMENT  = 1 << 4,
   COMPONENT_XPVALUE   = 1 << 5,
   COMPONENT_ANIMAL    = 1 << 6,
   COMPONENT_PROTECTOR = 1 << 7,
   COMPONENT_TARGET    = 1 << 8,

} Component;

#define NUMBER_OF_ANIMALS      40
#define NUMBER_OF_PROTECTORS   20
#define NUMBER_OF_PROJECTILES   5

#define MAX_ENTITIES   ( NUMBER_OF_ANIMALS     + \
                         NUMBER_OF_PROTECTORS  + \
                         NUMBER_OF_PROJECTILES  )

typedef struct World
{
   int mask[ MAX_ENTITIES ];

   int id[ MAX_ENTITIES ];

   ComponentLocation     location [ MAX_ENTITIES ];
   ComponentHealth       health   [ MAX_ENTITIES ];
   ComponentAttack       attack   [ MAX_ENTITIES ];
   ComponentMovement     movement [ MAX_ENTITIES ];
   ComponentXPValue      XPValue  [ MAX_ENTITIES ];
   ComponentTarget       target   [ MAX_ENTITIES ];

} World;

void InitEntities( );

#endif // __COMPONENT_H


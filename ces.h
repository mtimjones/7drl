// ces.h, Component-Entity-System header

#ifndef __COMPONENT_H
#define __COMPONENT_H

typedef struct ComponentLocation
{
   int Y;
   int X;

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

typedef enum
{
   COMPONENT_NONE       = 0,
   COMPONENT_LOCATION   = 1 << 1,
   COMPONENT_HEALTH     = 1 << 2,
   COMPONENT_ATTACK     = 1 << 3,
   COMPONENT_MOVEMENT   = 1 << 4,
   COMPONENT_XPVALUE    = 1 << 5,
   COMPONENT_ANIMAL     = 1 << 6,
   COMPONENT_PROTECTOR  = 1 << 7,

} Component;

#define NUMBER_OF_ANIMALS      40
#define NUMBER_OF_PROTECTORS   20

#define MAX_ENTITIES   ( NUMBER_OF_ANIMALS + NUMBER_OF_PROTECTORS )

typedef struct World
{
   int mask[ MAX_ENTITIES ];

   ComponentLocation     location [ MAX_ENTITIES ];
   ComponentHealth       health   [ MAX_ENTITIES ];
   ComponentAttack       attack   [ MAX_ENTITIES ];
   ComponentMovement     movement [ MAX_ENTITIES ];
   ComponentXPValue      XPValue  [ MAX_ENTITIES ];

} World;

void InitEntities( );

#endif // __COMPONENT_H


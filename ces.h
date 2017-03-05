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
   COMPONENT_MOBILE     = 1 << 4,
   COMPONENT_XPVALUE    = 1 << 5,

} Component;


#define MAX_ENTITIES   50

typedef struct World
{
   int mask[ MAX_ENTITIES ];

   ComponentLocation     location[ MAX_ENTITIES ];
   ComponentHealth       health[ MAX_ENTITIES ];
   ComponentAttack       attack[ MAX_ENTITIES ];
   ComponentXPValue      XPValue[ MAX_ENTITIES ];

} World;

void InitEntities( );

#endif // __COMPONENT_H


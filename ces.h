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

} ComponentHealth

typedef struct ComponentAttack
{
   int Strength;

} ComponentAttack;

typedef struct ComponentAppearance
{
   char Appearance;

} ComponentAppearance;

typedef enum
{
   COMPONENT_NONE       = 0,
   COMPONENT_LOCATION   = 1 << 1,
   COMPONENT_HEALTH     = 1 << 2,
   COMPONENT_ATTACK     = 1 << 3,
   COMPONENT_APPEARANCE = 1 << 4,

} Component;


#define MAX_ENTITIES   30

typedef struct World
{
   int mask[ MAX_ENTITIES ];

   ComponentLocation     location[ MAX_ENTITIES ];
   ComponentHealth       health[ MAX_ENTITIES ];
   ComponentAttack       attack[ MAX_ENTITIES ];
   ComponentAppearance   appearance[ MAX_ENTITIES ];

} World;

#endif // __COMPONENT_H


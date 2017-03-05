// player.h, types, etc.

#ifndef __PLAYER_H
#define __PLAYER_H

typedef struct Player_type
{
   int Level;
   int XP;
   int XPToNextLevel;
   int Health;
   int MaxHealth;
   int ArtifactsHeld;
   int Strength;
   int LocationY;
   int LocationX;

} Player_type;

#endif // __PLAYER_H

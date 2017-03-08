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
   int LocationY;
   int LocationX;
   int SlingRange;
   int SlingPower;
   int ShotsAvailable;

   // Last direction moved.
   int dY;
   int dX;

} Player_type;

#endif // __PLAYER_H

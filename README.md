# 7drl ("The Forest")

This repo contains the source code for a Seven Day Rogue Like entry called "The Forest."  This
is a quick attempt at a roguelike in a short time (not sure if it will be fun or not).

# Task List

- [x]  Add map generation. (Reused)

- [x]  Add ncurses-based viewport. (Reused)

- [x]  Add player input, ability to move around.

- [x]  Add a game-loop with time.

- [x]  Update the UI to permit map.

- [x]  Update the UI to permit messages.

- [ ]  Add a CES (Component Entity System) framework for entities in the world (not player).

- [ ]  Add combat system, how attack works, defense, etc.

- [ ]  XP System, XP to next level is 110% of previous level.

- [x]  Update the UI to permit stats.

- [ ]  Add Animals (health NPCs) into the world (random movement, vary speed).

- [ ]  Add Protectors, with pathfinding to attack the player.

- [ ]  Add a dynamic legend which emits a description for the items on the screen. (Stretch)

- [ ]  Add the secret door to escape.

- [ ]  Add a function for distance between objects.

- [ ]  Two types of enemies in the environment.  Animals, that can restore health and Protectors that carry artifacts (harder to kill).

- [ ]  Add A* pathfinding.

- [ ]  In the stats section, show the direction of the closest animal and protector. (Stretch)

- [ ]  Think about weapons and effects.  Need to indicate a weapon in status, text-effect when used, damage differences (area), weapon types. (Stretch)


# Dependencies

The only dependency is ncurses.

# Building and Running

The source includes a standard Makefile, so make should suffice:

```
make
./7drl
```


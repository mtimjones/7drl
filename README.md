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

- [x]  Add a CES (Component Entity System) framework for entities in the world (not player).

- [x]  Add combat system, how attack works, defense, etc.

- [x]  Add a health system (animals increase health, level increases health max, etc.).

- [x]  XP System, XP to next level is 110% of previous level.

- [x]  Update the UI to permit stats.

- [x]  Add Animals (health NPCs) into the world (random movement, vary speed).

- [ ]  Add Protectors, with pathfinding to attack the player.

- [ ]  Add a dynamic legend which emits a description for the items on the screen. (Stretch)

- [ ]  Add the secret door to escape.

- [x]  Add a function for distance to player.

- [x]  Two types of enemies in the environment.  Animals, that can restore health and Protectors that carry artifacts (harder to kill).

- [ ]  Add A* pathfinding.

- [ ]  In the stats section, show the direction of the closest animal and protector. (Stretch)

- [ ]  Add support for mouse click detection (for projectiles). (Stretch)

- [x]  Add a sling.  The sling shoots for 8 spaces (can be extended with sling bonus items).

- [x]  Add sling bonus system (90% range, 10% shot bonus).

- [ ]  Think about weapons and effects.  Need to indicate a weapon in status, text-effect when used, damage differences (area), weapon types. (Stretch)

- [ ]  Add towers that emit enemies (near the exit).  Towers can be destroyed.

- [ ]  Add ncurses color. (Stretch)

- [ ]  Add an end-game sequence where protectors appear around the exit requiring the player to kill them before escaping.


# Dependencies

The only dependency is ncurses.

# Building and Running

The source includes a standard Makefile, so make should suffice.  Your terminal window should be
large enough to fit the game window, so expand it.

```
make
./7drl
```


# Screenshot (3/6)

```
    ┌───────────────────────────────────────────────────────────────────────────────────────┐
    │                                        ^^                    ^^^^^| The Forest        │
    │                  ^^^^   ^^      ^^^^          ^^^^^^^^^^       ^^^|                   │
    │                  ^^^^   ^^    ^^^^^^^^^^      ^^^^^^^^^^          | Player Stats      │
    │            ^^    ^^^^         ^^^^^^^^^^^              ^^^^^^^    |  Level:         1 │
    │            ^^    ^^^^         ^^^^^^^^^^^              ^^^^^^^    |  XP:            0 │
    │            ^^              ^^^^^^^^^^^^^^              ^^^^^^^    |  XPtoNextLvl:  20 │
    │            ^^              ^^^^^   ^^^^^^              ^^^^^^^    |                   │
    │    ^^^^^^                  ^^^^^       ^^     ^^^^^               |  Health:       20 │
    │    ^^^^^^                  ^^^^^       ^^     ^^^^^^^             |  Sling Range:   8 │
    │                ^^^^^^                         ^^^^^^^             |  Shots Avail:   1 │
    │                ^^^^^^            ^^^^^^       ^^^^^^^^^^^^^       |                   │
    │                 ^^^^^          ^^^^^^^^       ^^^^^^^^^^^^^       |  Artifacts:     0 │
    │^^^^             ^^^^^        ^^^^^^^^^^             ^^^^^^^       |                   │
    │^^^^                   ^^^^^^ ^^^^^^^^^^                          ^|                   │
    │^^^^                   ^^^^^^ ^^^^^                               ^|                   │
    │                       ^^        @                       ^^^^^    ^|                   │
    │                                                         ^^^^^    ^|                   │
    │                                                       ^^^^^^^     |                   │
    │                                                       ^^^^^^      |                   │
    │                                 ^^^^^^^            ^^  ^^^^ ^^^   |                   │
    │                                 ^^^^^^^            ^^  ^^^^^^^^^^ |                   │
    │                                ^^^^^^^^ ^^^^^^^    ^^  ^^^^^^^^^^ |                   │
    │^^^^                          ^^^^^^^^^^ ^^^^^^^    ^^^^^^   ^^^   |                   │
    │^^^^                          ^^^^^^^   ^^^^^^      ^^^^^^         |                   │
    │^^^^    ^^^^^^                ^^        ^^^^^^      ^^^^^^   ^^^^^^|                   │
    │        ^^^^^^                ^^        ^^^^^^^^^^  ^^^^^^   ^^^^^^|                   │
    │        ^^^^^^^                           ^^^^^^^^                 |                   │
    │         ^^^^^^                   ^^      ^^^^^       ^^^^^^       |                   │
    │         ^^^^^^                   ^^      ^^^^^   ^^^ ^^^^^^       |                   │
    │^        ^^^^^^  ^^^^                             ^^^ ^^^^^^  ^^^^ | Time         339  │
    │^             ^^ ^^^^          ^^                 ^^^ ^^^^^^^^^^^^ | Location 183,421  │
    │---------------------------------------------------------------------------------------│
    │                                                                                       │
    │Welcome to The Forest.                                                                 │
    │  You're trapped in the forest, but you can escape with enough artifacts.              │
    │  Artifacts are carried by Protectors, which must be killed to attain them.            │
    │  Once you have 10 artifacts, find the door in the South to escape.                    │
    │  Move with wasd.                                                                      │
    └───────────────────────────────────────────────────────────────────────────────────────┘
```

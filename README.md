# Text-Based Adventure Game in C

## Description
This repository contains a text-based adventure game written in C. The game features a map with multiple rooms, objects, and player interactions. Navigate through rooms, pick up objects, and solve puzzles to win the game.

## Features
- Multiple rooms with unique descriptions
- Objects that can be picked up or interacted with
- Player inventory system
- Simple navigation system (North, South, East, West)
- Win condition

## How to Run
1. Clone this repository
2. Navigate to the directory containing the C file
3. Compile the C file using `gcc -o game game.c`
4. Run the compiled file using `./game`

## Game Structure
The game uses the following structures:
- `Room`: Represents a room in the game with its properties.
- `Object`: Represents an object that can be picked up or interacted with.
- `Player`: Represents the player's state in the game.

## Code Snippet
```c
typedef struct {
    char name[MAX_DESCRIPTION_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int north, south, east, west;
    int objects[3];
} Room;

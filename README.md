# PACMAN_PFminiproject2
# Pac-Man — PF Mini Project

## About the Project

We are developing a Pac-Man game using C++ and SFML 3.1.0 as part of our Programming Fundamentals mini project.

The game is built in Visual Studio 2022. We are developing it feature by feature, using separate classes and files to keep the code organized.

## Team Members

| Name | Roll Number |
|---|---|
| Kashaf Ul Iman | 26L-0011 |
| Urwa Baig | 26L-0035 |

## Technologies Used
- C++
- SFML 3.1.0
- Visual Studio 2022
- GitHub

## Project Files

- `main.cpp` — Main game window, input handling and game loop.
- `Maze.h` and `Maze.cpp` — Maze class, file loading, drawing and wall detection.
- `Player.h` and `Player.cpp` — Player position, direction and movement.
- `maze.txt` — Stores the maze layout and starting positions.

## Features Implemented

### Feature 1 — Game Window and Game Loop
- Created the game window using SFML.
- Added the main game loop.
- Added window closing functionality.
- Organized the program into input, update and drawing functions.
- Set the frame rate to 60 FPS.

### Feature 2 — Maze Loading and Rendering
- Maze is loaded from `maze.txt` instead of being written directly into the code.
- Reads the number of rows and columns from the first line.
- Stores the maze in a 2D character array.
- Uses nested loops to draw walls, pellets and power pellets.
- Uses `P` to identify the player starting position.
- Uses `G` to identify the four ghost starting positions.
- Added checks for invalid maze dimensions, incorrect symbols and missing files.

**Maze symbols:**

| Symbol | Meaning |
|---|---|
| `#` | Wall |
| `.` | Pellet |
| `O` | Power pellet |
| `-` | Empty path |
| `P` | Player start |
| `G` | Ghost start |

### Feature 3 — Player Movement
- Created a separate `Player` class using `Player.h` and `Player.cpp`.
- Added direction values from 0 to 4.
- Added arrow key and W/A/S/D controls.
- Player moves one cell every 8 frames.
- Player continues moving after the key is released.
- Added wall detection to prevent the player from entering walls.
- Direction changes towards walls are ignored.

## GitHub Commit History

The following commits document the changes made during development:

| Commit | Changes
| Updated main game loop and maze integration | Updated `main.cpp` to connect the game loop with maze loading and rendering. |
| Implemented maze loading and rendering | Added `Maze.cpp`, `Maze.h` and `maze.txt` to load and display the maze. |
| Added Player class | Created `Player.h` and `Player.cpp` for player position, direction and movement functions. |
| Integrated player movement | Updated `main.cpp` to handle keyboard input, player updates and drawing. |
| Added wall detection declaration | Updated `Maze.h` with the `isWall()` function. 
| Implemented wall detection | Updated `Maze.cpp` to check whether a position is a wall or outside the maze boundaries. |
| Added project documentation | Updated this README with the project details, features and development history. |

## Running the Project

1. Open `PacMan.sln` in Visual Studio 2022.
2. Make sure the configuration is set to Debug and x64.
3. Ensure SFML 3.1.0 is configured correctly.
4. Make sure `maze.txt` is available in the game's working directory.
5. Build the solution.
6. Run the game using Ctrl + F5.

## Current Progress

Features 1, 2 and 3 have been implemented and tested.

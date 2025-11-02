# Lightcycle - Terminal Version

This is a terminal-based rendition of the classic **Snake/Tron Lightcycle** concept, developed as a two-player game project.  

## Game Overview
- The game features **two snakes**, each controlled by a different player.  
- Player 1 uses **WASD** keys, and Player 2 uses the **arrow keys**.  
- Each snake moves around the board, leaving a trail behind.  
- If a snake's head collides with the other snake or the walls, that player **loses**.  
- The game continues until one snake remains or both collide (draw).  

## How to Play
1. Run the game in your terminal.  
2. Player 1 moves with **WASD**; Player 2 moves with **arrow keys**.  
3. Avoid hitting the other snake or walls.  
4. The last snake standing wins!  

## Features
- Two-player gameplay in the terminal  
- Real-time movement using **ncurses**  
- Collision detection between snakes and walls  
- Simple, clear terminal display  

## Requirements
- C compiler (clang recommended for the Makefile)  
- **ncurses** library installed  
- Terminal or command-line interface  

## How to Run
```bash
make
./lightcycle

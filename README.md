# Gaming Hub
A C++ console-based gaming collection featuring three classic games: Rock Paper Scissors, Snake, and Tic Tac Toe. The application includes score tracking and game history functionality.


## Features
- Multiple game options in a single application
- Score tracking system
- Game history logging
- Simple console-based user interface
- Object-oriented design with inheritance


## Games Available

### Snake Game
- Classic snake movement mechanics
- Fruit collection for scoring
- Wall collision detection
- Score tracking
- Controls: W (Up), S (Down), A (Left), D (Right), X (Exit)

### Rock Paper Scissors
- Player vs Computer gameplay
- Score tracking for wins/losses/ties
- Exit option available during gameplay

### Tic Tac Toe
- Two-player gameplay
- Board validation
- Win detection for rows, columns, and diagonals
- Draw detection


## Requirements
- C++ compiler with C++11 support or higher
- Windows operating system (due to conio.h usage)
- Standard C++ libraries


## Dependencies
- iostream
- cstdlib
- ctime
- vector
- conio.h
- chrono
- thread
- fstream


## Installation
1. Clone or download the source code
2. Compile the code using a C++ compiler:
```bash
g++ -o gamingHub main.cpp
```
3. Run the executable:
```bash
./gamingHub
```

## Usage
1. Launch the application
2. Select a game option from the menu:
   - Enter 1 for Rock Paper Scissors
   - Enter 2 for Snake Game
   - Enter 3 for Tic Tac Toe
   - Enter 4 to view previous game scores


## Score Tracking
- Scores are automatically saved after each game session
- Game history is stored in gamingHub.txt
- History includes date, time, and scores for each game

## File Structure
- main.cpp: Main source code file
- gamingHub.txt: Score history file (automatically created)


## Class Structure
- Game: Abstract base class for all games
- SnakeGame: Implementation of Snake game
- RockPaperScissors: Implementation of Rock Paper Scissors game
- TicTacToe: Implementation of Tic Tac Toe game


## Known Limitations
- Console-based interface only
- Windows-specific due to conio.h usage
- Single session scoring system
- No configuration options for game parameters


## Future Improvements
- Cross-platform compatibility
- Configurable game settings
- Enhanced user interface
- Additional games
- Player profiles and persistent high scores
- Multiplayer networking capabilities

# **MiniMax algorithm on Tic-Tac-Toe**
Implementation of the classic game (Tic-Tac-Toe) using the MiniMax algorithm to optimize plays made by the computer.

## **Content Board**
- [Description](#description)
- [Features](#features)
- [Running The Project](#runningtheproject)
- [MiniMax Algorithm](#minimaxalgorithm)
- [Next Steps](#nextsteps)

## **Description**
Tic-Tac-Toe is a board game for two players, where each of the players tries to align three symbols on a line ('X' for player one and 'O' for player two). This implementation uses the MiniMax Algorithm to make the computer only make the most optimized plays, making it a challenging opponent.

## **Features**
- **Game Modes:** Play against another player or a computer. Computer Vs Computer mode was also implemented.
- **Artifical Intelligence:** The computer uses the MiniMax algorithm to make the most optimal plays.
- **Simple interface:** The program runs on a terminal console, having a simple and easy to read interface.
- **Tecnologys:** Project made on the C language using libraries (besisdes the usual ones) such as <math.h>, <time.h>, <unistd.h> and <ctype.h>.


## **Running The Project**
1. **Clone the repository:**
    git clone git@github.com:ricas28/Tic-Tac-Toe-MiniMax-.git
2. **Change directory:**
    cd Tic-Tac-Toe-MiniMax-/
3. **Compile:**
    gcc -o main Board.c Menu.c Tic-Tac-Toe.c MiniMax.c main.c -lm
4. **Run:**
    ./main
5. **Play:**
    The starting menu will be presented and the user can decide what game mode to play.

## **MiniMax Algorithm**
MiniMax is a search algorithm used for finding the best play for a two player game on a current game state. It explores all possible moves to make, and evaluates them until and end game condition is found. This algorithm assumes that the other player will also make the most optimal plays.
- **Maximizes** the score of the user that is playing.
- **Minimizes** the score of the opponent.
- This project also implements the **Alpha-Beta pruning** method to optimize the evaltuation process, ignoring some useless branches.

## **Next Steps**
- Implementing a graphical version of the game.
- Add a difficulty setting for the computer.
- Creating a more user friendly interface.



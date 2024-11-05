/**
 * Interface for Tic-Tac-Toe program.
 */
#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include "Board.h"

/** Constants for players. */
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define EMPTY '.'

/** Constants for logic implementations. */
#define TRUE 1
#define FALSE 0

int isPlayerSymbol(char symbol);
char findWinner(Board board);
int isValidPlay(Board board, int play[]);
void switchPlayers(int *player1, int *player2);
void initializeGame();

#endif
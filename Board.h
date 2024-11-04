/**
 * Interface for board program.
 */
#ifndef __BOARD_H__
#define __BOARD_H__

/** Constants for board size. */
#define COLUMN_SIZE 3
#define ROW_SIZE 3

/** Typedef to hide the board implementation. */
typedef struct Board *Board;

Board newBoard();
void destroyBoard(Board board);
void putOnBoard(Board board, char symbol, int row, int column);
void removeFromBoard(Board board, int row, int column);
int getEmptySpaces(Board board);
char (*getTable(Board board))[COLUMN_SIZE];
char getSymbol(Board board, int row, int col);
void printTable(Board board);

#endif
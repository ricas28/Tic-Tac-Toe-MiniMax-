#ifndef __BOARD_H__
#define __BOARD_H__

/** Constants for board size. */
#define COLUMN_SIZE 3
#define ROW_SIZE 3

/** Typedef to hide the board implementation. */
typedef struct Board *Board;

Board newBoard();
void destroyBoard(Board board);
char (*getTable(Board board))[COLUMN_SIZE];
void printTable(Board board);

#endif
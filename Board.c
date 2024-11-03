/**
 * Program to represent a Tic-Tac-Toe board.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

/** Constants for players. */
#define PLAYER_1 'X'
#define PLAYER_2 'O'

/** Board stucture. */
struct Board{
    char table[ROW_SIZE][COLUMN_SIZE];
};

/**
 * Initizalizes a new Board.
 * If the Board object is NULL doesn't do nothing.
 * 
 * @param board Board being initialized.
 */
void initializeBoard(Board board){
    if(board == NULL) return;

    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            // Initialize each cell with a dot.
            board->table[i][j] = '.';
        }
    } 
}

/**
 * Creates and returns a new board object.
 * If Board object can't be created by some reason, NULL will be returned.
 */
Board newBoard(){
    Board board = (Board)malloc(sizeof(struct Board));
    if(board != NULL) initializeBoard(board);
    return board;
}

/**
 * Destroys the given Board object.
 * 
 * @param board Board object.
 */
void destroyBoard(Board board){
    if(board){
        free(board);
    }
}


/**
 * Returns the board's table.
 * 
 * @param board Board object
 * @return board's table.
 */
char (*getTable(Board board))[COLUMN_SIZE]{
    return board->table;
}

/**
 * Prints the given board's table.
 * 
 * @param board Board object.
 */
void printTable(Board board){
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            printf(" %c ", getTable(board)[i][j]);
            if (j < COLUMN_SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < ROW_SIZE - 1) printf("-----------");
        printf("\n");
    }
} 
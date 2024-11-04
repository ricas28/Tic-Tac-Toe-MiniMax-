/**
 * Program to represent a  board object.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

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
 * 
 * @return new Board object.
 */
Board newBoard(){
    Board board = (Board)malloc(sizeof(struct Board));
    if(board != NULL) initializeBoard(board);
    return board;
}

/**
 * Puts the given symbol on the board's table according to the
 * given coordinates (indexed at 1).
 * 
 * @param board board.
 * @param symbol char to put on the board.
 * @param row row coordinate.
 * @param column column coordinate.
 */
void putOnBoard(Board board, char symbol, int row, int column){
    if (row <= 0 || row > ROW_SIZE || column <= 0 || column > COLUMN_SIZE){
        printf("Invalid coordinates: (%d, %d)!\n", row, column);
        return;
    }
    getTable(board)[row-1][column-1] = symbol;
}

/**
 * Removes the symbol at the coordinates (row, column) from the
 * given board.
 * 
 * @param board board.
 * @param row row coordinate.
 * @param column column coordinate.
 */
void removeFromBoard(Board board, int row, int column){
    putOnBoard(board, '.', row, column);   
}

/**
 * Returns the number of empty spaces on a board.
 * 
 * @param board board.
 * @return number of empty spaces on a board.
 */
int getEmptySpaces(Board board){
    int emptySpaces = 0;

    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
            if(getSymbol(board, i, j) == '.')
                emptySpaces++;
        }
    }
    return emptySpaces;
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
 * Returns the symbol at the given coordinates (indexed at 0).
 * 
 * @param board board.
 * @param row row coordinate.
 * @param col col coordinate.
 * @return symbol at the coordinates (row, col).
 */
char getSymbol(Board board, int row, int col){
    return getTable(board)[row][col];
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
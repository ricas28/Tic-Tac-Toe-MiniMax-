/**
 * Program that implements the miniMax algorithm for a Tic-Tac-Toe game.
 */
#include <stdio.h>
#include <math.h>
#include "Tic-Tac-Toe.h"

/**
 * Determines the most optimal play on a given board.
 * 
 * @param board current board.
 * @param isMax "bool" that determines if player is maximizing score or not.
 * @return score that a finished game has.
 */
double miniMax(Board board, int isMax){
    int emptySpaces = getEmptySpaces(board), winner = findWinner(board);
    double score, newScore;

    if(winner != EMPTY){
        return winner == PLAYER_1 ? (1 + emptySpaces) : (-1 - emptySpaces); 
    }
    if (emptySpaces == 0)
        return 0;

    score = isMax ? -INFINITY : INFINITY;
    /** Try all possible moves. */
    for(int i = 1; i <= ROW_SIZE; i++){
        for(int j = 1; j <= COLUMN_SIZE; j++){
            /** Check if play can be made. */
            if(!isPlayerSymbol(getSymbol(board, i-1, j-1))){
                putOnBoard(board, isMax ? PLAYER_1 : PLAYER_2, i, j);
                newScore = miniMax(board, !isMax);
                if ((isMax && newScore > score) || 
                    (!isMax && newScore < score)){
                        score = newScore;
                }
                /** Remove play from the board. */
                removeFromBoard(board, i, j);
            }
        }
    }
    return score;
}
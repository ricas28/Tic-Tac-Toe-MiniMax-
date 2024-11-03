#include <stdio.h>
#include "Board.h"

int main(void){
    Board board = newBoard();
    /** Check if creation of board was successfull. */
    if(board == NULL) return -1;
    printTable(board);
    destroyBoard(board);
    return 0;
}
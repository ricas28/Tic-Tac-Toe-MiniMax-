/**
 * Program for Tic-Tac-Toe game's logic.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Board.h"

/** Constants for logic implementations. */
#define TRUE 1
#define FALSE 0

/** Constants for players. */
#define PLAYER_1 'X'
#define PLAYER_2 'O'

/**
 * Checks if the given symbol is a player symbol.
 * 
 * @param symbol symbol to check.
 * @return TRUE if it's a player symbol and false otherwise.
 */
int isPlayerSymbol(char symbol){
    return symbol == PLAYER_1 || symbol == PLAYER_2;
}

/**
 * Checks if the any of the rows on a board has a win condition.
 * 
 * @param board board.
 * @return TRUE if a win condition was found and FALSE otherwise.
 */
int checkRows(Board board){
    for(int i = 0; i < ROW_SIZE; i++){
        if(isPlayerSymbol(getSymbol(board, i, 0)) &&
            getSymbol(board, i, 0) == getSymbol(board, i, 1) && 
            getSymbol(board, i, 0) == getSymbol(board, i, 2)){
                return TRUE;
        }
    }
    return FALSE;
}

/**
 * Checks if the any of the columns on a board has a win condition.
 * 
 * @param board board.
 * @return TRUE if a win condition was found and FALSE otherwise.
 */
int checkColumns(Board board){
    for(int i = 0; i < COLUMN_SIZE; i++){
        if(isPlayerSymbol(getSymbol(board, 0, i)) &&
            getSymbol(board, 0, i) == getSymbol(board, 1, i) && 
            getSymbol(board, 0, i) == getSymbol(board, 2, i) ){
                return TRUE;
        }
    }
    return FALSE;
}

/**
 * Checks if the any of the diagonls on a board has a win condition.
 * 
 * @param board board.
 * @return TRUE if a win condition was found and FALSE otherwise.
 */
int checkDiagonals(Board board){
    /** Check Positive diagonal. */
    if (isPlayerSymbol(getSymbol(board, 0, 0)) && 
        getSymbol(board, 0, 0) == getSymbol(board, 1, 1) && 
        getSymbol(board, 0, 0) == getSymbol(board, 2, 2)){
            return TRUE;
    }

    /** Check negative diagonal. */
    else if (isPlayerSymbol(getSymbol(board, 0, 2)) &&
        getSymbol(board, 0, 2) == getSymbol(board, 1, 1) && 
        getSymbol(board, 0, 2) == getSymbol(board, 2, 0)){
            return TRUE;
    }
    return FALSE;
}

/**
* Checks if the game is over on a given board.
* 
* @param board board.
* @return TRUE if a win condition was found and FALSE otherwise.
*/
int isGameOver(Board board){
    return checkRows(board) || checkColumns(board) || checkDiagonals(board);
}   

/**
 * Request for a human play.
 * 
 * @param play array that will be filled with the play.
 * */
void requestHumanPlay(int *play){
    char *row, *col;

    row = requestOption("Enter a row[1-3]: ", '1', '3');
    col = requestOption("Enter a column[1-3]: ", '1', '3');
    play[0] = atoi(row);
    play[1] = atoi(col);
    freeOption(row);
    freeOption(col);
}

int isValidPlay(Board board, int play[]){
    return !isPlayerSymbol(getSymbol(board, play[0] - 1, play[1] - 1));
}

/**
 * Switches the current player.
 * 
 * @param player1 pointer for "bool" of player1.
 * @param player2 pointer for "bool" of player2.
 */
void switchPlayers(int *player1, int *player2){
    if(*player1){
        *player1 = FALSE;
        *player2 = TRUE;
    }
    else{
        *player1 = TRUE;
        *player2 = FALSE;
    }
}

/**
 * Makes the main loop for a new game.
 * 
 * @param PVP int for PvP games.
 * @param PVC int for PVC games.
 * @param CVC int for CVC games.
 */
void playGame(int PvP, int PvC, int CvC){
    /** Player1 ('X') is always the first to play. */
    int player1 = TRUE, player2 = FALSE, play[2]; 
    Board board = newBoard();

    do{
        printTable(board);
        /** Humans always make plays on PVP an in player1's turn on PvC. */
        if(PvP || (PvC && player1)){
            /** Decide wich symbol will be put on the board. */
            requestHumanPlay(play);
            while(!isValidPlay(board, play)){
                printf("Invalid play: (%d,%d)!\n", play[0], play[1]);
                requestHumanPlay(play);
            }
        }
        else{
            /** Decide wether is maximizing according to the player. */
            printf("Computador!");
            //play = miniMax(board, player1 ? TRUE : FALSE);
        }
        putOnBoard(board, player1 ? PLAYER_1 : PLAYER_2, play[0], play[1]);
        switchPlayers(&player1, &player2);
    }while(!isGameOver(board) && getEmptySpaces(board) != 0);
    printTable(board);
    /** Players swicth even after the current player wins the game. */
    printf("Player [%c] wins!!\n", player2 ? PLAYER_1 : PLAYER_2);
    destroyBoard(board);
}

/**
 * Processes a Menu option according to each game mode code.
 * 
 * @param option option being analysed.
 */
void processMenuOption(char option){
    switch(option){
        case '1':
            playGame(TRUE, FALSE, FALSE);
            break;
        case '2':
            playGame(FALSE, TRUE, FALSE);
            break;
        case '3':
            playGame(FALSE, FALSE, TRUE);
            break;
        case '4':
            break;
        default:
            fprintf(stderr, "Unexepcted Error: Invalid option passed through\n");
    }
}

/**
 * Initalizes a new game.
 */
void initializeGame(){
    char *option;

    /** Show the menu. */
    showGameMenu();
    /** Request the menu option to be executed. */
    option = requestOption("Type Menu Option: ", '1', '4');
    processMenuOption(*option);
    /** After using option, free the allocated memory. */
    freeOption(option);
}
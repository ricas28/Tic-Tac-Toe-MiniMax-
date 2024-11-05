/**
 * Program for Tic-Tac-Toe game's logic.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "Menu.h"
#include "Board.h"
#include "Tic-Tac-Toe.h"
#include "MiniMax.h"

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
char checkRows(Board board){
    for(int i = 0; i < ROW_SIZE; i++){
        if(isPlayerSymbol(getSymbol(board, i, 0)) &&
            getSymbol(board, i, 0) == getSymbol(board, i, 1) && 
            getSymbol(board, i, 0) == getSymbol(board, i, 2)){
                return getSymbol(board, i, 0);
        }
    }
    return EMPTY;
}

/**
 * Checks if the any of the columns on a board has a win condition.
 * 
 * @param board board.
 * @return TRUE if a win condition was found and FALSE otherwise.
 */
char checkColumns(Board board){
    for(int i = 0; i < COLUMN_SIZE; i++){
        if(isPlayerSymbol(getSymbol(board, 0, i)) &&
            getSymbol(board, 0, i) == getSymbol(board, 1, i) && 
            getSymbol(board, 0, i) == getSymbol(board, 2, i) ){
                return getSymbol(board, 0, i);
        }
    }
    return EMPTY;
}

/**
 * Checks if the any of the diagonls on a board has a win condition.
 * 
 * @param board board.
 * @return player symbol if a win condition was found and EMPTY otherwise.
 */
char checkDiagonals(Board board){
    /** Check Positive diagonal. */
    if (isPlayerSymbol(getSymbol(board, 0, 0)) && 
        getSymbol(board, 0, 0) == getSymbol(board, 1, 1) && 
        getSymbol(board, 0, 0) == getSymbol(board, 2, 2)){
            return getSymbol(board, 0, 0);
    }

    /** Check negative diagonal. */
    else if (isPlayerSymbol(getSymbol(board, 0, 2)) &&
        getSymbol(board, 0, 2) == getSymbol(board, 1, 1) && 
        getSymbol(board, 0, 2) == getSymbol(board, 2, 0)){
            return getSymbol(board, 0, 2);
    }
    return EMPTY;
}

/**
* Checks if the game is over on a given board.
* 
* @param board board.
* @return winner symbol if a win condition was found and EMPTY otherwise.
*/
char findWinner(Board board){
    char winner, rows, cols, diagonals;

    rows = checkRows(board);
    cols = checkColumns(board);
    diagonals = checkDiagonals(board);

    if (rows != EMPTY)
        return rows;
    if(cols != EMPTY)
        return cols;
    if(diagonals != EMPTY)
        return diagonals;
        
    return EMPTY;
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
 * Generates a new random number between minNum and maxNum.
 * 
 * @param minNum min number.
 * @param maxNum max number.
 * @return new number between minNum and maxNum.
 */
int generateNewRandom(int minNum, int maxNum){
    int result = 0, lowNum = 0, hiNum = 0;
 
    if (minNum < maxNum)  {
        lowNum = minNum;
        hiNum = maxNum + 1;
    } 
    else {
        lowNum = maxNum + 1;
        hiNum = minNum;
    }
    
    srand(time(NULL));
    result = (rand() % (hiNum - lowNum)) + lowNum;
    return result;
}

/**
 * Makes a random play.
 * 
 * @param play array that will store the play.
 */
void makeRandomPlay(int play[]){
    play[0] = generateNewRandom(1, 3);
    play[1] = generateNewRandom(1, 3);
}

/**
 * Finds the best move on the current board using a miniMax algorithm.
 * 
 * @param board current board.
 * @param isMax "bool" to decide if player is maximizing or not.
 * @param play array to store the best play.
 */
void findBestMove(Board board, int isMax, int play[]){
    int bestRow, bestCol;
    double score, newScore, alpha, beta;

    score = isMax ? -INFINITY : INFINITY;
    alpha = -INFINITY;
    beta = INFINITY;

    for(int i = 1; i <= ROW_SIZE; i++){
        for(int j = 1; j <= COLUMN_SIZE; j++){
            /** Check if play can be made. */
            if(!isPlayerSymbol(getSymbol(board, i-1, j-1))){
                putOnBoard(board, isMax ? PLAYER_1 : PLAYER_2, i, j);
                newScore = miniMax(board, !isMax, alpha, beta);
                if ((isMax && newScore > score) || 
                    (!isMax && newScore < score)){
                        score = newScore;
                        bestRow = i;
                        bestCol = j;
                }
                if(isMax && newScore > alpha) alpha = newScore;
                else if(!isMax && newScore < beta) beta = newScore;
                /** Remove play for backtracking. */
                removeFromBoard(board, i, j);
            }
        }
    }
    /** Store the best play. */
    play[0] = bestRow;
    play[1] = bestCol;
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
    int player1 = TRUE, player2 = FALSE, play[2], emptySpaces, emptyTab = TRUE;
    char winner; 
    Board board = newBoard();

    do{
        printTable(board);
        /** Humans always make plays on PVP and on player1's turn on PvC. */
        if(PvP || (PvC && player1)){
            /** Decide wich symbol will be put on the board. */
            requestHumanPlay(play);
            while(!isValidPlay(board, play)){
                printf("Invalid play: (%d,%d)!\n", play[0], play[1]);
                requestHumanPlay(play);
            }
        }
        else{
            printf("Computer is playing...\n");
            sleep(1);
            /** Make first computer play random, for more diverse games */
            if (emptyTab)
                makeRandomPlay(play);
            else
                findBestMove(board, player1 ? TRUE : FALSE ,play);
        }
        putOnBoard(board, player1 ? PLAYER_1 : PLAYER_2, play[0], play[1]);
        /** After a play, the board is no longer empty. */
        emptyTab = FALSE;
        switchPlayers(&player1, &player2);
        winner = findWinner(board);
        emptySpaces = getEmptySpaces(board);
    }while(winner == EMPTY && emptySpaces != 0);

    printTable(board);
    if (winner == EMPTY && emptySpaces == 0)
        printf("Draw...\n");
    else
        printf("Player [%c] wins!!\n", winner);
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
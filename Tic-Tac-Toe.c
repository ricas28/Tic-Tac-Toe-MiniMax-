/**
 * Program for Tic-Tac-Toe game's logic.
 */
#include <stdio.h>
#include "Menu.h"
#include "Board.h"

void initializeGame(){
    char* option;

    /** Show the menu. */
    showGameMenu();
    /** Request the menu option to be executed. */
    option = requestOption();
    //processOption(option);
    /** After using option, free the allocated memory. */
    freeOption(option);
}
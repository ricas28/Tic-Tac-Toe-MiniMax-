/**
 * Program for the game's menu.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 50

/**
 * Shows the game Menu.
 */
void showGameMenu(){
    printf("WELCOME TO TIC-TAC-TOE!\n");
    printf("========= MENU ==========\n");
    printf("1 - Player Vs Player\n");
    printf("2 - Player Vs Computer\n");
    printf("3 - Computer Vs Computer\n");
    printf("4 - Quit\n");
    printf("=========================\n");
}

/**
 * Checks if the given option is valid.
 * 
 * @param option option being analised.
 * @return True if it's a valid option and False otherwise.
 */
int isValidOption(char* option){
    return strlen(option) == 1 && *option >= '1' && *option <= '4';
}

void lstrip(char* str) {
    char* p = str; /** Pointer to original string. */

    /** Advance the pointer until a non space char is found. */
    while (isspace((unsigned char)*p)) {
        p++;
    }

    /** No need to move memory if there's no spaces to remove. */
    if (p != str) {
        memmove(str, p, strlen(p) + 1); /** +1 to include '\0' */
    }
}

void rstrip(char* str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

/**
 * Reades a line from the stdin.
 * 
 * @return string that was read.
 */
char *readOption(){
    int bufferSize = BUFFER_SIZE, i = 0;
    char *option = (char*)malloc(bufferSize*sizeof(char)), c;
    /** Check if allocation was successfull */
    if(option == NULL){
        fprintf(stderr, "Error: alocating memory for readOption\n");
        return NULL;
    }

    /** Read until a '\n' is found. */
    while ((c = getchar()) != '\n'){
        /** Check if buffer has been exceeded. */
        if (i >= bufferSize - 1){
            bufferSize *= 2; /** Double the buffer size. */
            option = (char*)realloc(option, bufferSize*sizeof(char));
            if(option == NULL){
                fprintf(stderr, "Error: realocating memory for readOption\n");
                return NULL;
            }
        }
        option[i] = c; /** Store read char. */
        i++;
    }
    option[i] = '\0'; /** Add terminating '\0'. */
    /** Strip spaces from left and right. */
    lstrip(option);
    rstrip(option);
    return option;
}

/**
 * Frees the memory allocated for reading an option.
 */
void freeOption(char *option){
    if(option){
        free(option);
    }
}

/**
 * Requests the user for a option (int).
 * Option then needs to be freed with freeOption function.
 * 
 * @return option the user typed.
 */
char *requestOption(){
    char *option;

    printf("Type a menu option: ");
    option = readOption();

    while(!isValidOption(option)){
        printf("Invalid menu option: \"%s\"!\n", option);
        printf("Type a menu option: ");
        /** We need to get rid of old option. */
        freeOption(option);
        option = readOption();
    }

    return option;
}
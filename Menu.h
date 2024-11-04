/**
 * Interface for Menu program.
 */
#ifndef __MENU_H__
#define __MENU_H__

void showGameMenu();
char *requestOption(char *text, char minVal, char maxVal);
void freeOption(char *option);

#endif

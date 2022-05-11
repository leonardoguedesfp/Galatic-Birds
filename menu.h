#ifndef MENU_H
#define MENU_H

#define STRTAM 50

//Imprime o menu completo.
int menu();

//Imprime a borda superior do menu.
void menu_superior();

//Imprime a borda inferior do menu.
void menu_inferior();

//Imprime um item do menu.
void menu_item(char str[]);

//Imprime uma linha horizontal no meio do menu.
void menu_linha_horizontal();


#endif // MENU_H

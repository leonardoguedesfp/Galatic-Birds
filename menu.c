#include "voo_reserva.h"
#include "tools.h"
#include "menu.h"

//Imprime o menu completo.
int menu()
{
    int opcao;

    menu_superior();
    menu_item("                  GALATIC BIRDS");
    menu_linha_horizontal();
    menu_item(" 1 - CADASTRAR VOO");
    menu_linha_horizontal();
    menu_item(" 2 - CADASTRAR RESERVA");
    menu_linha_horizontal();
    menu_item(" 3 - CONSULTAR VOO");
    menu_linha_horizontal();
    menu_item(" 4 - CONSULTAR RESERVA");
    menu_linha_horizontal();
    menu_item(" 5 - CONSULTAR PASSAGEIRO");
    menu_linha_horizontal();
    menu_item(" 6 - CANCELAR VOO");
    menu_linha_horizontal();
    menu_item(" 7 - CANCELAR RESERVA");
    menu_linha_horizontal();
    menu_item(" 8 - EXCLUIR VOO");
    menu_linha_horizontal();
    menu_item(" 9 - CONSULTAR VOOS CADASTRADOS");
    menu_linha_horizontal();
    menu_item("10 - CONSULTAR RESERVAS CADASTRADAS");
    menu_linha_horizontal();
    menu_item("11 - SAIR DO PROGRAMA");
    menu_inferior();

    do{
        char newline;
        fflush(stdin);
        printf("\nDigite um numero que corresponda a opcao desejada: ");
        if(scanf("%d%c", &opcao, &newline) != 2 || newline != '\n' || opcao < 1 || opcao > 11){
            while(getchar()!='\n');
            printf("Opcao inexistente.\n");
        }
        else {
            return opcao;
        }
    } while(1);
}

//Imprime a borda superior do menu.
void menu_superior()
{
    printf("%c", 201);
    for (int i =0; i < STRTAM; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);
}

//Imprime a borda inferior do menu.
void menu_inferior()
{
    printf("%c", 200);
    for (int i =0; i < STRTAM; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

//Imprime um item do menu.
void menu_item(char str[])
{
    printf("%c", 186);
    printf("%-*s", STRTAM, str);
    printf("%c\n", 186);
}

//Imprime uma linha horizontal no meio do menu.
void menu_linha_horizontal()
{
    printf("%c", 204);
    for (int i =0; i < STRTAM; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);
}



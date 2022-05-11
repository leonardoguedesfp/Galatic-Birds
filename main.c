/*

TRABALHO APRESENTADO COMO REQUISITO PARA APROVAÇÃO NA DISCIPLINA ALGORITMOS E PROGRAMAÇÃO DE COMPUTADORES (COD: CIC0004) DA
UNIVERSIDADE DE BRASÍLIA MINISTRADA NO SEMESTRE 2021.1.

ALUNO: Leonardo Guedes da Fonseca Passos
MATRICULA: 211029414
PROFESSOR: Giovanni Almeida Santos
TURMA: CC

APRESENTAÇÃO: Programa que gerencia as operacoes da Galatic Birds, agencia de viagens que opera voos ate a linha de Karman.

*/

#include "tools.h"
#include "voo_reserva.h"
#include "menu.h"

//PROTOTIPOS DAS FUNCOES DECLARADAS E DEFINIDAS NA MAIN.

//Importa os voos do arquivo para uma array.
int importar_voos(FILE *v, Voo lista_voos[]);

//Importa as reservas do arquivo para uma array.
int importar_res(FILE *r, Reserva lista_res[]);

//Sobrescreve o arquivo binario de voos com o conteudo atualizado da array de voos.
void sobresc_voos_bin(FILE *v, Voo lista_voos[], int qtd_voos);

//Sobrescreve o arquivo de texto de voos com o conteudo atualizado da array de voos.
void sobresc_voos_txt(FILE *v_txt, Voo lista_voos[], int qtd_voos);

//Sobrescreve o arquivo binario de reservas com o conteudo atualizado da array de reservas.
void sobresc_res_bin(FILE *r, Reserva lista_res[], int qtd_res);

//Sobrescreve o arquivo de texto de reservas com o conteudo atualizado da array de reservas.
void sobresc_res_txt(FILE *r_txt, Reserva lista_res[], int qtd_res);

//Sobrescreve todos os arquivos (binarios e de texto) com o conteudo atualizado das arrays (de reservas e de voos).
void sobresc_arquivos(FILE *v, FILE *v_txt, Voo lista_voos[], int qtd_voos, FILE *r, FILE *r_txt, Reserva lista_res[], int qtd_res);


int main()
{
    FILE *v, *r;
    FILE *v_txt, *r_txt;
    Voo lista_voos[TAM_LISTA_VOOS];
    Reserva lista_res[TAM_LISTA_RES];
    int qtd_voos = 0;
    int qtd_res = 0;
    int res_exc;

/* Antes de rodar o menu, as duas sequencias de funcoes a seguir importam todos os voos e reservas que estavam armazenadas
em arquivo, armazena-os em duas arrays e retornam o numero de voos e reservas que foram importadas. */
    qtd_voos = importar_voos(v, lista_voos);
    qtd_res = importar_res(r, lista_res);

    while(1) {
        int menuOp = menu();
        switch (menuOp){
            case 1: //Cadastrar voo

/* Cada voo e cadastrado pela funcao voo_cad e armazenado tanto em arquivo (pela funcao voo_arq) quanto na array de voos,
na posicao seguinte ao do ultimo voo preenchido (controlado pela variavel qtd_voos). Mesmo raciocinio se aplica no "case 2".
Obs: Embora os voos e reservas sejam armazenados tanto em arquivos de texto quanto em binarios, apenas estes ultimos tem
funcao no programa. O arquivo de texto foi criado apenas para facilitar a visualizacao.
*/
                lista_voos[qtd_voos] = voo_arq(voo_cad(lista_voos, qtd_voos));
                qtd_voos++;

                printf("\n");
                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();

            break;

            case 2: //Cadastrar reserva
                lista_res[qtd_res] = reserva_arq(res_cad(lista_res, qtd_res, lista_voos, qtd_voos));
                qtd_res++;

                printf("\n");
                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();

            break;

            case 3: //Consultar voo
                voo_consulta(lista_voos, lista_res, qtd_voos, qtd_res);

                printf("\n");
                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 4: //Consultar reserva
                res_consulta(lista_voos, lista_res, qtd_voos, qtd_res);

                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 5: //Consultar passageiro
                cpf_consulta(lista_voos, lista_res, qtd_voos, qtd_res);

                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 6: //Cancelar voo (cancela o voo na array e sobrescreve os arquivos de voo com o conteudo da array)
                cancel_voo_array(lista_voos, lista_res, qtd_voos, qtd_res);
                sobresc_arquivos(v, v_txt, lista_voos, qtd_voos, r, r_txt, lista_res, qtd_res);

                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 7: //Cancelar resserva (cancela a reserva na array e sobrescreve os arquivos de reserva com o conteudo da array)
                cancel_res_array (lista_voos, lista_res, qtd_voos, qtd_res);
                sobresc_arquivos(v, v_txt, lista_voos, qtd_voos, r, r_txt, lista_res, qtd_res);

                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 8: //Excluir voo (exclui o voo na array e sobrescreve os arquivos de voo com o conteudo da array)
                res_exc = exclui_voo_array (lista_voos, lista_res, qtd_voos, qtd_res);
                qtd_voos--; //decrementa a variavel que controla o numero de voos cadastrados
                for (int i = 0; i < res_exc; i++) {
                    qtd_res--; //decrementa a variavel que controla o numero de reservas cadastradas
                }
                sobresc_arquivos(v, v_txt, lista_voos, qtd_voos, r, r_txt, lista_res, qtd_res);


                printf("Aperte enter para retornar ao menu...");
                fflush(stdin);
                getchar();
            break;

            case 9: //Consultar voos registrados (imprime dados de todos os voos)
                consulta_voos_cadastrados (lista_voos, qtd_voos);
                printf("\n\n\nAperte enter para retornar ao menu...");
                getchar();
            break;


            case 10: //Consultar reservas registradas (imprime dados de todas as reservas)
                consulta_res_cadastradas (lista_res, qtd_res);
                printf("\n\n\nAperte entre para retornar ao menu...");
                getchar();
            break;

            case 11: //Sair do programa
                printf("Opcao 11 funcionando!\n");
                return 0;
            break;
        }
    }
    return 0;
}

//Importa os voos do arquivo para uma array.
int importar_voos(FILE *v, Voo lista_voos[])
{
    Voo voo1;
    v = fopen("voos.bin", "ab+");

    if (v == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    int qtd_voos = 0;

    while (fread(&voo1, sizeof(voo1), 1, v) == 1) {
        lista_voos[qtd_voos] = voo1;
        qtd_voos++;
    }

    fclose(v);
    return qtd_voos;
}

//Importa as reservas do arquivo para uma array.
int importar_res(FILE *r, Reserva lista_res[])
{
    Reserva res1;
    r = fopen("reservas.bin", "ab+");

    if (r == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    int qtd_res = 0;

    while (fread(&res1, sizeof(res1), 1, r) == 1) {
        lista_res[qtd_res] = res1;
        qtd_res++;
    }

    fclose(r);
    return qtd_res;
}

//Sobrescreve o arquivo binario de voos com o conteudo atualizado da array de voos.
void sobresc_voos_bin(FILE *v, Voo lista_voos[], int qtd_voos)
{
    int i = 0;

    v = fopen("voos.bin", "wb");

    if (v == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    do{
        if (lista_voos[i].num_voo != ""){
            fwrite(&lista_voos[i], sizeof(Voo), 1, v);
            i++;
        }
    }while(i < qtd_voos);


    fclose(v);
}

//Sobrescreve o arquivo de texto de voos com o conteudo atualizado da array de voos.
void sobresc_voos_txt(FILE *v_txt, Voo lista_voos[], int qtd_voos)
{
    int i = 0;

    v_txt = fopen("voos.txt", "w");

    if (v_txt == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    do{
        if (lista_voos[i].num_voo != "") {
            fprintf(v_txt, "%s %s %s %d %d\n", lista_voos[i].num_voo, lista_voos[i].data, lista_voos[i].horario, lista_voos[i].status, lista_voos[i].capacidade);
            i++;
        }
    }while(i < qtd_voos);


    fclose(v_txt);
}

//Sobrescreve o arquivo binario de reservas com o conteudo atualizado da array de reservas.
void sobresc_res_bin(FILE *r, Reserva lista_res[], int qtd_res)
{
    int i = 0;

    r = fopen("reservas.bin", "wb");

    if (r == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    do{
        if (lista_res[i].num_reserva != "") {
            fwrite(&lista_res[i], sizeof(Reserva), 1, r);
            i++;
        }
    }while(i < qtd_res);


    fclose(r);
}

//Sobrescreve o arquivo de texto de reservas com o conteudo atualizado da array de reservas.
void sobresc_res_txt(FILE *r_txt, Reserva lista_res[], int qtd_res)
{
    int i = 0;

    r_txt = fopen("reservas.txt", "w");

    if (r_txt == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    do{
        if (lista_res[i].num_reserva != "") {
            fprintf(r_txt, "%s %s %s %s %s %d %d\n", lista_res[i].num_reserva, lista_res[i].num_voo, lista_res[i].cpf, lista_res[i].nome, lista_res[i].nascimento, lista_res[i].sexo, lista_res[i].status);
            i++;
        }
    }while(i < qtd_res);


    fclose(r_txt);
}

//Sobrescreve todos os arquivos (binarios e de texto) com o conteudo atualizado das arrays (de reservas e de voos).
void sobresc_arquivos(FILE *v, FILE *v_txt, Voo lista_voos[], int qtd_voos, FILE *r, FILE *r_txt, Reserva lista_res[], int qtd_res)
{
    sobresc_voos_bin(v, lista_voos, qtd_voos);
    sobresc_voos_txt(v_txt, lista_voos, qtd_voos);
    sobresc_res_bin(r, lista_res, qtd_res);
    sobresc_res_txt(r_txt, lista_res, qtd_res);
}



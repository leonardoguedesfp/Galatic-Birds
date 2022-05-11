#ifndef VOO_RESERVA_H
#define VOO_RESERVA_H

#define TAM_NUM_VOO 9
#define TAM_NUM_RES 10
#define TAM_DATA 11
#define TAM_HORARIO 6
#define TAM_CPF 12
#define TAM_NOME 50
#define TAM_NASCIMENTO 11
#define TAM_SEXO 6
#define TAM_STATUS 6
#define TAM_LISTA_VOOS 100
#define TAM_LISTA_RES 1000

typedef struct voo {                    //Definindo e dando nome  a estrutura Voo.
    char num_voo[TAM_NUM_VOO];          //formato: JEB-XXXX
    char data[TAM_DATA];                //formato: dd/mm/aaaa
    char horario[TAM_HORARIO];          //formato: hh:mm
    int status;                         //Correspondencias: 0 p/ Ativo e 1 p/ Cancelado.
    int capacidade;

} Voo;

typedef struct reserva {                //Definindo e dando nome  a estrutura Reserva.
    char num_reserva[TAM_NUM_RES];      //formato: GB-XXXXXX
    char num_voo[TAM_NUM_VOO];          //formato: JEB-XXXX
    char cpf[TAM_CPF];                  //formato: XXXXXXXXXXX.
    char nome[TAM_NOME];
    char nascimento[TAM_NASCIMENTO];    //formato: dd/mm/aaaa
    int sexo;                           //Correspondencias:  0 p/ Masculino; 1 p/ Feminino e 2 p/ Outros)
    int status;                         //Correspondencias: 0 p/ Ativa e 1 p/ Cancelada.

} Reserva;


//Le informacoes do usuario e retorna uma struc Voo com esses dados.
Voo voo_cad(Voo lista_voos[], int qtd_voos);

//Armazena uma struc Voo em arquivo.
Voo voo_arq(Voo b);

//Le informacoes do usuario e retorna uma struc Reserva com esses dados.
Reserva res_cad(Reserva lista_res[], int qtd_res, Voo lista_voos[], int qtd_voos);

//Armazena uma struc Reserva em arquivo.
Reserva reserva_arq(Reserva b);

//Pesquisa um voo na base de dados e imprime algumas informacoes a respeito dele.
void voo_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Pesquisa uma reserva na base de dados e imprime algumas informacoes a respeito dela.
void res_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Pesquisa todas as reservas vinculadas a determinado CPF e retorna as informacoes a respeito delas.
void cpf_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Cancela o voo (e reserva a ele vinculadas) na array.
void cancel_voo_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Cancela reserva na array.
void cancel_res_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Exclui o voo (e reserva a ele vinculadas) na array. Retorna o numero de reservas excluidas.
int exclui_voo_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res);

//Imprime todos os voos cadastrados e os dados relacionados a cada um deles.
void consulta_voos_cadastrados (Voo lista_voos[], int qtd_voos);

//Imprime todas as reservas cadastradas e os dados relacionados a cada um delas.
void consulta_res_cadastradas (Reserva lista_res[], int qtd_res);



#endif // VOO_RESERVA_H

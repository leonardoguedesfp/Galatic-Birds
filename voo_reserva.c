#include "voo_reserva.h"
#include "tools.h"
#include "menu.h"

//Le informacoes do usuario e retorna uma struc Voo com esses dados.
Voo voo_cad(Voo lista_voos[], int qtd_voos)
{
    Voo voo;
    int controle;

    while(1){   //Lendo e validando numero do voo
        printf("Digite o numero do voo no formato JEB-XXXX: ");
        scanf("%s", voo.num_voo);
        if (val_num_voo(voo.num_voo) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(voo.num_voo); i++){ //Passando as letras para maiúsculo.
                voo.num_voo[i] = toupper(voo.num_voo[i]);
            }

            controle = 0;
            for (int i = 0; i < qtd_voos; i++){ //Verificando se o voo ja existe no sistema
                if (strcmp(lista_voos[i].num_voo, voo.num_voo) == 0) {
                    controle++;
                }
            }

            if (controle != 0){
                printf ("O voo informado ja esta cadastrado no sistema. Digite outro numero de voo. "); //020
            }
            else {
                break;
            }
        }
    }

    while(1){   //Lendo e validando data
        printf("Digite a data do voo no formato dd/mm/aaaa: ");
        scanf("%s", voo.data);
        if (val_data(voo.data) == 0) {
            printf("Formato incorreto. ");
        }
        else if (val_data(voo.data) == 2) {
            printf("O dia informado nao existe. ");
        }
        else if (val_data(voo.data) == 3) {
            printf("O mes informado nao existe. ");
        }
        else if (val_data(voo.data) == 4) {
            printf("A data informada deve ser futura. ");
        }
        else {
            break;
        }
    }

    while(1){   //Lendo e validando horario
        printf("Digite o horario do voo no formato hh:mm: ");
        scanf("%s", voo.horario);
        if (val_hora(voo.horario) != 1) {
            if (val_hora(voo.horario) == 0) {
                printf("Formato incorreto. ");
            }
            else if (val_hora(voo.horario) == 2) {
                printf("o valor relativo a hora deve ser informado entre 0 e 23. ");
            }
            else if (val_hora(voo.horario) == 3) {
                printf("o valor relativo aos minutos deve ser informado entre 0 e 60. ");
            }

        }
        else{
            break;
        }
    }

    voo.status = 0; //Atribuindo status ATIVO


    do{
        char newline;
        printf("Digite a capacidade do voo: "); //Lendo e validando capacidade do voo
        if(scanf("%d%c", &voo.capacidade, &newline) != 2 || newline != '\n') {
            while(getchar()!='\n');
            printf("A capacidade do voo deve corresponder a um numero inteiro. ");
        }
        else{
            if (voo.capacidade <= 0){
                printf("A capacidade do voo deve ser maior do que zero. ");
            }
            else {
                break;
            }
        }

    } while(1);

    printf("\nVOO CADASTRADO COM SUCESSO.\n");                  //Confirmando o cadastro do voo e imprimindo as informacoes
    printf("O numero do voo e %s.\n", voo.num_voo);
    printf("A data do voo e %s.\n", voo.data);
    printf("O horario do voo e %s.\n", voo.horario);
    printf("O status do voo e ATIVO.\n");
    printf("A capacidade do voo e %d.\n", voo.capacidade);

    return voo;

}

//Armazena uma struc Voo em arquivo
Voo voo_arq(Voo b)
{
    // Armazenando o voo em arquivo binario
    FILE *a;

    a = fopen("voos.bin", "ab+");

    if (a == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    fwrite(&b, sizeof(b), 1, a);

    fclose(a);

    // Armazenando o voo em arquivo de texto
    FILE *arquivo_txt;

    arquivo_txt = fopen("voos.txt", "a+");

    if (arquivo_txt == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    fprintf(arquivo_txt, "%s %s %s %d %d\n", b.num_voo, b.data, b.horario, b.status, b.capacidade );

    fclose(arquivo_txt);

    return b;
}

//Le informacoes do usuario e retorna uma struc Reserva com esses dados.
Reserva res_cad(Reserva lista_res[], int qtd_res, Voo lista_voos[], int qtd_voos)
{
    Reserva res;
    int controle_res;
    int controle_voo, controle_voo_canc;
    int passageiros, res_dupla;
    int index_voo;

    while(1){   //Lendo e validando numero da reserva
        printf("Digite o numero da reserva no formato GB-XXXXXX: ");
        scanf("%s", res.num_reserva);
        if (val_num_reserva(res.num_reserva) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(res.num_reserva); i++){  //Passando as letras para maiúsculo.
                res.num_reserva[i] = toupper(res.num_reserva[i]);
            }

            controle_res = 0; //Verificando se a reserva já existe no sistema
            for (int i = 0; i < qtd_res; i++){
                if(strcmp(lista_res[i].num_reserva, res.num_reserva) == 0) {
                    controle_res++;
                }
            }

            if (controle_res != 0){
                printf ("O numero de reserva informado ja esta cadastrado no sistema. ");
            }
            else {
                break;
            }
        }
    }

    while(1){   //Lendo e validando numero do voo
        printf("Digite o numero do voo no formato JEB-XXXX: ");
        scanf("%s", res.num_voo);
        if (val_num_voo(res.num_voo) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(res.num_voo); i++){ //Tornando a string maiuscula
                res.num_voo[i] = toupper(res.num_voo[i]);
            }

            controle_voo = 0; //Verificando se o voo nao existe no sistema, se foi cancelado, se ja ocorreu ou se esta lotado
            controle_voo_canc = 0;
            for (int i = 0; i < qtd_voos; i++){
                if(strcmp(lista_voos[i].num_voo, res.num_voo) == 0) {
                    controle_voo++;
                    index_voo = i;

                    if(lista_voos[i].status == 1) {
                        controle_voo_canc++;
                    }
                }
            }
            if (controle_voo == 0){
                printf("O voo informado nao existe. Escolha outro voo.");
            }
            else {
                if (controle_voo_canc != 0) {
                    printf("O voo informado foi cancelado. Escolha outro voo. ");
                }
                else {
                    if (val_data(lista_voos[index_voo].data) == 4) {
                        printf("O voo informado ja ocorreu. Escolha outro voo. ");
                    }
                    else {
                        passageiros = 0;
                        for (int i = 0; i < qtd_res; i++){  //Verifica se o voo ja esta lotado.
                            if(strcmp(lista_res[i].num_voo, res.num_voo) == 0) {
                                if(lista_res[i].status == 0){
                                    passageiros++;
                                }
                            }
                        }
                        if (passageiros >= lista_voos[index_voo].capacidade) {
                            printf("O voo informado esta lotado. Escolha outro voo: ");
                        }
                        else{
                            break;
                        }
                    }

                }
            }
        }
    }

    while(1){ //Lendo e validando numero do CPF
        printf("Digite o numero do CPF sem espacos, pontos ou tracos: ");
        scanf("%s", res.cpf);
        if (val_CPF(res.cpf) == 2) {
            printf("Formato incorreto. ");
        }
        else
            if (val_CPF(res.cpf) == 0) {
                printf("Numero de CPF invalido. ");
            }
            else {  //Confirmando se o passageiro ja nao tem reserva para o voo
                res_dupla = 0;
                for (int i = 0; i < qtd_res; i++){
                    if(strcmp(lista_res[i].num_voo, res.num_voo) == 0) {
                        if(strcmp(lista_res[i].cpf, res.cpf) == 0){
                            if(lista_res[i].status == 0) {
                                res_dupla++;
                            }
                        }
                    }
                }

                if (res_dupla != 0) {
                    printf("Ja ha reserva ativa para o titular deste CPF. ");
                }
                else {
                   break;
                }
            }
    }

    printf("Digite o nome: ");
    fflush(stdin);
    scanf("%[^\n]s", res.nome);
    for (int i = 0; i < strlen(res.nome); i++){ //Tornando as letras do nome maiusculas
        res.nome[i] = toupper(res.nome[i]);
    }

    while(1){ //Lendo e validando data
        printf("Digite o nascimento no formato dd/mm/aaaa: ");
        scanf("%s", res.nascimento);
        if (val_data(res.nascimento) == 0) {
            printf("Formato incorreto. ");
        }
        else if (val_data(res.nascimento) == 2) {
            printf("O dia informado nao existe. ");
        }
        else if (val_data(res.nascimento) == 3) {
            printf("O mes informado nao existe. ");
        }
        else if (val_data(res.nascimento) == 1) {
            printf("A data informada nao pode ser futura. ");
        }
        else{
            break;
        }
    }

    printf("Digite o sexo do passageiro (0 - Masculino; 1 p/ Feminino; ou 2 p/ Outros): "); //Lendo sexo do passageiro
    scanf("%d", &res.sexo);

    res.status = 0; //Atribuindo o status ATIVO para a reserva

    printf("\nRESERVA CADASTRADA COM SUCESSO.\n");  //Confirmando o cadastro da reserva e imprimindo as informacoes
    printf("O numero da reserva e %s.\n", res.num_reserva);
    printf("O numero do voo e %s.\n", res.num_voo);
    printf("O numero do CPF e %s.\n", res.cpf);
    printf("O nome do passageiro e %s.\n", res.nome);
    printf("A data de nascimento do passageiro e %s.\n", res.nascimento);
    printf("O sexo do passageiro e %d.\n", res.sexo);
    printf("O status da reserva e ATIVA.\n");

    return res;
}

//Armazena uma struc Reserva em arquivo.
Reserva reserva_arq(Reserva b)
{
    // Armazenando a reserva em arquivo binario
    FILE *a;

    a = fopen("reservas.bin", "ab+");

    if (a == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    fwrite(&b, sizeof(b), 1, a);

    fclose(a);

    // Armazenando a reserva em arquivo de texto
    FILE *arquivo_txt;

    arquivo_txt = fopen("reservas.txt", "a+");

    if (arquivo_txt == NULL) {
        printf("Arquivo nao pode ser aberto!");
        exit(1);
    }

    fprintf(arquivo_txt, "%s %s %s %s %s %d %d\n", b.num_reserva, b.num_voo, b.cpf, b.nome, b.nascimento, b.sexo, b.status);

    fclose(arquivo_txt);
    return b;
}

//Pesquisa um voo na base de dados e imprime algumas informacoes a respeito dele.
void voo_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    int passageiros, voo_index;
    float percent_lot;
    char consult_voo[9];
    int controle_voo;

    while(1){ //Lendo e validando o numero do voo
        printf("Digite o numero do voo no formato JEB-XXXX: ");
        scanf("%s", consult_voo);
        if (val_num_voo(consult_voo) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(consult_voo); i++){ //Tornando a string maiuscula
                consult_voo[i] = toupper(consult_voo[i]);
            }

            controle_voo = 0; //Verificando se o voo existe no sistema
            for (int i = 0; i < qtd_voos; i++){
                if(strcmp(lista_voos[i].num_voo, consult_voo) == 0) {
                    controle_voo++;
                }
            }
            if (controle_voo == 0){
                printf("O voo informado nao existe. ");
            }
            else {
                break;
            }
        }
    }

    for (int j = 0; j < qtd_voos; j++) {            //Identifica o voo informado e retorna o seu índice na array de voos.
        if (strcmp(lista_voos[j].num_voo, consult_voo) == 0){
            voo_index = j;
        }
    }
    printf("\n\n");
    printf("=================================================================================\n");
    printf("                            CONSULTA AO VOO %s\n", lista_voos[voo_index].num_voo);
    printf("=================================================================================\n");

    printf("LISTA DE PASSAGEIROS:\n");
    printf("---------------------------------------------------------------------------------\n");
    passageiros = 0;

//Para cada reserva atrelada ao voo, imprime o nome do passageiro.
    for (int i = 0; i < qtd_res; i++) {
        if (strcmp(lista_res[i].num_voo, consult_voo) == 0){
            passageiros++;
            printf(">> %s\n", lista_res[i].nome);
            printf("---------------------------------------------------------------------------------\n");
        }
    }
//Imprime o percentual de lotacao, os assentos ocupados e os assentos existentes.
    percent_lot = 100 * (float) passageiros / lista_voos[voo_index].capacidade;
    printf("\nTAXA DE OCUPACAO: %.2f por cento (%d assentos ocupados entre os %d assentos existentes)\n", percent_lot, passageiros, lista_voos[voo_index].capacidade);
}

//Pesquisa uma reserva na base de dados e imprime algumas informacoes a respeito dela.
void res_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    char consult_res[10];
    char sexo[6];
    char status_res[6];
    char status_voo[6];
    int controle_res = 0;
    int res_index = 0;
    int voo_index = 0;

    while(1){ //Lendo e validando numero de reserva
        printf("Digite o numero da reserva no formato GB-XXXXXX: ");
        scanf("%s", consult_res);
        if (val_num_reserva(consult_res) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(consult_res); i++){ //Tornando letras maiusculas
                consult_res[i] = toupper(consult_res[i]);
            }

            controle_res = 0; //Verificando se a reserva ja existe no sistema
            for (int i = 0; i < qtd_res; i++){
                if(strcmp(lista_res[i].num_reserva, consult_res) == 0) {
                    controle_res++;
                    res_index = i;
                }
            }

            if (controle_res == 0){
                printf ("A reserva informada nao esta cadastrada no sistema. ");
            }
            else {
                break;
            }
        }
    }

    for (int j = 0; j < qtd_voos; j++){ //O status da reserva sera ATIVA para 0 e CANCELADA para outros numeros.
        if(strcmp(lista_res[res_index].num_voo, lista_voos[j].num_voo) == 0) {
            voo_index = j;
            if (lista_voos[j].status == 0) {
                strcpy(status_voo, "ATIVO");
            }
            else {
                strcpy(status_voo, "CANCE");
            }
        }
    }

    for (int i = 0; i < qtd_res; i++) { //O status do voo sera ATIVO para 0 e CANCELADO para outros numeros.
        if (lista_res[i].status == 0) {
            strcpy(status_res, "ATIVO");
        }
        else {
            strcpy(status_res, "CANCE");
        }

        if (lista_res[i].sexo == 0) { //O sexo sera MASCULINO para 0, FEMININO para 1 e 0 para OUTROS.
            strcpy(sexo, "MASCU");
        }
        else if (lista_res[i].sexo == 1) {
            strcpy(sexo, "FEMIN");
        }
        else {
            strcpy(sexo, "OUTRO");
        }

        if (strcmp(lista_res[i].num_reserva, consult_res) == 0){       //Imprimindo dados da reserva e do respectivo voo.
            printf("\n\n");
            printf("==================================================================\n");
            printf("             CONSULTA A RESERVA %s\n", lista_res[res_index].num_reserva);
            printf("==================================================================\n");
            printf(">>>DADOS DA RESERVA:\n");
            printf("------------------------------------------------------------------\n");
            printf("     NUMERO DA RESERVA: %s\n", lista_res[res_index].num_reserva);
            printf("------------------------------------------------------------------\n");
            printf("     NOME: %s\n", lista_res[res_index].nome);
            printf("------------------------------------------------------------------\n");
            printf("     CPF: %s\n", lista_res[res_index].cpf);
            printf("------------------------------------------------------------------\n");
            printf("     DATA DE NASCIMENTO: %s\n", lista_res[res_index].nascimento);
            printf("------------------------------------------------------------------\n");
            printf("     SEXO: %s\n", sexo);
            printf("------------------------------------------------------------------\n");
            printf("     STATUS DA RESERVA: %s\n", status_res);
            printf("------------------------------------------------------------------\n");

            printf(">>>DADOS DO VOO:\n");
            printf("------------------------------------------------------------------\n");
            printf("     NUMERO DO VOO: %s\n", lista_voos[voo_index].num_voo);
            printf("------------------------------------------------------------------\n");
            printf("     DATA DO VOO: %s\n", lista_voos[voo_index].data);
            printf("------------------------------------------------------------------\n");
            printf("     HORARIO DO VOO: %s\n", lista_voos[voo_index].horario);
            printf("------------------------------------------------------------------\n");
            printf("     STATUS DO VOO: %s\n", status_voo);
            printf("\n\n\n");
        }
    }
}

//Pesquisa todas as reservas vinculadas a determinado CPF e retorna as informacoes a respeito delas.
void cpf_consulta(Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    char consult_cpf[TAM_CPF];
    char sexo[TAM_SEXO];
    char status[TAM_STATUS];
    int controle_cpf = 0;
    int indice_cpf = 0;
    int num = 0;
    int voo_index = 0;
    int res_index = 0;

    while(1){ //Lendo e validando CPF
        printf("Digite o numero do CPF sem espacos, pontos ou tracos: ");
        scanf("%s", consult_cpf);
        if (val_CPF(consult_cpf) == 2) {
            printf("Formato incorreto. ");
        }
        else {
            if (val_CPF(consult_cpf) == 0) {
                printf("Numero de CPF invalido. ");
            }
            else {
                break;
            }
        }
    }

    for (int i = 0; i < qtd_res; i++) {  //Verificando se ha cadastro previo para o CPF
        if (strcmp(lista_res[i].cpf, consult_cpf) == 0) {
            controle_cpf++;
        }
    }

    if (controle_cpf == 0) {
        printf("O CPF informado nao esta cadastrado em nenhum voo.\n ");
    }
    else{
        printf("\n\n"); //Imprimindo o título
        printf("==========================================================\n");
        printf("CONSULTA AS RESERVAS VINCULADAS AO CPF %s\n", consult_cpf);
        printf("==========================================================\n");

        for (int i = 0; i < qtd_res; i++) {
            if (strcmp(lista_res[i].cpf, consult_cpf) == 0) {
                if (lista_res[i].status == 0) { //O status do voo sera ATIVO para 0 e CANCELADO para outros numeros.
                    strcpy(status, "ATIVO");
                }
                else {
                    strcpy(status, "CANCE");
                }

                if (lista_res[i].sexo == 0) { //O sexo sera MASCULINO para 0, FEMININO para 1 e 0 para OUTROS.
                    strcpy(sexo, "MASCU");
                }
                else if (lista_res[i].sexo == 1) {
                    strcpy(sexo, "FEMIN");
                }
                else {
                    strcpy(sexo, "OUTRO");
                }
            }
        }

        printf("\n                  DADOS DO PASSAGEIRO(A)\n\n"); //Imprimindo dados do passageiro
        printf("----------------------------------------------------------\n");
        printf("NOME DO PASSAGEIRO: %s\n", lista_res[res_index].nome);
        printf("----------------------------------------------------------\n");
        printf("CPF: %s\n", lista_res[res_index].cpf);
        printf("----------------------------------------------------------\n");
        printf("SEXO: %s\n", sexo);
        printf("----------------------------------------------------------\n");
        printf("DATA DE NASCIMENTO: %s\n", lista_res[res_index].nascimento);
        printf("----------------------------------------------------------\n");
        printf("\n                   RESERVAS CADASTRADAS\n\n");
        printf("----------------------------------------------------------\n");



        for (int i = 0; i < qtd_res; i++) {
            if (strcmp(lista_res[i].cpf, consult_cpf) == 0) {
                printf(">>> DADOS DA RESERVA %s\n", lista_res[i].num_reserva); //Imprimindo dados da reserva
                printf("----------------------------------------------------------\n");
                printf("     STATUS DA RESERVA: %s\n", status);
                printf("----------------------------------------------------------\n");
                for (int j = 0; j < qtd_voos; j++) {
                    if (strcmp(lista_voos[j].num_voo, lista_res[i].num_voo) == 0) {
                        printf("     NUMERO DO VOO: %s\n", lista_voos[j].num_voo);
                        printf("----------------------------------------------------------\n");
                        printf("     DATA DO VOO: %s\n", lista_voos[j].data);
                        printf("----------------------------------------------------------\n");
                        printf("     HORARIO DO VOO: %s\n", lista_voos[j].horario);
                        printf("\n\n");

                    }
                }
            }
        }
    }
}

//Cancela o voo (e reserva a ele vinculadas) na array.
void cancel_voo_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    char consult_voo[TAM_NUM_VOO];
    int controle, voo_indice, res_indice, marcador;

    while(1){ //Lendo e validando numero de voo
        printf("Digite o numero do voo no formato JEB-XXXX: ");
        scanf("%s", consult_voo);
        if (val_num_voo(consult_voo) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int k = 0; k < strlen(consult_voo); k++){ //Passando as letras do voo para maiusculo.
                consult_voo[k] = toupper(consult_voo[k]);
            }

            for (int i = 0; i < qtd_voos; i++){
                if (strcmp(lista_voos[i].num_voo, consult_voo) == 0) {
                    controle++;     //Verifica quantos voos existem com o numero informado
                    marcador = lista_voos[i].status;    //Verifica o status original do voo.
                    voo_indice = i;     //Retorna o indice em que foi encontrado o voo pesquisado
                }
            }

            if (controle == 0){
                printf ("O voo informado nao esta cadastrado no sistema. Pesquise por outro voo. ");
            }
            else {
                break;
            }
        }
    }

    if (marcador != 0) { //Verifica se o voo que se pretende cancelar ja estava cancelado
        printf("\nErro! O voo %s ja havia sido cancelado antes.\n\n", consult_voo);
    }
    else if (val_data(lista_voos[voo_indice].data) == 4){ //Verifica se o voo que se pretende cancelar ja ocorreu
        printf("\nErro! O voo %s ja ocorreu.\n\n", consult_voo);
    }
    else {
        lista_voos[voo_indice].status = 1; //Cancelando o voo na array.

        printf("\n\n\n===================================================================\n");
        printf("                            CANCELAMENTO DE VOOS\n");
        printf("===================================================================\n");
        printf("O voo %s foi cancelado com sucesso\n", consult_voo);
        printf("-------------------------------------------------------------------\n\n");

        for (int j = 0; j < qtd_res; j++) { //Cancelando todas reservas vinculadas ao voo na array.
            if (strcmp(lista_res[j].num_voo, consult_voo) == 0) {
                lista_res[j].status = 1;
                printf("Reserva %s, atrelada ao voo %s, cancelada com sucesso\n\n", lista_res[j].num_reserva, consult_voo);
                printf("-------------------------------------------------------------------\n");
            }
        }
    }
}

//Cancela reserva na array.
void cancel_res_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    int controle_res = 0;
    int marcador = 0;
    int contador = 0;
    int res_indice = 0;
    int voo_indice = 0;
    char num_voo[TAM_NUM_VOO] = "";
    char consult_res[TAM_NUM_RES] = "";

    while(1){ //Lendo e validando numero da reserva
        printf("Digite o numero da reserva no formato GB-XXXXXX: ");
        scanf("%s", consult_res);
        if (val_num_reserva(consult_res) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int i = 0; i < strlen(consult_res); i++){ //Tornando as letras maiusculas
            consult_res[i] = toupper(consult_res[i]);
            }

            controle_res = 0; //Verificando se a reserva já existe no sistema
            for (int i = 0; i < qtd_res; i++){
                if(strcmp(lista_res[i].num_reserva, consult_res) == 0) {
                    controle_res++;
                    marcador = lista_res[i].status; //Status original da reserva.
                    res_indice = i;
                    strcpy(num_voo, lista_res[i].num_voo);
                }
            }

            if (controle_res == 0){ //Verificando se a reserva esta cadastrada.
                printf ("A reservao informada nao esta cadastrada no sistema. Pesquise por outra reserva. ");
            }
            else {
                break;
            }
        }
    }

    for (int i = 0; i < qtd_voos; i++) {
        if(strcmp(lista_voos[i].num_voo, num_voo) == 0){
            voo_indice = i; //Retorna o indice do voo buscado na array de voos
        }
    }

    if (marcador != 0) { //Verifica se a reserva que se busca cancelar ja nao estava cancelada
        printf("\nErro! A reserva %s ja havia sido cancelada antes\n\n", consult_res);
    }

    else if (val_data(lista_voos[voo_indice].data) == 4){ //Verifica se a reserva nao se refere a voo que ja ocorreu
        printf("\nErro! O voo vinculado a reserva %s ja ocorreu\n\n", consult_res);
    }
    else {
        lista_res[res_indice].status = 1; //Cancelando o voo na array.

        printf("\n\n\n===================================================================\n");
        printf("                      CANCELAMENTO DE RESERVAS\n");
        printf("===================================================================\n");
        printf("A reserva %s foi cancelada com sucesso\n", consult_res);
        printf("-------------------------------------------------------------------\n\n");
    }
}

//Exclui o voo (e reserva a ele vinculadas) na array. Retorna o numero de reservas excluidas.
int exclui_voo_array (Voo lista_voos[], Reserva lista_res[], int qtd_voos, int qtd_res)
{
    Reserva lista_prov_res[TAM_LISTA_RES];
    char consult_voo[TAM_NUM_VOO];
    int controle, voo_indice, res_indice;
    int contador = 0;
    int res_exc = 0;
    Voo temp;

    while(1){ //Lendo e validando o numero do voo
        printf("Digite o numero do voo no formato JEB-XXXX: ");
        scanf("%s", consult_voo);
        if (val_num_voo(consult_voo) != 1) {
            printf("Formato incorreto. ");
        }
        else{
            for (int k = 0; k < strlen(consult_voo); k++){ //Passando as letras do voo para maiusculo.
                consult_voo[k] = toupper(consult_voo[k]);
            }

            for (int i = 0; i < qtd_voos; i++){
                if (strcmp(lista_voos[i].num_voo, consult_voo) == 0) {
                    controle++;
                    voo_indice = i;
                }
            }

            if (controle == 0){ //Verificando se o voo esta cadastrado no sistema
                printf ("O voo informado nao esta cadastrado no sistema. Pesquise por outro voo. "); //020
            }
            else {
                break;
            }
        }
    }

    for (int i = (voo_indice + 1); i < qtd_voos; i++){            //Excluindo voo e sobrescrevendo cada um pelo sucessivo.
        strcpy(lista_voos[i - 1].num_voo, lista_voos[i].num_voo);
        strcpy(lista_voos[i - 1].data, lista_voos[i].data);
        strcpy(lista_voos[i - 1].horario, lista_voos[i].horario);
        lista_voos[i - 1].status = lista_voos[i].status;
        lista_voos[i - 1].capacidade = lista_voos[i].capacidade;
    }

        lista_voos[qtd_voos - 1].num_voo[0] = '\0'; //Limpando os lixos que ficam no fim da array (ultima posicao)
        lista_voos[qtd_voos - 1].data[0] = '\0';
        lista_voos[qtd_voos - 1].horario[0] = '\0';
        lista_voos[qtd_voos - 1].status = 100;
        lista_voos[qtd_voos - 1].capacidade = 100;

        printf("\n\n\n===================================================================\n");
        printf("                            EXCLUSAO DE VOOS\n");
        printf("===================================================================\n");
        printf("O voo %s foi excluido com sucesso\n", consult_voo);
        printf("-------------------------------------------------------------------\n\n");

       for (int j = 0; j < qtd_res; j++) {          //Verificando as reservas que serao excluidas e imprimindo a informacao.
            if (strcmp(lista_res[j].num_voo, consult_voo) == 0) {
                printf("Reserva %s, atrelada ao voo %s, excluida com sucesso\n\n", lista_res[j].num_reserva, consult_voo);
                printf("-------------------------------------------------------------------\n");
                res_exc++;
            }
            else {                                  //Passando as reservas nao excluidas para uma array provisoria
                strcpy(lista_prov_res[contador].num_reserva, lista_res[j].num_reserva);
                strcpy(lista_prov_res[contador].num_voo, lista_res[j].num_voo);
                strcpy(lista_prov_res[contador].cpf, lista_res[j].cpf);
                strcpy(lista_prov_res[contador].nome, lista_res[j].nome);
                strcpy(lista_prov_res[contador].nascimento, lista_res[j].nascimento);
                lista_prov_res[contador].sexo = lista_res[j].sexo;
                lista_prov_res[contador].status = lista_res[j].status;
                contador++;
            }
       }

       for (int j = 0; j < contador; j++) {          //Passando as reservas de volta da array provisoria para a original
            strcpy(lista_res[j].num_reserva, lista_prov_res[j].num_reserva);
            strcpy(lista_res[j].num_voo, lista_prov_res[j].num_voo);
            strcpy(lista_res[j].cpf, lista_prov_res[j].cpf);
            strcpy(lista_res[j].nome, lista_prov_res[j].nome);
            strcpy(lista_res[j].nascimento, lista_prov_res[j].nascimento);
            lista_res[j].sexo = lista_prov_res[j].sexo;
            lista_res[j].status = lista_prov_res[j].status;
        }

    return res_exc;
}

//Imprime todos os voos cadastrados e os dados relacionados a cada um deles.
void consulta_voos_cadastrados (Voo lista_voos[], int qtd_voos)
{
    printf("\n\n\n===========================================\n"); //Imprimindo voos registrados no sistema
    printf("          VOOS REGISTRADOS NO SISTEMA\n");
    printf("===========================================\n\n");
    char status_voo[6];
    for (int i = 0; i < qtd_voos; i++) {
        if (lista_voos[i].status == 0) {
            strcpy(status_voo, "ATIVO");
        }
        else {
            strcpy(status_voo, "CANCE");
        }

        printf("%s %s %s %s %d\n", lista_voos[i].num_voo, lista_voos[i].data, lista_voos[i].horario,
                status_voo, lista_voos[i].capacidade);
        printf("-------------------------------------------\n");
    }
}

//Imprime todas as reservas cadastradas e os dados relacionados a cada um delas.
void consulta_res_cadastradas (Reserva lista_res[], int qtd_res)
{
    //Imprimindo as reservas registradas no sistema
    printf("\n\n\n=====================================================================================================================\n");
    printf("                                         RESERVAS REGISTRADAS NO SISTEMA\n");
    printf("=====================================================================================================================\n\n");
    char sexo[TAM_SEXO];
    char status[TAM_STATUS];
    char vazio[10] = "         ";

    for (int i = 0; i < qtd_res; i++) {
        if (lista_res[i].status == 0) {
            strcpy(status, "ATIVO");  //O status do voo sera ATIVO para 0 e CANCELADO para outros numeros.
        }
        else {
            strcpy(status, "CANCE");
        }

        if (lista_res[i].sexo == 0) { //O sexo sera MASCULINO para 0, FEMININO para 1 e 0 para OUTROS.
            strcpy(sexo, "MASCU");
        }
        else if (lista_res[i].sexo == 1) {
            strcpy(sexo, "FEMIN");
        }
        else {
            strcpy(sexo, "OUTRO");
        }

        printf("%-3d  %s   %s   %s   %-45s   %s   %s   %s\n", i, lista_res[i].num_reserva, lista_res[i].num_voo, lista_res[i].cpf,
                lista_res[i].nome, lista_res[i].nascimento, sexo, status);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
    }
}

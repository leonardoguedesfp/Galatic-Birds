#include "tools.h"
#include "voo_reserva.h"
#include "menu.h"

//Validacao de data. Retorna 0 (erro/formato), 2 (erro/dia) 3 (erro/mes). Para datas validas, 1 (datas futuras) e 4 (passadas).
int val_data(char data[])
{
    char dd[3] = "";
    char mm[3] = "";
    char aa[5] = "";
    int dia, mes, ano = 0;
    int dia_atual, mes_atual, ano_atual = 0;


    if (strlen(data) != 10) { //Teste de formato: Posicao das barras e digitos
        return 0;
    }

    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }


    if (!isdigit(data[0]) || !isdigit(data[1]) || !isdigit(data[3]) || !isdigit(data[4]) ||
        !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9])) {
        return 0;
    }

    for (int i = 0; i < strlen(data); i++){ //Transformando em inteiros cada grupo de digitos (dia, mes e ano)
        if (i == 0 || i == 1) {
            dd[i] = data[i];
        }
        else if (i == 3 || i == 4) {
            mm[i - 3] = data[i];
        }
        else {
            aa[i - 6] = data[i];
        }
    }

    dia = atoi(dd);
    mes = atoi(mm);
    ano = atoi (aa);


    if (dia <= 0 || mes <= 0 || ano <= 0) { //Teste de formato: Evitando dia, mes ou ano negativos
        return 0;
    }

    if (mes > 12) {
        return 3; //mes inexistente
    }

    switch(mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (dia > 31) {
                return 2; //dia inexistente.
            }
        break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (dia > 30) {
                return 2; //dia inexistente.
            }
        break;
        case 2:
             if (ano % 4 == 0) {
                if (ano % 100 == 0) {
                    if (ano % 400 == 0) { //e bissexto
                        if (dia > 29) {
                            return 2;
                        }
                    else { //nao e bissexto
                        if (dia > 28) {
                            return 2;
                        }
                else { //e bissexto
                    if (dia > 29) {
                        return 2;
                    }
                }
                    }
                    }
                }
            }
            else { //nao e bissexto
                if (dia > 28) {
                    return 2;
                }
            }
        break;
    }


    struct tm *data_atual;              //Verificar se a data e passada ou futura
    time_t segundos;

    time(&segundos);

    data_atual = localtime(&segundos);

    dia_atual = data_atual->tm_mday;
    mes_atual = data_atual->tm_mon+1;
    ano_atual = data_atual->tm_year+1900;

    if (ano - ano_atual > 0){
        return 1;                           //data futura
    }
    else if (ano - ano_atual < 0){
        return 4;                           //data passada
    }
    else {                                  //Anos sao iguais
        if (mes - mes_atual > 0){
            return 1;                       //data futura
        }
        else if (mes - mes_atual < 0){
            return 4;                       //data passada
        }
            else {
                if (dia - dia_atual >= 0) {
                    return 1;               //data futura
                }
                else if (dia - dia_atual < 0){
                    return 4;               //data passada
                }
            }
    }
}

// Validacao de numero de Voo (foramto JEB-XXXX).Retorna 1 para número de voo valido e 0 invalido.
int val_num_voo(char num_voo[])
{
    if (strlen(num_voo) != 8) { //Verificando se o numero do voo foi informado com 8 posicoes.
        return 0;
    }

    if (strncmp(num_voo, "JEB-", 4) != 0 && strncmp(num_voo, "jeb-", 4) != 0 ) { //Verificando correcao da parte alfabetica
        return 0;
    }


//Verificando se os 4 ultimos digitos são numericos.
    if (!isdigit(num_voo[4]) || !isdigit(num_voo[5]) || !isdigit(num_voo[6]) || !isdigit(num_voo[7])) {
        return 0;
    }

    return 1;
}

//Validacao de numero de Reserva (formato GB-XXXXXX).Retorna 1 para numero de reserva valido e 0 invalido.
int val_num_reserva(char num_reserva[])
{
    if (strlen(num_reserva) != 9) { //Verificando se a reserva do voo foi informada com 9 posicoes.
        return 0;
    }

    if (strncmp(num_reserva, "GB-", 3) != 0 && strncmp(num_reserva, "gb-", 3) != 0 ) { //Verificando correcao da parte alfabetica
        return 0;
    }

//Verificando se os 6 ultimos digitos são numericos.
    if (!isdigit(num_reserva[3]) || !isdigit(num_reserva[4]) || !isdigit(num_reserva[5])
        || !isdigit(num_reserva[6]) || !isdigit(num_reserva[7]) || !isdigit(num_reserva[8])) {
        return 0;
    }

    return 1;
}

//Validacao de horario (formato hh:mm). Retorna 1 (horário valido), 0 (formato errado), 2 (hora errada) e 3 (minuto errado).
int val_hora(char horario[])
{
    char hh[3];
    char mm[3];
    int hora;
    int min;

    if (strlen(horario) != 5) { //Verificando se o horario foi informado com 5 posicoes.
        return 0;
    }

    if (horario[2] != ':') { //Verificando se o separador (:) foi posicionado no lugar correto.
        return 0;
    }

//Verificando se os 2 primeiros e os 2 ultimos digitos são numericos.
    if (!isdigit(horario[0]) || !isdigit(horario[1]) || !isdigit(horario[3]) || !isdigit(horario[4])) {
        return 0;
    }
//Verificando se as horas e os minutos respeitam os limites (0 a 23 para horas e 0 a 60 para minutos)
    for (int i = 0; i <= 1; i++){
        hh[i] = horario[i];
    }

    for (int j = 3; j <= 4; j++){
        mm[j - 3] = horario[j];
    }

    hora = atoi(hh);
    min = atoi(mm);


    if (hora > 23 || hora < 0) {
        return 2;
    }

    if (min > 59 || min < 0) {
        return 3;
    }
    return 1;
}

//Validacao de CPF. Retorna 1 para CPF valido, 2 para CPF com formato incorreto e 0 para CPF invalido.
int val_CPF(char *cpf)
{
    int i, j;
    int dig1 = 0, dig2 = 0;
    if(strlen(cpf) != 11) {
        return 2; //CPF invalido por ter o tamanho inadequado.
    }
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0)) {
        return 0; //CPF invalido por ter todos os digitos iguais.
    }
    else{
        for(i = 0, j = 10; i < 9; i++, j--) {
            dig1 += (cpf[i]-48) * j;
        }
        dig1 %= 11;
        if(dig1 < 2){
            dig1 = 0;
        }
        else {
            dig1 = 11 - dig1;
        }
        if((cpf[9]-48) != dig1) {
            return 0;
        }
            /*
            CPF invalido ja que o digito 1 nao bate com a validacao (multiplicacao dos numeros por 10 a 2, divisao do somatorio
            dos resultados por 11. Validacao e igual ao resto, sendo que 0 e 1 retornam 0)
            */
        else {
            for(i = 0, j = 11; i < 10; i++, j--)
                    dig2 += (cpf[i]-48) * j;
            dig2 %= 11;
            if(dig2 < 2) {
                dig2 = 0;
            }
            else {
                dig2 = 11 - dig2;
            }
            if((cpf[10]-48) != dig2) {
                return 0;
            }
                /*
                CPF invalido já que o digito 2 nao bate com a validacao (multiplicacao dos numeros, inclusive dig1, por 11 a 2.
                Divisao do somatorio dos resultados por 11. Validacao e igual ao numero 11 menos o resto (0 e 1 retornam sempre 0).
                */
        }
    }
    return 1;
}



#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//Validacao de data. Retorna 0 (erro/formato), 2 (erro/dia) 3 (erro/mes). Para datas validas, 1 (datas futuras) e 4 (passadas).
int val_data(char data[]);

// Validacao de numero de Voo (foramto JEB-XXXX).Retorna 1 para número de voo valido e 0 invalido.
int val_num_voo(char num_voo[]);

//Validacao de numero de Reserva (formato GB-XXXXXX).Retorna 1 para numero de reserva valido e 0 invalido.
int val_num_reserva(char num_reserva[]);

//Validacao de horario (formato hh:mm). Retorna 1 (horário valido), 0 (formato errado), 2 (hora errada) e 3 (minuto errado).
int val_hora(char horario[]);

//Validacao de CPF. Retorna 1 para CPF valido, 2 para CPF com formato incorreto e 0 para CPF invalido.
int val_CPF(char *cpf);


#endif // TOOLS_H




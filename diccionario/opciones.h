/* 
 * File:   opciones.h
 * Author: Alfredo
 *
 * Created on 30 de enero de 2014, 04:40 PM
 */

#ifndef OPCIONES_H
#define	OPCIONES_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "atributo.h"

#define MAX_COMANDS 100



#define ACCION_T 1
#define ATRIBUTO_T 2


typedef struct params_t{
    char N[TAM_NOMBRE]; //parametro nombre
    char D[TAM_NOMBRE]; //parametro diccionario
    char T[TAM_NOMBRE]; //parametro tipo
    char E[TAM_NOMBRE]; //parametro entidad
    char S[TAM_NOMBRE]; //parmetro size (tamano)
    char K[TAM_NOMBRE]; //parametro llave (key)

    char ME[TAM_NOMBRE]; //parametro opcion modifica entidad
    char AE[TAM_NOMBRE]; //parametro opcion alta entidad
    char BE[TAM_NOMBRE]; //parametro opcion baja entidad
    char MA[TAM_NOMBRE]; //parametro opcion modifica atributo
    char AA[TAM_NOMBRE]; //parametro opcion alta atributo
    char BA[TAM_NOMBRE]; //parametro opcion baja atributo
    char CE[TAM_NOMBRE]; //parametro opcion consulta entidad
    char C[TAM_NOMBRE];  //consulta (todas la entidades)
    
}params;

typedef struct comando_t{
    char opcion[20];
    char parametro[100];
    int tipo;
} comando;

class opciones {
public:
    opciones(int numeroArgumentos, char** nombreArgumentos, int isConsole);
    opciones(const opciones& orig);
    virtual ~opciones();

    int isEjecutable();
    int getNumComandos();
    comando getComando(int index);
private:
    int isValid(comando comand);
    int fillOptions(int numArgs,char** nomArgs);
    int _isValid;
    int _numcomands;
    comando _comands[MAX_COMANDS];



};

#endif	/* OPCIONES_H */


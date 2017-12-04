/* 
 * File:   Registro.h
 * Author: alfredo
 *
 * Created on 8 de abril de 2014, 12:46 PM
 */

#ifndef Registro_H
#define	Registro_H


#include <stdlib.h>
#include "archivo.h"
#include "entidad.h"
#include "atributo.h"
#include "consola.h"

class Registro {
public:
    Registro();
    Registro(Entidad* ent, Archivo *arch);
    Registro(const Registro& orig);
    virtual ~Registro();
    
    void setSiguiente(DIR_t siguiente);
    DIR_t getSiguiente();
    
    void empaqueta(void* dato, Atributo *AtrDestino);
    void* desempaqueta(Atributo* atr);
    char* getBuffer();
    void setBuffer(char*);
    int  getSize();
    int compara(Registro* reg, Atributo* atr);
    void imprime();
private:
    Entidad *_ent;
    Archivo *_dic;
    int _desp;
    int _tam;
    char* _datos;

};

#endif	/* Registro_H */


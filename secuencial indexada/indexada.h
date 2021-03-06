/* 
 * File:   Indexada.h
 * Author: alfredo
 *
 * Created on 8 de abril de 2014, 12:45 PM
 */

#ifndef INDEXADA_H
#define	INDEXADA_H
#include "consola.h"
#include "archivo.h"
#include "entidad.h"
#include "atributo.h"
#include "registro.h"
#include "indice.h"

#include "error.h"
#include <ctype.h>

class Indexada {
public:
    Indexada(char* nombreDic);
    Indexada(const Indexada& orig);
    
    static int ImportaDiccionario(char* nombreDic, char* nombreSec);
    int AltaIndexada(char* nomEntidad);
    int BajaIndexada(char* nomEntidad, char* key);
    int ModificaIndexada(char* nomEntidad, char* key);
    int ConsultaIndexada(char* nomentidad="");
   
    virtual ~Indexada();
private:
    Registro* pideRegistro(Entidad* ent);
    Registro* pideRegistroFrom(Entidad* ent,Registro *reg);
    int insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg, Indice* indice, DIR_t posind);
    
    DIR_t eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,Indice* indice, DIR_t posind);
    
    int buscaRegistro(Entidad* ent, Registro* reg,Indice* indice);
    Registro* buscaReg(Entidad* ent, Registro* reg, DIR_t *pos,Indice* indice);
    
    Entidad* buscaEnt(char* nombre);
    int buscaEntidad(char* nombre); 
    int buscaEntidad(Entidad* entidad);
    
    Indice* dameIndice(Entidad* ent, Registro* reg, DIR_t *posIndice);
    Indice* buscaIndice(Entidad* ent, Registro* reg, Atributo* atrPrimario, DIR_t *posIndice);
    DIR_t eliminaIndice();
    void InsertaIndice(Entidad* ent,DIR_t posent,Indice* ind, DIR_t posind);
    
    DIR_t getPosEnt(char* NombreEntidad);
    Atributo* getAtrPrimario(Entidad* ent);
    
    void* pideDato(Atributo* atr);
    void* pideDatoFrom(Atributo* atr,void* dato);
    int esEntero(char* cad);
    int esDecimal(char* cad);
    
    char* _nomdic;
    Archivo* _arch;
    Consola *_cons;
    

};

#endif	/* INDEXADA_H */


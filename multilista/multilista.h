/* 
 * File:   Multilista.h
 * Author: alfredo
 *
 * Created on 8 de abril de 2014, 12:45 PM
 */

#ifndef MULTILISTA_H
#define	MULTILISTA_H
#include "consola.h"
#include "archivo.h"
#include "entidad.h"
#include "atributo.h"
#include "registro.h"
#include "indice.h"

#include "error.h"
#include "listabloque.h"
#include <ctype.h>

class Multilista {
public:
    Multilista(char* nombreDic);
    Multilista(const Multilista& orig);
    
    static int ImportaDiccionario(char* nombreDic, char* nombreSec);
    int AltaMultilista(char* nomEntidad);
    int BajaMultilista(char* nomEntidad,char* nomAtributo, char* key);
    int ModificaMultilista(char* nomEntidad,char* nomAtributo, char* key);
    int ConsultaMultilista(char* nomentidad, char* nomatributo);
   
    virtual ~Multilista();
private:
    Registro* pideRegistro(Entidad* ent);
    Registro* pideRegistroFrom(Entidad* ent,Registro *reg);
    int insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg, Indice* indice, DIR_t posind);
    
    DIR_t eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,Indice* indice, DIR_t posind);
    
    int buscaRegistro(Entidad* ent, Registro* reg,Indice* indice);
    Registro* buscaReg(Entidad* ent, Registro* reg, DIR_t *pos,Indice* indice);
    listabloque* buscaRegistros(Entidad* ent, Registro* reg, Atributo* atrRef);
    
    int isRegistroEqual(Entidad* ent, Registro *r1,Registro *r2);
    Entidad* buscaEnt(char* nombre);
    int buscaEntidad(char* nombre); 
    int buscaEntidad(Entidad* entidad);
    
    Atributo* buscaAtr(Entidad* entidad, char* nombreAtributo);
    int buscaAtributo(Entidad* entidad, char* nombreAtributo); 
    int buscaAtributo(Entidad* entidad,Atributo* atributo);
    
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

#endif	/* MULTILISTA_H */


/* 
 * File:   Secuencial.h
 * Author: alfredo
 *
 * Created on 8 de abril de 2014, 12:45 PM
 */

#ifndef SECUENCIAL_H
#define	SECUENCIAL_H
#include "consola.h"
#include "archivo.h"
#include "entidad.h"
#include "atributo.h"
#include "registro.h"

#include "error.h"
#include <ctype.h>

class Secuencial {
public:
    Secuencial(char* nombreDic);
    Secuencial(const Secuencial& orig);
    
    static int ImportaDiccionario(char* nombreDic, char* nombreSec);
    int AltaSecuencial(char* nomEntidad);
    int BajaSecuencial(char* nomEntidad, char* key);
    int ModificaSecuencial(char* nomEntidad, char* key);
    int ConsultaSecuencial(char* nomentidad="");
   
    virtual ~Secuencial();
private:
    Registro* pideRegistro(Entidad* ent);
    Registro* pideRegistroFrom(Entidad* ent,Registro *reg);
    int insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg);
    DIR_t eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg);
    int buscaRegistro(Entidad* ent, Registro* reg);
    Registro* buscaReg(Entidad* ent, Registro* reg, DIR_t *pos);
    
    Entidad* buscaEnt(char* nombre);
    int buscaEntidad(char* nombre); 
    int buscaEntidad(Entidad* entidad);
    
    
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

#endif	/* SECUENCIAL_H */


/* 
 * File:   diccionario.h
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 *
 * Created on 28 de enero de 2014, 04:57 PM
 *
 * Descripción:
 */

#ifndef DICCIONARIO_H
#define	DICCIONARIO_H

#include "archivo.h"
#include "entidad.h"
#include "atributo.h"

class Diccionario {
public:
    Diccionario();
    Diccionario(char* nombre);
    Diccionario( Diccionario& orig);
    virtual ~Diccionario();

    int altaEntidad(char* nombre);
    int bajaEntidad(char* nombre);
    int modificaEntidad(char* nombre, char* nombre_nuevo);
    
    int altaAtributo(Atributo atributo, Entidad entidad);
    int bajaAtributo(Atributo atributo, Entidad entidad);
    int modificaAtributo(Atributo atributo, Atributo nuevo, Entidad entidad);
    
    void consultaEntidades();
    void consultaEntidad(char* nombre);
    void consultaAtributos(char* nombreEntidad);
    
    int creaDiccionario();
    int creaDiccionario(char* nombre);

    char* getNombre();

   
private:

    int insertaEntidad(Entidad *entidad,DIR_t direccion);
    DIR_t eliminaEntidad(char* nombre);    
    Entidad* buscaEnt(char* nombre);
    int buscaEntidad(char* nombre); 
    int buscaEntidad(Entidad* entidad);
   

    int insertaAtributo(Entidad *entidad,DIR_t dir_entidad,Atributo* atributo,DIR_t dir_atributo);
    DIR_t eliminaAtributo(Entidad *entidad,DIR_t dir_entidad, char* nombre_atributo);
    Atributo* buscaAtr(char* nombre_entidad,char* nombre_atributo);
    int buscaAtributo(char* nombre_entidad,char* nombre_atributo);    
    int buscaAtributo(Entidad* entidad,Atributo* atributo);


    char _nombre[FILENAME_MAX];
    Archivo* _arch;

};

#endif	/* DICCIONARIO_H */


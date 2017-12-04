/* 
 * File:   archivo.h
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 *
 * Created on 28 de enero de 2014, 04:58 PM
 *
 * Descripción: *
 *
 *      Clase para manipular un archivo en modo binario en el cual
 *      se manipulan las entidades y los atributos del diccionario
 *      de datos.
 */

#ifndef ARCHIVO_H
#define	ARCHIVO_H


#include <stdio.h>
#include <string.h>

#include "entidad.h"
#include "atributo.h"
#include "indice.h"

class Archivo {

public:
    Archivo();
    Archivo(char* nombre);
    Archivo(const Archivo& orig);
    virtual ~Archivo();

    int creaArchivo(char* nombre);
    int creaArchivo();    

    int escribeCab(DIR_t cabecera);
    DIR_t leeCab();

    Entidad* leeEntidad(DIR_t direccion);
    DIR_t escribeEntidad(Entidad*  entidad, DIR_t direccion);
    
    Atributo* leeAtributo(DIR_t direccion);
    DIR_t escribeAtributo(Atributo* atributo, DIR_t direccion);
    
    char* leeBloque(int size,DIR_t direccion);
    DIR_t escribeBloque(char* buffer, int size, DIR_t direccion);
    
    Indice* leeIndice(DIR_t direccion);
    DIR_t escribeIndice(Indice* indice,DIR_t direccion);
    
    DIR_t getDirFin();

private:
    int abreArchivo();
    void cierraArchivo();
    char _nombre[FILENAME_MAX];
    
    FILE* _arch;


};

#endif	/* ARCHIVO_H */


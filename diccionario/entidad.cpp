/* 
 * File:   entidad.cpp
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 * 
 * Created on 28 de enero de 2014, 05:14 PM
 *
 * Descripción:
 *
 * Implementación de los métodos de la clase entidad.
 * ver entidad.h para mas información.
 */


#include "entidad.h"
#include <string.h>



Entidad::Entidad(char* nombre) {

    strcpy(_nombre,nombre);
    _dir_atributos=-1;
    _dir_siguiente=-1;
    _num_atributos=0;
}
Entidad::Entidad() {

    strcpy(_nombre,"");
    _dir_atributos=-1;
    _dir_siguiente=-1;
    _num_atributos=0;
}
Entidad::Entidad(const Entidad& orig) {
}

Entidad::~Entidad() {
}
DIR_t Entidad::getSiguiente(){
    return _dir_siguiente;
}
void Entidad::setSiguiente(DIR_t siguiente){

    _dir_siguiente=siguiente;
}

DIR_t Entidad::getDirAtributos(){
    return _dir_atributos;
}
void Entidad::setDirAtributos(DIR_t dir){
    _dir_atributos=dir;
}

char* Entidad::getNombre(){
    return _nombre;
}
void Entidad::setNombre(char* nombre){
    strcpy(_nombre,nombre);
}

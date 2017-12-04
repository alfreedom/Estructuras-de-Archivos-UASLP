/* 
 * File:   indice.cpp
 * Author: alfredo
 * 
 * Created on 14 de mayo de 2014, 04:36 PM
 */

#include <stddef.h>
#include <stdio.h>
#include "indice.h"

Indice::Indice() {
    _sig=EOF;
    _datos=EOF;
    _inicio=0;
    _fin=0;
}
Indice::Indice(int inicio, int fin){
    
    _sig=EOF;
    _datos=EOF;
    _inicio=inicio;
    _fin=fin;
   
    
}
Indice::Indice(const Indice& orig) {
}

Indice::~Indice() {
}

DIR_t Indice::getSig(){
    return _sig;
}
void Indice::setSig(DIR_t sig){
    _sig=sig;
}

DIR_t Indice::getPtrDatos(){
    return _datos;
}
void Indice::setPtrDatos(DIR_t ptrDatos){
    _datos=ptrDatos;
}

int Indice::getInicio(){
    return _inicio;
}
void Indice::setInicio(int inicio){
    _inicio=inicio;
}
int Indice::getFin(){
    return _fin;
}
void Indice::setFin(int fin){
    _fin=fin;
}
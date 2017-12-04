/* 
 * File:   atributo.cpp
 * Author: Alfredo
 * 
 * Created on 10 de febrero de 2014, 03:06 PM
 */

#include "atributo.h"
#include <string.h>

Atributo::Atributo() {
}

Atributo::Atributo(char* Nombre,TIPO_T Tipo,int Size,LLAVE Llave){
	
	strcpy(_nombre,Nombre);
	_tipo=Tipo;
	_tam=Size;
	_llave=Llave;
	_ptr_datos=-1;
	_ptr_foraneo=-1;
	_atr_sig=-1;
}
Atributo::Atributo(const Atributo& orig) {
}

Atributo::~Atributo() {
}

char*	Atributo::getNombre(){
	return _nombre;
}
void	Atributo::setNombre(char* Nombre){
	strcpy(_nombre,Nombre);
}

TIPO_T	Atributo::getTipo(){
	return _tipo;
}
void	Atributo::setTipo(TIPO_T Tipo){
	_tipo=Tipo;
}

int		Atributo::getSize(){
	return _tam;
}
void	Atributo::setSize(int Size){
	_tam=Size;
}

LLAVE	Atributo::getLlave(){
	return _llave;
}
void	Atributo::setLlave(LLAVE Llave){
	_llave=Llave;
}

DIR_t	Atributo::getSiguiente(){
	return _atr_sig;
}
void	Atributo::setSiguiente(DIR_t Siguiente){
	_atr_sig=Siguiente;
}

DIR_t	Atributo::getPtrForaneo(){
	return _ptr_foraneo;
}
void	Atributo::setPtrForaneo(DIR_t PtrForaneo){
	_ptr_foraneo=PtrForaneo;
}

DIR_t	Atributo::getPtrDatos(){
	return _ptr_datos;
}
void	Atributo::setPtrDatos(DIR_t PtrDatos){
	_ptr_datos=PtrDatos;
}

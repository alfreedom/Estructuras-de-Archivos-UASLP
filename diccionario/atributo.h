/* 
 * File:   atributo.h
 * Author: Alfredo
 *
 * Created on 10 de febrero de 2014, 03:06 PM
 */

#ifndef ATRIBUTO_H
#define	ATRIBUTO_H

#define TAM_NOMBRE  30

typedef  long DIR_t;
typedef unsigned char byte;

enum TIPO_T{
	ENTERO,
	CADENA,
	FLOTANTE,
	DOBLE,
	CARACTER
};

/*Enumeración para los tipos de llaves:
	NONE = sin llave.
	PRIMARIA = el atributo es llave primaria
	FORANEA = el atributo es llave foranea*/
enum LLAVE{
	NONE,
	PRIMARIA,
	FORANEA,
};


class Atributo {
public:
    Atributo();
    Atributo(char* Nombre,TIPO_T Tipo = ENTERO,int Size = 0,LLAVE Llave = NONE);
    Atributo(const Atributo& orig);
    
    char*	getNombre();
    void	setNombre(char* Nombre);
    
    TIPO_T	getTipo();
    void	setTipo(TIPO_T Tipo);
    
    int		getSize();
    void	setSize(int Size);
    
    LLAVE	getLlave();
    void	setLlave(LLAVE Llave);
    
    DIR_t	getSiguiente();
    void	setSiguiente(DIR_t Siguiente);
    
    DIR_t	getPtrForaneo();
    void	setPtrForaneo(DIR_t PtrForaneo);
    
    DIR_t	getPtrDatos();
    void	setPtrDatos(DIR_t PtrDatos);
    
    
    virtual ~Atributo();
private:
    char    _nombre[TAM_NOMBRE];    
    TIPO_T  _tipo;
    int     _tam;
    LLAVE   _llave;
    
    DIR_t   _atr_sig;
    DIR_t   _ptr_datos;
    DIR_t   _ptr_foraneo;

};

#endif	/* ATRIBUTO_H */


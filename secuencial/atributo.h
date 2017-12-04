/* 
 * Proyecto: Diccionario de datos.
 * 
 * File:   atributo.h
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 * 
 *
 * Created on 10 de febrero de 2014, 03:06 PM
 * 
 * * Descripción:
 *
 *      Clase para crear y manipular atributos del diccionario de datos.
 *      Esta clase define los datos que se guardaran en el archivo, el tamaño
 *      de esta clase será el tamaño del bloque de datos del atributo que se 
 *      escribiran en archivo. La clase cuenta con metodos para obtener, 
 *      establecer o hacer operaciones sobre los campos del atributo.
 *
 * Métodos implementados:
 *
 *
 *       Atributo(char* Nombre,TIPO_T Tipo = ENTERO,int Size = 0,LLAVE Llave = NONE)
 *          Constructor de la clase atributo, recibe el nombre del atributo y 
 *          opcionalmente el tipo, el tamaño y la llave
 *
 *              Nombre:  Nombre que se le asignara al atributo. 
 *              Tipo:    Tipo de dato del atributo (1:int 2:long 3:string 4:float 5:double 6:string)
 *              Size:    Tamaño en bytes del atributo.
 *              Llave:   Tipo de llave del atributo (0:Ninguna 1:primaria)   
 *
 *      DIR_t getSiguiente()
 *          Devuelve la dirección del siguiente atributo apunta.
 *
 *      void setSiguiente(DIR_t siguiente)
 *          Establece la direccion del siguiente atributo al que se debe
 *          apuntar.
 *
 *      TIPO_T getTipo()
 *          Devuelve el tipo del atributo.
 *      
 *      void setTipo();
 *          Establece el tipo del atributo.
 * 
 *      LLAVE getLlave()
 *          Devuelve la llave del atributo.
 *      
 *      void setLlave(LLAVE key);
 *          Establece la llave del atributo.
 * 
 *      int getSize()
 *          Devuelve el tamaño atributo.
 *      
 *      void setSize(int size);
 *          Establece el tamaño del atributo.
 * 
 *      DIR_t getPtrDatos()
 *          Devuelve la dirección del bloque de datos del atributo.
 *      
 *      void setPtrDatos(DIR_t ptrDatos);
 *          Establece la dirección del bloque de datos del atributo.
 * 
 *      DIR_t getPtrForaneo()
 *          Devuelve la dirección de la entidad foranea referenciada por el
 *          atributo..
 *      
 *      void setPtrForaneo(DIR_t ptrForaneo);
 *          Establece la dirección de la entidad foranea referenciada por el
 *          atributo. 
 *
 *      char* getNombre()
 *          Devuelve el nombre del atributo.
 *
 *      void setNombre(char* nombre)
 *          Establece el nombre del atributo.
 *
 *              nombre:  Nombre que se le asignara al atributo.
 *
 */
 

#ifndef ATRIBUTO_H
#define	ATRIBUTO_H

#define TAM_NOMBRE  30

typedef  long DIR_t;
typedef unsigned char byte;

enum TIPO_T{
	ENTERO=1,
        LONG,
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


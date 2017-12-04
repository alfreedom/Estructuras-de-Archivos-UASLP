/* 
 * File:   entidad.h
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 *
 * Created on 28 de enero de 2014, 05:14 PM
 *
 * Descripción:
 *
 *      Clase para crear y manipular entidades del diccionario de datos.
 *      Esta clase define los datos que se guardaran en el archivo, el tamaño
 *      de esta clase será el tamaño del bloque de datos que se escribiran en
 *      archivo. La clase cuenta con metodos para obtener, establecer o hacer
 *      operaciones sobre los atributos de la entidad.
 *
 * Métodos implementados:
 *
 *
 *       Entidad(char* nombre)
 *          Constructor de la clase entidad, recibe el nombre de la entidad
 *          e inicializa los apuntadores y variables internas.
 *
 *              nombre:  Nombre que se le asignara a la entidad.
 *
 *      Entidad()
 *          Constructor de la clase entidad. igual que la anterior, solo que
 *          el nombre de la entidad lo deja vacio.
 *
 *      DIR_t getSiguiente()
 *          Devuelve la dirección de la siguiente entidad a la que apunta.
 *
 *      void setSiguiente(DIR_t siguiente)
 *          Establece la direccion de la siguiente entidad a la que se debe
 *          apuntar.
 *
 *      void setDirAtributos(DIR_t direccion)
 *          Establece la direccion del primer atributo de la lista de atributos
 *          de la entidad.
 *
 *              direccion:  Direccion del primer atributo.
 *
 *      DIR_t getDitAtributos()
 *          Devuelve la direccion del primer atributo de la lista de atributos
 *          de la entidad.
 *
 *      char* getNombre()
 *          Devuelve el nombre actual de la entidad.
 *
 *      void setNombre(char* nombre)
 *          Establece el nombre de la entidad.
 *
 *              nombre:  Nombre que se le asignara a la entidad.
 *
 */

#ifndef ENTIDAD_H
#define	ENTIDAD_H

#define TAM_NOMBRE  30

//tipo de dato definido para las direcciones en archivo.
typedef  long DIR_t;

class Entidad {
public:
    Entidad(char* nombre);
    Entidad();
    Entidad(const Entidad& orig);
    virtual ~Entidad();

    DIR_t getSiguiente();
    void setSiguiente(DIR_t siguiente);

    DIR_t getDirAtributos();
    void setDirAtributos(DIR_t dir);

    char* getNombre();
    void setNombre(char* nombre);
private:
    char _nombre[TAM_NOMBRE];
    DIR_t _dir_siguiente;
    DIR_t _dir_atributos;
    int   _num_atributos;

};

#endif	/* ENTIDAD_H */


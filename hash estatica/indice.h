/* 
 * File:   indice.h
 * Author: alfredo
 *
 * Created on 14 de mayo de 2014, 04:36 PM
 */

#ifndef INDICE_H
#define	INDICE_H
#include "atributo.h"
#include "entidad.h"
#define RANGO 10

class Indice {
public:
    Indice();
    Indice(int inicio,int fin);
    Indice(const Indice& orig);
        
    DIR_t getSig();
    void setSig(DIR_t sig);
    
    DIR_t getPtrDatos();
    void setPtrDatos(DIR_t ptrDatos);
    
    int getInicio();
    void setInicio(int inicio);
    
    int getFin();
    void setFin(int fin);
    
    virtual ~Indice();
private:
    int _inicio;
    int _fin;
    DIR_t _sig;
    DIR_t _datos; 

};

#endif	/* INDICE_H */


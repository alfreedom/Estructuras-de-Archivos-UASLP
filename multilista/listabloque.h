/* 
 * File:   listabloque.h
 * Author: alfredo
 *
 * Created on 29 de mayo de 2014, 11:31 AM
 */

#ifndef LISTABLOQUE_H
#define	LISTABLOQUE_H

#include "registro.h"
#include "atributo.h"

class listabloque {
    
    typedef struct nodor_t{
        Registro* bloque;
        nodor_t* sig;
    }nodor;
public:
    listabloque();
    listabloque(const listabloque& orig);
    virtual ~listabloque();
    
    void Add(Registro* reg);
    void Ordena(Atributo* atrRef);
    void Rewind();
    int  Size();
    Registro* GetNext();
private:
    int count;
    nodor* cab;
    nodor* actual;

};

#endif	/* LISTABLOQUE_H */


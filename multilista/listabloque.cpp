/* 
 * File:   listabloque.cpp
 * Author: alfredo
 * 
 * Created on 29 de mayo de 2014, 11:31 AM
 */

#include "listabloque.h"

listabloque::listabloque() {
    cab=NULL;
    actual=cab;
    count=0;
}

listabloque::listabloque(const listabloque& orig) {
}

listabloque::~listabloque() {
}

void listabloque::Add(Registro* reg){
    nodor* nuevo=new nodor;
    
    nuevo->bloque=reg;
    nuevo->sig=cab;
    if(!cab)
        actual=nuevo;
    cab=nuevo;
    count++;
}
void listabloque::Ordena(Atributo* atrRef){
    
    nodor* aux=cab;
    nodor* aux2;
    
    while(aux){
        
        aux2=aux->sig;
        while(aux2){
            if(aux->bloque->compara(aux2->bloque,atrRef)>0){
                Registro* raux=aux->bloque;
                aux->bloque=aux2->bloque;
                aux2->bloque=raux;
            }
            aux2=aux2->sig;
        }
        
        
        aux=aux->sig;
    }
    
}
void listabloque::Rewind(){
    actual=cab;
}
int  listabloque::Size(){
    return count;
}
Registro* listabloque::GetNext(){
    
    Registro* ret=NULL;
    if(actual){
        ret=actual->bloque;
        actual=actual->sig;
    }
    
    return ret;
}
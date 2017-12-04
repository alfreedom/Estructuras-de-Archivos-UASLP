/* 
 * File:   Registro.cpp
 * Author: alfredo
 * 
 * Created on 8 de abril de 2014, 12:46 PM
 */

#include "registro.h"

Registro::Registro() {
}
Registro::Registro(Entidad* ent, Archivo *arch) {
    
    _ent=ent;
    _dic=arch;
    DIR_t cabatr=ent->getDirAtributos();
    _tam=0;
    while(cabatr!=EOF){
        Atributo* atr=_dic->leeAtributo(cabatr);
        _tam+=atr->getSize();
        cabatr=atr->getSiguiente();
    }
    _tam+=sizeof(DIR_t);
    _datos=new char[_tam];
    *((DIR_t*)_datos+0)=EOF;
}
Registro::Registro(const Registro& orig) {
}

Registro::~Registro() {
}

void copy(char* dest, void* orig, int numbytes){
    for(int i=0;i<numbytes;i++)
        dest[i]=*((char*)orig+i);
}
char* getBytes(void* dato, Atributo *atr){
    
    char* data= new char[atr->getSize()];
    int d;
    switch(atr->getTipo()){
                case ENTERO:                    
                    d=(int)dato;
                    memcpy(data,&d,sizeof(int));
                    break;
                    case CADENA:     
                    memcpy(data,dato,atr->getSize());
                    break;
                
            }
    return data;
}
void Registro::empaqueta(void* dato, Atributo *AtrDestino){
    
    int desp= sizeof(DIR_t);
    DIR_t cabatr;
    cabatr=_ent->getDirAtributos();
    
    int entero;
    float flotante;
    char caracter;
    long largo;
   
    while(cabatr!=EOF){
        Atributo *atr=_dic->leeAtributo(cabatr);
        if(dato){
            if(!strcmp(atr->getNombre(),AtrDestino->getNombre()))
            {
                switch(atr->getTipo()){
                    case ENTERO:
                        entero=(int)dato;
                        memcpy(_datos+desp,&entero,atr->getSize());
                        break;
                    case LONG:
                        largo=(long)dato;
                        memcpy(_datos+desp,&largo,atr->getSize());
                        break;
                    case CADENA:
                        memcpy(_datos+desp,dato,atr->getSize());
                        break;
                    case FLOTANTE:
                    case DOBLE: 
                        flotante=*(float*)dato;
                        memcpy(_datos+desp,&flotante,atr->getSize());
                        break;
                    case CARACTER:
                        caracter=*(char*)dato;
                        memcpy(_datos+desp,&caracter,atr->getSize());
                        break;
                }
            break;
            }
            
        }
        desp+=atr->getSize();
        cabatr=atr->getSiguiente();
    }
    
}
void* Registro::desempaqueta(Atributo* atr){
    
    int desp= sizeof(DIR_t);
    DIR_t cabatr=_ent->getDirAtributos();
    int *entero;
    float *flotante;
    char *caracter;
    long *largo;
    
    
    while(cabatr!=EOF){
        Atributo *_atr=_dic->leeAtributo(cabatr);
        if(!strcmp(_atr->getNombre(),atr->getNombre()))
        {
            switch(atr->getTipo()){
                case ENTERO:
                    entero=new int;
                    memcpy(&entero,_datos+desp,atr->getSize());
                    return entero;
                case LONG:
                    largo=new long;
                    memcpy(&largo,_datos+desp,atr->getSize());
                    return largo;
                case CADENA:
                    return _datos+desp;
                case FLOTANTE:
                case DOBLE: 
                    flotante=new float;
                    memcpy(&flotante,_datos+desp,atr->getSize());
                    return flotante;
                case CARACTER:
                    caracter=new char;
                    memcpy(&caracter,_datos+desp,atr->getSize());
                    return caracter;
                    
            }
                        
        }
        desp+=_atr->getSize();
        cabatr=_atr->getSiguiente();
    }
}
char* Registro::getBuffer(){
    return _datos;
}
void Registro::setBuffer(char* buffer){
    memcpy(_datos,buffer,_tam);
}
int  Registro::getSize(){
    return _tam;
}
void Registro::setSiguiente(DIR_t siguiente){
    *((DIR_t*)_datos+0)=siguiente;
}
DIR_t Registro::getSiguiente(){
    return *((DIR_t*)_datos+0);
}
void Registro::imprime(){
    
    DIR_t cabatr=_ent->getDirAtributos();    
    int d;
    while(cabatr!=EOF){
        Atributo *atr=_dic->leeAtributo(cabatr);
        //printw("%s: ",atr->getNombre());
            switch(atr->getTipo()){
                case ENTERO:
                   
                    printw("%d\t\t",(int)this->desempaqueta(atr));                    
                    break;
                case LONG:
                    printw("%lu\t\t",(long)this->desempaqueta(atr));
                    break;
                case CADENA:
                    printw("%s\t\t",(char*)this->desempaqueta(atr));
                    break;
                case FLOTANTE:
                case DOBLE: 
                    printw("%f\t\t",*(float*)this->desempaqueta(atr));  
                    break;
                case CARACTER:
                    printf("%c\t\t",*(char*)this->desempaqueta(atr)); 
                    break;
            
            
        }
        cabatr=atr->getSiguiente();
    }
}
int Registro::compara(Registro* reg, Atributo* atr){
    
    switch(atr->getTipo()){
            case ENTERO:                
                int i1,i2;
                i1=(int)this->desempaqueta(atr);
                i2=(int)reg->desempaqueta(atr);
               
                if(i1==i2)
                    return 0;
                else if(i1<i2)
                    return -1;
                else
                    return 1;
                break;
            case LONG:
                long l1,l2;
                l1=(long)this->desempaqueta(atr);
                l2=(long)reg->desempaqueta(atr);
                if(l1==l2)
                    return 0;
                else if(l1<l2)
                    return -1;
                else
                    return 1;
                break;
            case CADENA:
                return strcmp((char*)this->desempaqueta(atr),(char*)reg->desempaqueta(atr));
                break;
            case FLOTANTE:
            case DOBLE:                   
                float f1,f2;
                f1=*(float*)this->desempaqueta(atr);               
                f2=*(float*)reg->desempaqueta(atr);
                if(f1==f2)
                    return 0;
                else if(f1<f2)
                    return -1;
                else
                    return 1;
                break;
            case CARACTER:
                char c1,c2;
                c1=*(char*)this->desempaqueta(atr);
                c2=*(char*)reg->desempaqueta(atr);
                if(c1==c2)
                    return 0;
                else if(c1<c2)
                    return -1;
                else
                    return 1;
                break;
        }
}
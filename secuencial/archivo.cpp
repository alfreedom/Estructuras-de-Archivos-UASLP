/* 
 * File:   archivo.cpp
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 * 
 * Created on 28 de enero de 2014, 04:58 PM
 *
 * Descripción:
 *
 * Implementación de los métodos de la clase archivo.
 * ver archivo.h para mas información.
 */

#include <sys/unistd.h>

#include "archivo.h"

Archivo::Archivo() {
    _arch=NULL;
    strcpy(_nombre,"archivo");
}
Archivo::Archivo(char* nombre) {
    _arch=NULL;
    strcpy(_nombre,nombre);
}
Archivo::Archivo(const Archivo& orig) {
}

Archivo::~Archivo() {
   if(_arch)
    cierraArchivo();
}

int Archivo::creaArchivo(char* nombre){

    _arch = fopen(nombre,"wb");
    int ret=0;
    if(_arch)
    {
        this->cierraArchivo();
        ret=1;
    }

    return ret;
}
int Archivo::creaArchivo(){

    return this->creaArchivo(_nombre);
}
int Archivo::abreArchivo(){

    _arch = fopen(_nombre,"rb+");
    return _arch!=NULL;
}
void Archivo::cierraArchivo(){
    fclose(_arch);
    _arch=NULL;
}

int Archivo::escribeCab(DIR_t cabecera){

    int ret=0;
    if(this->abreArchivo())
    {
        fseek(_arch,0,SEEK_SET);
        fwrite(&cabecera,sizeof(DIR_t),1,_arch);
        ret=1;
        this->cierraArchivo();
    }

    return ret;
    
}
DIR_t Archivo::leeCab(){
    DIR_t ret=0;
    if(this->abreArchivo())
    {
        fseek(_arch,0,SEEK_SET);
        fread(&ret,sizeof(DIR_t),1,_arch);
        this->cierraArchivo();return ret;
    }

    return ret;
}

Entidad* Archivo::leeEntidad(DIR_t direccion){
   
    Entidad *ent=NULL;

    if(this->abreArchivo())
    {
        ent=new Entidad();
        fseek(_arch,direccion,SEEK_SET);

        fread(ent,sizeof(Entidad),1,_arch);

        this->cierraArchivo();
    }

    return ent;
}
DIR_t Archivo::escribeEntidad(Entidad*  entidad, DIR_t direccion){
     

    if(this->abreArchivo())
    {
        if(direccion == EOF)
        {
            fseek(_arch,0,SEEK_END);
            direccion=ftell(_arch);
        }
        else
            fseek(_arch,direccion,SEEK_SET);

        fwrite(entidad,sizeof(Entidad),1,_arch);
        
        this->cierraArchivo();
        
    }
    else
        direccion=EOF;

    return direccion;
}

Atributo* Archivo::leeAtributo(DIR_t direccion){

    Atributo *atr=NULL;

    if(this->abreArchivo())
    {
        atr=new Atributo();
        fseek(_arch,direccion,SEEK_SET);

        fread(atr,sizeof(Atributo),1,_arch);

        this->cierraArchivo();
    }

    return atr;
}
DIR_t Archivo::escribeAtributo(Atributo* atributo, DIR_t direccion){

    if(this->abreArchivo())
    {
        if(direccion == EOF)
        {
            fseek(_arch,0,SEEK_END);
            direccion=ftell(_arch);
        }
        else
            fseek(_arch,direccion,SEEK_SET);

        fwrite(atributo,sizeof(Atributo),1,_arch);
        
        this->cierraArchivo();
        
    }
    else
        direccion=EOF;

    return direccion;
}

char* Archivo::leeBloque(int size, DIR_t direccion){
    
    char* buff=NULL;

    if(this->abreArchivo())
    {
        buff=new char[size];
        fseek(_arch,direccion,SEEK_SET);
        fread(buff,size,1,_arch);
        this->cierraArchivo();
    }

    return buff;
}
DIR_t Archivo::escribeBloque(char* buffer, int size,DIR_t direccion){
    
    if(this->abreArchivo())
    {
        if(direccion == EOF)
        {
            fseek(_arch,0,SEEK_END);
            direccion=ftell(_arch);
        }
        else
            fseek(_arch,direccion,SEEK_SET);

        fwrite(buffer,size,1,_arch);
        
        this->cierraArchivo();
        
    }
    else
        direccion=EOF;

    return direccion;
}

DIR_t Archivo::getDirFin(){
    int ret=EOF; 
    if(this->abreArchivo())
    {
        fseek(_arch,0L,SEEK_END);
        ret=ftell(_arch);
        this->cierraArchivo();
    }
    return ret;
}

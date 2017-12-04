/* 
 * File:   opciones.cpp
 * Author: Alfredo
 * 
 * Created on 30 de enero de 2014, 04:40 PM
 */

#include "opciones.h"


opciones::opciones(int numeroArgumentos, char** nombreArgumentos, int isConsole) {
   
    _isValid=0;
    int isaction=0,error=0,i,j;
    _numcomands=0;
    comando aux;
   
    
    for(int i=0;i<MAX_COMANDS;i++)
    {
        strcpy(_comands[i].opcion,"");
        strcpy(_comands[i].parametro,"");
        _comands[i].tipo=0;
    }
    
   _numcomands = this->fillOptions(numeroArgumentos,nombreArgumentos);
   if(_numcomands)
   {
       for(int i=0;i<_numcomands;i++){
           int type=isValid(_comands[i]);
           if(type)
           {
               if(type==ACCION_T && !isaction)
               {
                   _comands[i].tipo=type;

                   aux=_comands[i];
                   _comands[i]=_comands[0];
                   _comands[0]=aux;
                   isaction=1;
               }               
           }
           else
           {
               error=1;
               printf("ERROR: no se reconoce la opcion \"%s %s\".\n",_comands[i].opcion, !strcmp(_comands[i].parametro,"")?"<>":_comands[i].parametro);
           }
       }
   }
   
    
   if( !error ){
       if(!isaction && !isConsole)
           printf("No se hace nada para diccionario\n");
       else
           _isValid=1;
   }

      
}

opciones::opciones(const opciones& orig) {
}

opciones::~opciones() {
}

int opciones::isValid(comando comand){

        #define NUM_OPCIONES 5
    const char* _OPTIONS[NUM_OPCIONES]={
    (char*)"-d",        //opcion diccionario
    (char*)"-e",        //opcion entidad
    (char*)"-n",        //opcione nombre
    (char*)"-k",        //opcione llave
    (char*)"-t"        //opcion tipo
    };

    #define NUM_ACCIONES 12
   const char* _ACTIONS[NUM_ACCIONES]={
   (char*) "-new",      //accion nuevo
   (char*) "-ae",       //accion alta entidad
   (char*) "-be",       //accion baja entidad
   (char*) "-aa",       //accion alta atributo
   (char*) "-ba",       //accion baja atributo
   (char*) "-ma",       //accion modifica atributo
   (char*)"-ce",       //accion consulta entidad
   (char*)"-c",        //accion consulta
   (char*)"-me",       //accion modifica entidad
   (char*)"-h",        //opcione ayuda
   (char*)"-help",     //opcione ayuda
   (char*)"-q"          //salir del modo consola
   };
    int op=0;
    for(int i=0;i<NUM_OPCIONES;i++)
        if(!strcmp(comand.opcion,_OPTIONS[i]))
        {
            op=ATRIBUTO_T;
            break;
        }
    
    for(int i=0;i<NUM_ACCIONES;i++)
        if(!strcmp(comand.opcion,_ACTIONS[i]))
        {
            op=ACCION_T;
            break;
        }
    
    
    
    return op;
}
int opciones::isEjecutable(){
    return _isValid;
}
comando opciones::getComando(int index){

    return _comands[index];
}
int opciones::getNumComandos(){
    return _numcomands;
}
int opciones::fillOptions(int numArgs,char** nomArgs){

    int numcomands=0;
    if(numArgs>1)
    {
        for(int i=1;i<numArgs;i++)
        {
            strcpy(_comands[numcomands].opcion,nomArgs[i]);
            if( (i+1) < numArgs )
            {
                if(nomArgs[i+1][0]!='-')
                {
                    strcpy(_comands[numcomands].parametro,nomArgs[i+1]);
                    i++;
                }
            }

            numcomands++;
        }

    }
    return numcomands;
}


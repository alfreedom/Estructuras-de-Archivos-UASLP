/* 
 * File:   main.cpp
 * Author: alfredo
 *
 * Created on 8 de abril de 2014, 12:45 PM
 */




#include <ncurses.h>
#include "consola.h"
#include "registro.h"
#include "indexada.h"
#include "help.h"
#include <stdio.h>
#include <string.h>


#define DEFAULTDICNAME "dic.sec"
#define MAX_LEN_OP 50

typedef struct opciones_t{
    
    char alta[MAX_LEN_OP];
    char baja[MAX_LEN_OP];
    char modifica[MAX_LEN_OP];
    char consulta[MAX_LEN_OP];
    char dic[MAX_LEN_OP];
    char importa[MAX_LEN_OP];
    char outputdic[MAX_LEN_OP];
    char exit[MAX_LEN_OP];
    char key[MAX_LEN_OP];
    char help[MAX_LEN_OP];
}Opciones;

Opciones getOpciones(int argc, char** argv);
int ejecutaOpciones(Opciones ops, int isConsole);
void attachError(int error);

int main(int argc, char** argv) {

    _error_=0;
    if(argc>1){
        Opciones ops=getOpciones(argc,argv);
        Indexada *sec;
        
        if(strcmp(ops.help,"")){
            ShowHelp();
        }
        else
        if(strcmp(ops.importa,"")){
            
            if(Indexada::ImportaDiccionario(ops.importa,ops.outputdic)){
                printf("OK! diccionario importado correctamente '%s' -> '%s'",ops.importa,ops.outputdic);
            }
            
        }
        else
        if(strcmp(ops.dic,"")){
            sec=new Indexada(ops.dic);
            
            if(strcmp(ops.alta,""))
            {
                
                _error_=sec->AltaIndexada(ops.alta);
                if(!_error_){
                    sec->ConsultaIndexada(ops.alta); 
                    printw("\nOK! presione una tecla para continuar.");
                    getch();
                }
            }
            
            
            if(strcmp(ops.baja,"") && strcmp(ops.key,""))
            {                
                _error_=sec->BajaIndexada(ops.baja,ops.key);
                
                if(!_error_)
                {
                    sec->ConsultaIndexada(ops.baja);
                    printw("\nOK! presione una tecla para continuar.");
                    getch();
                }
            }
            
            
            if(strcmp(ops.consulta,""))
            {
                if(!strcmp(ops.consulta,"ALL"))
                    _error_=sec->ConsultaIndexada();
                else
                    _error_=sec->ConsultaIndexada(ops.consulta);
                
                if(!_error_){
                    printw("\nOK! presione una tecla para continuar.");
                    getch();
                }
            }
            
            if(strcmp(ops.modifica,"") && strcmp(ops.key,""))
            {
                _error_=sec->ModificaIndexada(ops.modifica,ops.key);
                if(!_error_){
                    sec->ConsultaIndexada(ops.modifica);        
                    printw("\nOK! presione una tecla para continuar.");
                    getch();
                }
               
            }
            
            delete sec;
        }
        else
            _error_=ERR_DICNOTSELECT;
        
        
      
       
    }
    attachError(_error_);
    
    //Indexada::ImportaDiccionario("fred.dic","fred.sec");
   /* 
    char* buff;
    void* dato=NULL;
    
    Archivo *dicSec = new Archivo((char*)"fred.sec");    
    DIR_t cab=dicSec->leeCab();    
    Entidad* ent=dicSec->leeEntidad(cab);    
    DIR_t cabatr=ent->getDirAtributos();
    Registro* b=new Registro(ent,dicSec);
    
  
    
    while(cabatr!=EOF){
        Atributo *atr=dicSec->leeAtributo(cabatr);
        dato=pideDato(atr);
        
        if(dato)               
           b->empaqueta(dato,atr);

               
  
            
        cabatr=atr->getSiguiente();
    }
    b->imprime();
     
     */
   
    
    
    //Consola *cons=new Consola();
    //cons->SetPrompt("@~:");
    //cons->Run();
    //sec->ImportaDiccionario("dic.d","dic.sec");
    
    return 0;
}
int ejecutaOpciones(Opciones ops, int isConsole){
    
}
Opciones getOpciones(int argc, char** argv){
     Opciones ops;
     bzero(ops.alta,MAX_LEN_OP);
     bzero(ops.baja,MAX_LEN_OP);
     bzero(ops.consulta,MAX_LEN_OP);
     bzero(ops.modifica,MAX_LEN_OP);
     bzero(ops.dic,MAX_LEN_OP);
     bzero(ops.exit,MAX_LEN_OP);
     bzero(ops.importa,MAX_LEN_OP);
     bzero(ops.outputdic,MAX_LEN_OP);
     bzero(ops.key,MAX_LEN_OP);
     bzero(ops.help,MAX_LEN_OP);
    while(*(++argv)){
        
        //alta Indexada
        if(!strcmp("-A",*argv) || !strcmp("-a",*argv)){
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.alta,*(argv+1));
                *(argv++);
            }
            else{
                _error_=ERR_PARAMEMPTY;
                
            }               
        }
        else//baja Indexada            
        if(!strcmp("-B",*argv) || !strcmp("-b",*argv)){
            
            if(*argv+1 && *(argv+1)[0]!='-'){
                strcpy(ops.baja,*(argv+1));
                *(argv++);
            }
            else{
                _error_=ERR_PARAMEMPTY;
            }               
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.key,*(argv+1));
                *(argv++);
            }
            else
                _error_=ERR_KEYEMPTY;
        }
        else//modifica Indexada            
        if(!strcmp("-M",*argv) || !strcmp("-m",*argv)){
            
           
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.modifica,*(argv+1));
               *(argv++);
            }
            else{
                _error_=ERR_PARAMEMPTY;
            }               
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.key,*(argv+1));
                *(argv++);
            }
            else
                _error_=ERR_KEYEMPTY;
        }
        else//consulta Indexada            
        if(!strcmp("-C",*argv) || !strcmp("-c",*argv)){
            
            if(*(argv+1) && *(argv+1)[0]!='-')
            {
                strcpy(ops.consulta,*(argv+1));
                *(argv++); 
            }
            else
                strcpy(ops.consulta,"ALL");
            
                   
        }
        else//consulta Indexada            
        if(!strcmp("-I",*argv) || !strcmp("-i",*argv)){
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.importa,*(argv+1));
                *(argv++);
            }
            else{
                _error_=ERR_PARAMEMPTY;
            }    
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.outputdic,*(argv+1));
                *(argv++);
            }
            else
                strcpy(ops.outputdic,DEFAULTDICNAME);
        }
        else//selecciona diccionario Indexada            
        if(!strcmp("-D",*argv) || !strcmp("-d",*argv)){
            
            if(*(argv+1) && *(argv+1)[0]!='-'){
                strcpy(ops.dic,*(argv+1));
                *(argv++);
            }
            else{
                _error_=ERR_PARAMEMPTY;
            }    
            
        }
        else//selecciona diccionario Indexada            
        if(!strcmp("-q",*argv) || !strcmp("-Q",*argv) || !strcmp("exit",*argv) || !strcmp("EXIT",*argv)){
            
               strcpy(ops.exit,"TRUE");
                *(argv++);            
            
        }
        else//selecciona diccionario Indexada            
        if(!strcmp("-h",*argv) || !strcmp("-H",*argv) || !strcmp("-help",*argv) || !strcmp("help",*argv) || !strcmp("?",*argv)){
            
               strcpy(ops.help,"TRUE");
                *(argv++);            
            
        }
        
    }
    
    return ops;
}
void attachError(int error){
    if(error & ERR_DECIMALERROR)
        printf("\nError: El valo ingresado no es un decimal valido.");
    else
     if(error & ERR_NUMERROR)
        printf("\nError: El valo ingresado no es un numero valido.");
     else
    if( error & ERR_DICNOTFOUND)
        printf("\nError: No se encuentra el diccionario seleccionado.");
    else
    if( error & ERR_ENTNOTFOUND )
        printf("\nError: no se encuentra la entidad seleccionada");
    else
    if( error & ERR_KEYNOTFOUND )
        printf("\nError: La entidad no tiene un atributo con llave primaria");
    else
    if( error & ERR_INPUTEMPTY)
        printf("\nError: La entrada de datos esta vacia");
    else
    if( error & ERR_REGNOTFOUND)
        printf("\nError: No se encuentra el registro especificado.");
    else
    if( error & ERR_REGEXIST)
        printf("\nError: Ya existe un registro con la llave especificada.");
    else
    if( error & ERR_DICNOTSELECT)
        printf("\nError: No se ha seleccionado un diccionario.");
    else
    if( error & ERR_PARAMEMPTY)
        printf("\nError: se ha dejado un campo vacio.");
    else
    if( error & ERR_NOTATR)
        printf("\nError: La tabla no tiene atributos.");
    else
        printf("\nOK");
    
    printf("\n");
}
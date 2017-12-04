/* 
 * File:   main.cpp
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 *
 * Created on 28 de enero de 2014, 04:32 PM
 *
 * Descripción:
 */


#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "entidad.h"
#include "opciones.h"
#include "help.h"
#include "atributo.h"
/*
 * 
 */

char nombre_dic_consola[100]="";

void ejecutaComando(comando com);
void consola();
int getArgs(char* string,char** args);

opciones *ops;
             
int main(int argc, char** argv) {

    printf("\n######################### Diccionario de Datos ###########################\n\n");
    ops=new opciones(argc,argv,0);
    comando com;
    int numComandos;

    if(argc==1)
    {
        consola();
    }
    else
    {

        if(ops->isEjecutable()){

            numComandos=ops->getNumComandos();
            for(int i=0;i<numComandos;i++)
            {
                com=ops->getComando(i);
                ejecutaComando(com);
            }
        }
    }
     printf("\n##########################################################################\n\n");
}

void consola(){

    char prompt[10]="@>: ";
    int exit=false;
    int nArgs;
    int numComandos=0;
    comando com;
    char** args;
    args=(char**)malloc(sizeof(char*) * 10);
    for(int i=0;i<10;i++){
        args[i]=(char*)malloc(sizeof(char)*100);
        strcpy(args[i],"");
    }
    char input[100]="";
    opciones *op;

    while(!exit){

        printf("%s",prompt);
        strcpy(input,"");
        gets(input);
        nArgs=getArgs(input,args);
        args[0];
        args[1];
        op=new opciones(nArgs,args,1);
        if(op->isEjecutable())
        {           

            numComandos=op->getNumComandos();
            for(int i=0;i<numComandos;i++)
            {
                com=op->getComando(i);
                if(!strcmp(com.opcion,"-q"))
                {
                    exit=true;
                    break;
                }
                else if(!strcmp(com.opcion,"-d")){
                    strcpy(nombre_dic_consola,com.parametro);
                    printf("Nombre del diccionario seleccionado: %s.\n",com.parametro);
                }
                else if(!strcmp(com.opcion,"-ae")){

                    if(!strcmp(com.parametro,""))
                        printf("ERROR: Alta Entidad -> No se especifico el nombre de la entidad.\n");
                    else
                    {
                         if(!strcmp(nombre_dic_consola,""))
                             printf("No se ha seleccionado un diccionario.\n");                         
                         else
                         {
                            Diccionario *dic=new Diccionario(nombre_dic_consola);
                            if(dic->altaEntidad(com.parametro))
                            {
                                printf("¡LISTO!: Se dio de alta la entidad \"%s\"  en el diccionario \"%s\".\n",com.parametro,nombre_dic_consola);
                                dic->consultaEntidades();
                            }
                            else
                                printf("ERROR: Alta Entidad -> No se pudo dar de alta la entidad \"%s\".\n",com.parametro);
                            
                            delete dic;
                        }
                    }
                }
                else if(!strcmp(com.opcion,"-be")){

                    if(!strcmp(com.parametro,""))
                        printf("ERROR: Baja Entidad -> No se especifico el nombre de la entidad.\n");
                    else
                    {
                         if(!strcmp(nombre_dic_consola,""))
                             printf("No se ha seleccionado un diccionario.\n");
                         else{
                            Diccionario *dic=new Diccionario(nombre_dic_consola);
                            if(dic->bajaEntidad(com.parametro))
                            {
                                printf("¡LISTO!: Se dio de baja la entidad \"%s\"  en el diccionario \"%s\".\n",com.parametro,nombre_dic_consola);
                                dic->consultaEntidades();
                            }
                            else
                                printf("ERROR: Baja Entidad -> No se pudo dar de baja la entidad \"%s\".\n",com.parametro);
                            
                            delete dic;
                        }
                    }
                }
                else if(!strcmp(com.opcion,"-me")){


                    if(!strcmp(com.parametro,""))
                        printf("ERROR: Modifica Entidad -> No se especifico el nombre de la entidad.\n");
                    else
                    {
                         if(!strcmp(nombre_dic_consola,""))
                             printf("No se ha seleccionado un diccionario.\n");
                         else{
                             comando cc;
                             int stats=0;
                             for(int i=0;i<numComandos;i++)
                             {
                                cc=op->getComando(i);
                                if(!strcmp(cc.opcion,"-n"))
                                {
                                    stats=1;
                                    if(!strcmp(cc.parametro,""))
                                        printf("ERROR: Modifica Entidad -> No se especifico el nombre nuevo de la entidad \"%s\".\n",com.parametro);
                                    else
                                    {
                                        Diccionario *dic=new Diccionario(nombre_dic_consola);
                                        if(dic->modificaEntidad(com.parametro,cc.parametro))
                                        {
                                            printf("¡LISTO!: Se modifico la entidad \"%s\" -> \"%s\"  en el diccionario \"%s\".\n",com.parametro,cc.parametro,nombre_dic_consola);
                                            dic->consultaEntidades();
                                        }
                                        else
                                            printf("ERROR: Modifica Entidad -> No se pudo dar de baja la entidad \"%s\".\n",com.parametro);

                                        delete dic;

                                        break;
                                    }
                                    
                                }
                             }
                             if(!stats)
                                 printf("ERROR: Modifica Entidad -> No se especifico el nombre nuevo de la entidad \"%s\".\n",com.parametro);
                        }
                    }
                }
                else if(!strcmp(com.opcion,"-c")){

                     if(!strcmp(nombre_dic_consola,""))
                         printf("No se ha seleccionado un diccionario.\n");
                     else
                     {
                        Diccionario *dic=new Diccionario(nombre_dic_consola);
                        dic->consultaEntidades();
                        delete dic;
                     }

                }
                else if(!strcmp(com.opcion,"-new")){

                     if(!strcmp(com.parametro,""))
                         printf("ERROR: Crea Diccionario ->No se especifico un nombre de archivo\n");
                    else
                    {
                        Diccionario *dic=new Diccionario(com.parametro);
                        if(dic->creaDiccionario())
                            printf("¡LISTO!: Diccionario %s creado correctamente.\n",dic->getNombre());
                        
                        else
                            printf("ERROR: Crea Diccionario -> No se pudo crear el diccionario %s.\n\n",dic->getNombre());
                        
                        delete dic;
                    }

                }
                else if(!strcmp(com.opcion,"-h") || !strcmp(com.opcion,"-help")){
                    ShowHelp();
                }
            }
            
        }
    }
}

int getArgs(char* string, char** args){

    char a[100]="";
    int i=0;
    int nargs=1;
    int idex=1;
    int idey=0;
    int isSpace=0;

    do
    {
        if(string[i]==' ' && !isSpace)
        {
            isSpace=1;
        }
        else{

            if(isSpace)
            {

                strcpy(args[idex++],a);
                for(int i=0;i<100;a[i++]='\0');
                isSpace=0;
                nargs++;
                idey=0;
            }
            a[idey++] = string[i];
        }

    }while(string[i++]);

    strcpy(args[idex++],a);
        return nargs+1;
}

void ejecutaComando(comando com)
{
    if(!strcmp(com.opcion,"-new"))
    {
        if(!strcmp(com.parametro,"")){
            printf("ERROR: Crea Diccionario ->No se especifico un nombre de archivo\n");
        }
        else{
            Diccionario *dic=new Diccionario(com.parametro);
            if(dic->creaDiccionario())
                printf("¡LISTO!: Diccionario %s creado correctamente.\n",dic->getNombre());
            else
                printf("ERROR: Crea Diccionario -> No se pudo crear el diccionario %s.\n\n",dic->getNombre());
            delete dic;
        }
    }
    else if(!strcmp(com.opcion,"-ae"))
    {
        if(!strcmp(com.parametro,"")){
            printf("ERROR: Alta Entidad -> No se especifico el nombre de la entidad.\n");
        }
        else{
        comando c;
        int numComandos=ops->getNumComandos();
        for(int i=0;i<numComandos;i++)
        {
            c=ops->getComando(i);
            if(!strcmp(c.opcion,"-d"))
            {
                if(!strcmp(c.parametro,"")){
                     printf("ERROR: Alta Entidad -> No se especifico el nombre del diccionario.\n");
                }
                else
                {
                    Diccionario *dic=new Diccionario(c.parametro);
                    if(dic->altaEntidad(com.parametro))
                    {
                        printf("¡LISTO!: Se dio de alta la entidad \"%s\"  en el diccionario \"%s\".\n",com.parametro,c.parametro);
                        dic->consultaEntidades();
                    }
                    else
                        printf("ERROR: Alta Entidad -> No se pudo dar de alta la entidad \"%s\".\n",com.parametro);
                    delete dic;
                    return;
                }
            }
        }
        printf("ERROR: Alta Entidad -> No se especifico el diccionario.");
       }
    }
    else if(!strcmp(com.opcion,"-me"))
    {
        if(!strcmp(com.parametro,"")){
            printf("ERROR: Modifica Entidad -> No se especifico el nombre de la entidad.\n");
        }
        else{
            comando c;
            int numComandos=ops->getNumComandos();
            char dic_name[TAM_NOMBRE]="";
            char new_name[TAM_NOMBRE]="";
            for(int i=0;i<numComandos;i++)
            {
                c=ops->getComando(i);
                if(!strcmp(c.opcion,"-d") && !strcmp(dic_name,""))
                     if(!strcmp(c.parametro,""))
                        return;
                     else
                         strcpy(dic_name,c.parametro);

                if(!strcmp(c.opcion,"-n") && !strcmp(new_name,""))
                     if(!strcmp(c.parametro,""))
                        return;
                     else
                         strcpy(new_name,c.parametro);

            }

            if(strcmp(dic_name,""))
            {
                if(strcmp(new_name,"")){
                        Diccionario *dic=new Diccionario(dic_name);
                        if(dic->modificaEntidad(com.parametro,new_name))
                        {
                            printf("¡LISTO!: Se modifico la entidad \"%s\" -> \"%s\"  en el diccionario \"%s\".\n",com.parametro,new_name,dic_name);
                            dic->consultaEntidades();
                        }
                        else
                            printf("ERROR: Modifica Entidad -> No se pudo dar de alta la entidad \"%s\".\n",com.parametro);
                        delete dic;
                        return;
                }
                else
                    printf("ERROR: Modifica Entidad -> No se especifico el nuevo nombre para la entidad.\n");
            }
            else
                printf("ERROR: Modifica Entidad -> No se especifico nombre del diccionario.\n");
       }
    }
    else if(!strcmp(com.opcion,"-c"))
    {
         if(!strcmp(com.parametro,"")){
            printf("ERROR: Consulta -> No se especifico el nombre del diccionario.\n");
         }
         else
         {
            Diccionario *dic=new Diccionario(com.parametro);
            dic->consultaEntidades();
            delete dic;
         }
    }
    else if(!strcmp(com.opcion,"-be"))
    {
        if(!strcmp(com.parametro,"")){
            printf("ERROR: Baja Entidad -> No se especifico el nombre de la entidad.\n");
        }
        else{
            comando c;
            int numComandos=ops->getNumComandos();
            for(int i=0;i<numComandos;i++)
            {
                c=ops->getComando(i);
                if(!strcmp(c.opcion,"-d"))
                {
                    if(!strcmp(c.parametro,"")){
                         printf("ERROR: Baja Entidad -> No se especifico el nombre del diccionario.\n");
                    }
                    else
                    {
                    Diccionario *dic=new Diccionario(c.parametro);
                    if(dic->bajaEntidad(com.parametro))
                    {
                        printf("¡LISTO!: Se dio de baja la entidad \"%s\" en el diccionario \"%s\".\n",com.parametro,c.parametro);
                        dic->consultaEntidades();
                    }
                    else
                        printf("ERROR: Baja Entidad -> No se pudo dar de baja la entidad \"%s\".\n",com.parametro);
                    
                    delete dic;
                    return;
                    }
                }
            }
            printf("ERROR: Alta Entidad -> No se especifico el diccionario.");
       }

    }
    else if(!strcmp(com.opcion,"-h") || !strcmp(com.opcion,"-help"))
    {

        ShowHelp();

    }
}


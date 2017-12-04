/* 
 * File:   help.h
 * Author: Alfredo
 *
 * Created on 4 de febrero de 2014, 02:02 PM
 */

#ifndef HELP_H
#define	HELP_H

#include <stdio.h>
#define MAX_LINE 80

char line[MAX_LINE];
void GenerateHelp()
{
    FILE *f=fopen("HELP","w");

    if(f)
    {
        fprintf(f,"********************* AYUDA DEL DICCIONARIO DE DATOS *********************\n\n");
        fprintf(f,"NOMBRE:\n");
        fprintf(f,"    dic.exe (windows) dic (linux)   Diccionario de Datos\n\n");
        fprintf(f,"SINTAXYS:\n");
        fprintf(f,"    dic.exe/dic <opncion1> parametro <opcion2> parametro ...\n\n");
        fprintf(f,"DESCRIPCION:\n");
        fprintf(f,"    Crea y  manipula  archivos que  guardaran  un diccionario\n");
        fprintf(f,"    de datos, agregando, eliminando, modificando y consultado\n");
        fprintf(f,"    entidades y atributos.\n\n");
        fprintf(f,"    -ae\n");
        fprintf(f,"        (Alta Entidad) <[nombre_de_la_entidad>\n");
        fprintf(f,"            Da de alta una entidad en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la entidad.\n\n");
        fprintf(f,"    -be\n");
        fprintf(f,"        (Baja Entidad) <nombre_de_la_entidad>\n");
        fprintf(f,"            Da de baja una entidad en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la entidad.\n\n");
        fprintf(f,"    -me  [-n]\n");
        fprintf(f,"        (Modifica Entidad) <nombre_de_la_entidad> [-n]\n");
        fprintf(f,"            Renombra una entidad en el diccionario especificado por -d.\n");
        fprintf(f,"            y el nombre especificado por -n.\n");
        fprintf(f,"            El parametro es el nombre de la entidad.\n\n");
        fprintf(f,"    -c\n");
        fprintf(f,"        (Consulta) <nombre_del_diccionario>\n");
        fprintf(f,"            Hace  una  consulta  en  el  diccionario  y muestra todos las\n");
        fprintf(f,"            entidades con sus atributos.\n");
        fprintf(f,"            El parametro es el nombre del diccionario.\n\n");
        fprintf(f,"    -ce\n");
        fprintf(f,"        (Consulta Entidad) <nombre_de_la_entidad>\n");
        fprintf(f,"            Hace una consulta de la entidad en el diccionario especificado\n");
        fprintf(f,"            por -d y muestra todos sus atributos.\n");
        fprintf(f,"            El parametro es el nombre de la entidad.\n\n");
        fprintf(f,"    -d\n");
        fprintf(f,"        (Archivo del diccionarcio) <nombre_del_diccionario>\n");
        fprintf(f,"            Especifica el diccionario a abrir.\n");
        fprintf(f,"            El parametro es el nombre del diccionario.\n");
        fprintf(f,"    -new\n");
        fprintf(f,"        (Nuevo Diccionario) <nombre_del_diccionario>\n");
        fprintf(f,"            Crea un nuevo archivo de diccionario.\n");
        fprintf(f,"            El parametro es el nombre del diccionario.\n\n");
        fprintf(f,"    -h, -help\n");
        fprintf(f,"        (Ayuda)\n");
        fprintf(f,"            Muestra este menu de ayuda.\n\n\n");
        fprintf(f,"PROGRAMADO POR:\n\n");
        fprintf(f,"    Alfredo Orozco de la Paz.\n");
        fprintf(f,"    Universidad Autonoma de San Luis Potosi UASLP.\n");
        fprintf(f,"    Area de Computacion e Informatica.\n");
        fprintf(f,"    Materia: Estructuras de Archivos.\n");
        fprintf(f,"    Profesor: Omar Adalid.\n");
        fprintf(f,"    Semestre 2013/2014-II.\n");
        fclose(f);
    }


}
void ShowHelp()
{
    FILE *f=fopen("HELP","rb");

    if(f)
    {
        while(fgets(line,MAX_LINE,f))
        printf("%s",line);
        fclose(f);
        
    }
    else
    {
        GenerateHelp();
        ShowHelp();
    }
       
}

#endif	/* HELP_H */


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
    FILE *f=fopen("HELPMULTILISTA","w");

    if(f)
    {
        fprintf(f,"**************** AYUDA DE LA ORGANIZACIÖN MULTILISTA *****************\n\n");
        fprintf(f,"NOMBRE:\n");
        fprintf(f,"    multilista (linux)   Organización Secuencial Indexada\n\n");
        fprintf(f,"SINTAXYS:\n");
        fprintf(f,"    multilista <opncion1> parametro <opcion2> parametro ...\n\n");
        fprintf(f,"DESCRIPCION:\n");
        fprintf(f,"    Crea y  manipula  registros de un diccionario con listas multiples ordenadas\n");
        fprintf(f,"    agregando, eliminando, modificando y consultado registros\n\n");
        
        fprintf(f,"    -a/-A\n");
        fprintf(f,"        (Alta) <nombre_de_la_tabla>\n");
        fprintf(f,"            Da de alta un nuevo registro en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la tabla.\n\n");
        
        fprintf(f,"    -b/-B\n");
        fprintf(f,"        (Baja) <nombre_de_la_tabla>\n");
        fprintf(f,"            Da de baja una entidad en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la entidad.\n\n");
        
        fprintf(f,"    -c/-C\n");
        fprintf(f,"        (Consulta) <nombre_de_la_tabla> <nombre_del_atributo>\n");
        fprintf(f,"            Hace  una  consulta  en  el  diccionario  y muestra todos los\n");
        fprintf(f,"            registros de la tabla en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la tabla y el atributo de referencia.\n\n");
        
        fprintf(f,"    -d\n");
        fprintf(f,"        (Archivo del diccionarcio) <nombre_del_diccionario>\n");
        fprintf(f,"            Especifica el diccionario a usar.\n");
        fprintf(f,"            El parametro es el nombre del diccionario.\n\n");
        
        fprintf(f,"    -h/-H/-help/help/?\n");
        fprintf(f,"        (Ayuda)\n");
        fprintf(f,"            Muestra este menu de ayuda.\n\n");
        
        fprintf(f,"    -i/-I\n");
        fprintf(f,"        (Importa Diccionario) <diccionario_fuente> <diccionario_destino>\n");
        fprintf(f,"            Importa un diccionario de datos a uno de tipo secuencial.\n");
        fprintf(f,"            El parametro es el nombre del diccionario a importar.\n");
        fprintf(f,"            El nombre del diccionario destino es opcional.\n\n");
       
        fprintf(f,"    -m/-M\n");
        fprintf(f,"        (Modifica) <nombre_de_la_tabla> <nombre_del_atributo> <key>\n");
        fprintf(f,"            Modifica un registro de una tabla con la clave especificado por <key>\n");
        fprintf(f,"            en el diccionario especificado por -d.\n");
        fprintf(f,"            El parametro es el nombre de la entidad, el nombre del atributo referencia\n");
        fprintf(f,"            y el valor del atributo.\n\n\n");
         
        fprintf(f,"MODO DE USO:\n");
        fprintf(f,"    ALTA:     -d dic.mul -a TABLA\n");
        fprintf(f,"    BAJA:     -d dic.mul -b TABLA ATRIBUTO CLAVE\n");
        fprintf(f,"    CONSULTA: -d dic.mul -c (muestra todos los atributos de la entidad)\n");
        fprintf(f,"    CONSULTA: -d dic.mul -c TABLA (muestra los registros en base al primer atributo)\n");
        fprintf(f,"    CONSULTA: -d dic.mul -c TABLA ATRIBUTO (muestra los registros en base a Atributo)\n");
        fprintf(f,"    MODIFICA: -d dic.mul -m TABLA ATRIBUTO CLAVE\n\n");
        fprintf(f,"PROGRAMADO POR:\n\n");
        fprintf(f,"    Alfredo Orozco de la Paz.\n");
        fprintf(f,"    Universidad Autonoma de San Luis Potosi UASLP.\n");
        fprintf(f,"    Area de Computacion e Informatica.\n");
        fprintf(f,"    Materia: Estructuras de Archivos.\n");
        fprintf(f,"    Profesor: Omar Adalid.\n");
        fprintf(f,"    Semestre 2013/2014-II.\n\n\r");
        fclose(f);
    }


}
void ShowHelp()
{
    FILE *f=fopen("HELPMULTILISTA","rb");

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


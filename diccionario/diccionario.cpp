/* 
 * File:   diccionario.cpp
 * Author: Alfredo Orozco de la Paz
 * Maetia: Estructuras de Archivos
 * 
 * Created on 28 de enero de 2014, 04:57 PM
 *
 * Descripción:
 *
 * Implementación de los métodos de la clase diccionario.
 * ver diccionario.h para mas información.
 */

#include "diccionario.h"


/******  Constructores y destructores ******/
Diccionario::Diccionario(){
     strcpy(_nombre,"diccionario");
     _arch =  new Archivo(_nombre);
     
}
Diccionario::Diccionario(char* nombre) {
     strcpy(_nombre,nombre);
     _arch =  new Archivo(_nombre);
}
Diccionario::Diccionario(Diccionario& orig) {

}
Diccionario::~Diccionario() {
    delete _arch;
}
/**********************************************/


/*************  Metodos publicos **************/
char* Diccionario::getNombre(){
    return _nombre;
}
int Diccionario::creaDiccionario(){
    return this->creaDiccionario(_nombre);
}
int Diccionario::creaDiccionario(char* nombre){
    
    int ret=0;
    
    if(_arch->creaArchivo() && _arch->escribeCab(EOF))
        ret=1;
            
    
    return ret;
}
int Diccionario::altaEntidad(char* nombre){
    
    Entidad* ent= new Entidad(nombre);
    int ret=1;
    if(!buscaEntidad(ent))
    {
        DIR_t pos = _arch->escribeEntidad(ent,EOF);
        if(pos==EOF)
        {
            printf("ERROR: Escribir Entidad -> No se pudo abrir el archivo \"%s\".\n\n", _nombre);
            ret= 0;
        }
        else
        if(!this->insertaEntidad(ent,pos))
        {
            printf("ERROR: Insertar Enidad -> No se pudo insertar la entidad \"%s\", ya existe una entidad con ese nombre.\n\n", nombre);
            ret=0;
        }
    }
    else
    {
        printf("ERROR: Alta Entidad -> ya existe una entidad con el nombre \"%s\".\n\n", nombre);
        ret=0;
    }
        

    return ret;
}
int Diccionario::bajaEntidad(char* nombre){

    
    int ret=0;
    if(buscaEntidad(nombre))
    {
        DIR_t pos = this->eliminaEntidad(nombre);
        if(pos==EOF)
            printf("ERROR: No se pudo eliminar la entidad \"%s\" en el diccionario \"%s\".\n",nombre,_nombre);
        else
            ret=1;
    }
    else
       printf("ERROR: No existe la entidad \"%s\" en el diccionario \"%s\".\n",nombre,_nombre);


    return ret;
}
int Diccionario::modificaEntidad(char* nombre, char* nombre_nuevo){


    int ret=1;
    if(buscaEntidad(nombre))
    {
        if(!buscaEntidad(nombre_nuevo))
        {
            DIR_t pos=eliminaEntidad(nombre);
            Entidad* ent=_arch->leeEntidad(pos);
            ent->setNombre(nombre_nuevo);
            pos = _arch->escribeEntidad(ent,pos);
            if(pos==EOF)
            {
                printf("ERROR: Escribir Entidad -> No se pudo abrir el archivo \"%s\".\n\n", _nombre);
                ret= 0;
            }
            else
            if(!this->insertaEntidad(ent,pos))
            {
                printf("ERROR: Insertar Enidad -> No se pudo insertar la entidad \"%s\", ya existe una entidad con ese nombre.\n\n", nombre);
                ret=0;
            }
        }
        else
        {
            printf("ERROR: Ya existe la entidad \"%s\" en el diccionario \"%s\".\n",nombre,_nombre);
            ret=0;
        }
    }
    else
    {
        printf("ERROR: No existe la entidad \"%s\" en el diccionario \"%s\".\n",nombre,_nombre);
        ret=0;
    }
    return ret;
}
void Diccionario::consultaEntidad(char* nombre){
    
    DIR_t cab= _arch->leeCab();
    int i=1;

    if(!cab)
        printf("ERROR: No existe el archivo \"%s\".\n",_nombre);
    else{
        while(cab!=EOF){
            Entidad* ent=_arch->leeEntidad(cab);
            printf("   %d:\t%s.\n",i++,ent->getNombre());
            if(!strcpy(ent->getNombre(),nombre)){

                   //AQUI MOSTRAR LOS ATRIBUTOS DE LA ENTIDAD
                return;
            }
            cab=ent->getSiguiente();
        }
        printf("ERROR: Consulta Entidad -> No existe la entidad %s.\n\n",nombre);
    }
}
void Diccionario::consultaEntidades(){

    DIR_t cab= _arch->leeCab();
    int i=1;
    if(!cab)
        printf("ERROR: No existe el archivo \"%s\".\n",_nombre);
    else{
        printf("\n*** Lista de Entidades en el archivo \"%s\":\n\n",_nombre);
        printf("\n   #  \tNombre\n\n");
        while(cab!=EOF){
            Entidad* ent=_arch->leeEntidad(cab);
            printf("   %d-\t%s\n",i++,ent->getNombre());
            cab=ent->getSiguiente();
        }
        printf("\n******************************************\n\n");
    }
}

int Diccionario::altaAtributo(Atributo atributo, Entidad entidad){

}
int Diccionario::bajaAtributo(Atributo atributo, Entidad entidad){

}
int Diccionario::modificaAtributo(Atributo atributo, Atributo nuevo, Entidad entidad){

}
void Diccionario::consultaAtributos(char* nombreEntidad){

	Entidad* ent=buscaEnt(nombreEntidad);
	char nomTipos[5][30] = {"Entero","Cadena","Flotante","Double","Caracter"};
	int i=1;
	if(ent){
		
            DIR_t cabAtr=ent->getDirAtributos();

            Atributo* atr;

            printf("\n*** Lista de Atributos en la entidad \"%s\":\n\n",nombreEntidad);
            printf("\n   #  \tNombre\t \tTipo\t \tTamanio\t \n\n");

            while(cabAtr!=EOF){
                atr=_arch->leeAtributo(cabAtr);
                printf("   %3d-\t%s",i++,ent->getNombre());
                printf("\t-\t%s",nomTipos[atr->getTipo()]);
                printf("\t-\t%d\n",atr->getSize());
                cabAtr=atr->getSiguiente();
            }
	}
	else
		printf("ERROR: Consulta Atributo -> No existe la entidad %s.\n\n",nombreEntidad);
}
/**********************************************/

/**************  Metodos privados *************/
int Diccionario::insertaEntidad(Entidad *entidad, DIR_t direccion){

    int ret=0;
    
    DIR_t pos_anterior,cab= _arch->leeCab();
    if(!cab)
        printf("ERROR: No existe el archivo \"%s\".\n",_nombre);
    else{
        Entidad  *ent_anterior,*ent;
        if(cab == EOF || strcmp( entidad->getNombre(),_arch->leeEntidad(cab)->getNombre() ) < 0 )
        {
            entidad->setSiguiente(cab);
            _arch->escribeCab(direccion);
            ret=1;
        }
        else{
            ent_anterior=_arch->leeEntidad(cab);
            ent=_arch->leeEntidad(cab);
            pos_anterior=cab;
            cab=ent->getSiguiente();
            ent=_arch->leeEntidad(cab);
            while(cab!=EOF && strcmp( entidad->getNombre(),ent->getNombre() ) > 0 )
            {
                ent_anterior=ent;
                pos_anterior=cab;
                cab=ent->getSiguiente();
                if(cab!=EOF)
                ent=_arch->leeEntidad(cab);
            }
            entidad->setSiguiente(ent_anterior->getSiguiente());
            ent_anterior->setSiguiente(direccion);
            if(_arch->escribeEntidad(ent_anterior,pos_anterior) !=EOF)
                ret=1;
        }
    }
       return (ret && _arch->escribeEntidad(entidad,direccion) !=EOF);

}
DIR_t Diccionario::eliminaEntidad(char* nombre){

    DIR_t cab = _arch->leeCab();
    DIR_t posAnt= cab;

    if(!cab)
        printf("ERROR: No existe el archivo \"%s\".\n",_nombre);
    else{
        Entidad *ent = _arch->leeEntidad(cab);

        if(!strcmp(nombre,ent->getNombre()))
        {
            _arch->escribeCab(ent->getSiguiente());
            return cab;
        }
        else{
            cab=ent->getSiguiente();
            Entidad *entAnteriro = ent;

            while( cab != EOF)
            {
                ent=_arch->leeEntidad(cab);
                if(!strcmp(nombre,ent->getNombre())){
                    cab=entAnteriro->getSiguiente();
                    entAnteriro->setSiguiente(ent->getSiguiente());
                    _arch->escribeEntidad(entAnteriro,posAnt);
                    return cab;
                }
                posAnt=cab;
                entAnteriro=ent;
                cab=ent->getSiguiente();
            }
        }
    }
    return -1;

}
Entidad* Diccionario::buscaEnt(char* nombre){

	DIR_t  cab= _arch->leeCab();
	
    if(!cab)
        printf("ERROR: No existe el archivo \"%s\".\n",_nombre);
    else
    {   
    	Entidad* ent;     
        while(cab!=EOF){
            ent=_arch->leeEntidad(cab);
            if(!strcmp(nombre,ent->getNombre()))
                return ent;

            cab=ent->getSiguiente();
        }
    }
    return NULL;
}
int Diccionario::buscaEntidad(char* nombre){

	return (this->buscaEnt(nombre) != NULL);
        
}
int Diccionario::buscaEntidad(Entidad* entidad){

    return this->buscaEntidad(entidad->getNombre());
}
/**********************************************/


/**********************************************/
int Diccionario::insertaAtributo(Entidad *entidad,DIR_t dir_entidad, Atributo* atributo, DIR_t dir_atributo){

    DIR_t cabAtr=entidad->getDirAtributos();
    int ret=0;
    //si la cabecera de atributos está vacia o si el primer atributo es mayor que el nuevo
    if(cabAtr == -1 || strcmp(atributo->getNombre(), _arch->leeAtributo(cabAtr)->getNombre()) < 0){

        atributo->setSiguiente(cabAtr);
        entidad->setDirAtributos(dir_atributo);
        _arch->escribeEntidad(entidad,dir_entidad);
        ret=1;
    }
    else{

        Atributo* atr_anterior=_arch->leeAtributo(cabAtr);
        Atributo *atr=_arch->leeAtributo(cabAtr);
        DIR_t pos_anterior=cabAtr;

        cabAtr=atr->getSiguiente();
        atr=_arch->leeAtributo(cabAtr);
        while(cabAtr!=EOF && strcmp( atributo->getNombre(),atr->getNombre() ) > 0 )
        {
            atr_anterior=atr;
            pos_anterior=cabAtr;
            cabAtr=atr->getSiguiente();
            if(cabAtr!=EOF)
                atr=_arch->leeAtributo(cabAtr);
        }
        atributo->setSiguiente(atr_anterior->getSiguiente());
        atr_anterior->setSiguiente(dir_atributo);
        if(_arch->escribeAtributo(atr_anterior,pos_anterior) !=EOF)
            ret=1;

    }

    return (ret && _arch->escribeAtributo(atributo,dir_atributo) !=EOF);
}
DIR_t Diccionario::eliminaAtributo(Entidad *entidad,DIR_t dir_entidad, char* nombre_atributo){

    DIR_t cabAtr = entidad->getDirAtributos();
    DIR_t posAnt= cabAtr;

    Atributo *atr = _arch->leeAtributo(cabAtr);

    if(!strcmp(nombre_atributo,atr->getNombre()))
    {
        entidad->setDirAtributos(atr->getSiguiente());
        _arch->escribeEntidad(entidad,dir_entidad);
        return cabAtr;
    }
    else{
        cabAtr=atr->getSiguiente();
        Atributo *atrAnteriro = atr;

        while( cabAtr != EOF)
        {
            atr=_arch->leeAtributo(cabAtr);
            if(!strcmp(nombre_atributo,atr->getNombre())){
                cabAtr=atrAnteriro->getSiguiente();
                atrAnteriro->setSiguiente(atr->getSiguiente());
                _arch->escribeAtributo(atrAnteriro,posAnt);
                return cabAtr;
            }
            posAnt=cabAtr;
            atrAnteriro=atr;
            cabAtr=atr->getSiguiente();
        }
    }

    return -1;
}
Atributo* Diccionario::buscaAtr(char* nombre_entidad,char* nombre_atributo){

    Entidad* ent=buscaEnt(nombre_entidad);

    if(ent){
        DIR_t cabAtr=ent->getDirAtributos();
        Atributo* atr;

        while(cabAtr!=EOF){
            atr=_arch->leeAtributo(cabAtr);

            if(!strcmp(nombre_atributo,atr->getNombre()))
                    return atr;

            cabAtr=atr->getSiguiente();
        }
    }

    return NULL;
}
int Diccionario::buscaAtributo(char* nombre_entidad,char* nombre_atributo){

	return buscaAtr(nombre_entidad,nombre_atributo) != NULL;
}
int Diccionario::buscaAtributo(Entidad* entidad,Atributo* atributo){

	return buscaAtributo(entidad->getNombre(),atributo->getNombre());
}

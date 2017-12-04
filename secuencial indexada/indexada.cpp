/* 
 * File:   Indexada.cpp
 * Author: alfredo
 * 
 * Created on 8 de abril de 2014, 12:45 PM
 */

#include "indexada.h"

Indexada::Indexada(char* nombreDic) {
    
    _nomdic=new char[strlen(nombreDic)+1];
    strcpy(_nomdic,nombreDic);
    _arch=new Archivo(nombreDic);
    _cons=new Consola();
    _cons->SetPrompt("Indexada>:");
    _cons->Init();
}

Indexada::Indexada(const Indexada& orig) {
}

Indexada::~Indexada() {
    _cons->Exit();
}

int Indexada::ImportaDiccionario(char* nombreDic, char* nombreSec){

    
    int ret=0;
    Archivo *dicSec = new Archivo(nombreSec);
    Archivo *dic =  new Archivo(nombreDic);
    
    if( dicSec->creaArchivo() ){
        dicSec->escribeCab(sizeof(DIR_t));
        DIR_t cabent=dic->leeCab();
        
        if(cabent){
            
            Entidad* ent=NULL;
            while(cabent!=EOF){
                ent=dic->leeEntidad(cabent);
                cabent=ent->getSiguiente();  
                DIR_t cabatr=ent->getDirAtributos();
                
                DIR_t pose=dicSec->escribeEntidad(ent,EOF);
                
                if(ent->getDirAtributos()!=EOF)
                    ent->setDirAtributos(dicSec->getDirFin());
                while(cabatr!=EOF){
                    Atributo* atr=dic->leeAtributo(cabatr);
                    cabatr=atr->getSiguiente();
                    DIR_t posa=dicSec->escribeAtributo(atr,EOF);
                    if(cabatr!=EOF)
                        atr->setSiguiente(dicSec->getDirFin());
                    dicSec->escribeAtributo(atr,posa);
                }
                
                if(cabent!=EOF)
                    ent->setSiguiente(dicSec->getDirFin());                 
                dicSec->escribeEntidad(ent,pose);
                
                ret=1;
            }
        }else
            printf("Error: No existe el diccionario \"%s\"\n",nombreDic);
    }
    else
        printf("Error: No se pudo creal el diccionario Indexada \"%s\"\n",nombreSec);
    
    return ret;
}
int Indexada::AltaIndexada(char* nomEntidad){
    
   
   Entidad* ent;
    _error_ = NO_ERROR;
    
    if(ent=buscaEnt(nomEntidad))
    {
        
        if(ent->getDirAtributos()!=EOF){            
            printw("\n*** Alta Indexada: ***");
            printw("\nAlta en la tabla \"%s\"\n\n",nomEntidad);
            Registro* reg=pideRegistro(ent);
            DIR_t posent=getPosEnt(nomEntidad);
            DIR_t posind;
            Indice* ind=dameIndice(ent,reg,&posind);
            if(!buscaRegistro(ent,reg,ind)){
                DIR_t dirBloque=_arch->escribeBloque(reg->getBuffer(),reg->getSize(),EOF);
                insertaRegistro(ent,posent,reg,dirBloque,ind,posind);
                printw("\n*** Registro insertado en el indice: %d ***",ind->getInicio());
            }
            else
                _error_ |= ERR_REGEXIST ;
        }
        else
            _error_ |= ERR_NOTATR;
              
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
     printw("\nAlta terminada \"%s\"\n",nomEntidad);
    return _error_;
}
int Indexada::BajaIndexada(char* nomEntidad, char* key){
    
    Entidad* ent;
    _error_ = NO_ERROR;
    void* dato;
    if(ent=buscaEnt(nomEntidad))
    {
        Registro* reg= new Registro(ent,_arch);        
       
        Atributo *atr=getAtrPrimario(ent);


        switch(atr->getTipo()){
            case ENTERO:
                if(esEntero(key))
                    dato=(void*)atoi(key);
                else
                    _error_ |= ERR_NUMERROR; 
                break;
            case LONG:
                if(esEntero(key))
                    dato=(void*)atol(key);
                else
                    _error_ |= ERR_NUMERROR; 
                break;

            case CADENA:
                dato=malloc(strlen(key));
                strcpy((char*)dato,key);
                break;
            case FLOTANTE:
            case DOBLE:       
                   if(esDecimal(key))                
                    {   
                        double d=0.0;
                        d=atof(key);
                        dato=&d;
                    }
                    else
                     _error_ |= ERR_DECIMALERROR;              
                break;
            case CARACTER:                       
                dato=(void*)key[0];
                break;
            }
        reg->empaqueta(dato,atr);        
        
        DIR_t posi;
        Indice *ind=dameIndice(ent,reg,&posi);
        printw("\n*** Baja Indexada: ***");
        
        ////MODIFICAR LA SIGUIENTE LINEA YA QUE SE HAYA BUSCADO EL INDICE////////
        if(buscaRegistro(ent,reg,ind))
        {
            printw("\n*** Registro eliminado del indice: %d ***",ind->getInicio());
            
            eliminaRegistro(ent,getPosEnt(nomEntidad),reg,ind,posi);
        }
        else
            _error_ |= ERR_REGNOTFOUND;
        
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Indexada::ModificaIndexada(char* nomEntidad, char* key){

    Entidad* ent;
    _error_ = NO_ERROR;
    void* dato;
    if(ent=buscaEnt(nomEntidad))
    {
        Registro* reg= new Registro(ent,_arch);        
       
        Atributo *atr=getAtrPrimario(ent);
        
        printw("\n*** Modifica Indexada: ***");
        printw("\nModificacion en la tabla \"%s\"\n\n",nomEntidad);

        switch(atr->getTipo()){
            case ENTERO:
                if(esEntero(key))
                    dato=(void*)atoi(key);
                else
                    _error_ |= ERR_NUMERROR; 
                break;
            case LONG:
                if(esEntero(key))
                    dato=(void*)atol(key);
                else
                    _error_ |= ERR_NUMERROR; 
                break;

            case CADENA:
                dato=malloc(strlen(key));
                strcpy((char*)dato,key);
                break;
            case FLOTANTE:
            case DOBLE:       
                   if(esDecimal(key))                
                    {   
                        double d=0.0;
                        d=atof(key);
                        dato=&d;
                    }
                    else
                     _error_ |= ERR_DECIMALERROR;              
                break;
            case CARACTER:                       
                dato=(void*)key[0];
                break;
            }
        reg->empaqueta(dato,atr);        
        
        Registro* aux;
        DIR_t posreg;
        DIR_t posind;
        Indice* ind=dameIndice(ent,reg,&posind);
        if(aux=buscaReg(ent,reg,&posreg,ind)){
           eliminaRegistro(ent,getPosEnt(nomEntidad),reg,ind,posind);
           Registro* nuevo=pideRegistroFrom(ent,aux);
           
           DIR_t posindnew;
           Indice* indnew=dameIndice(ent,nuevo,&posindnew);
           if(!buscaRegistro(ent,nuevo,indnew)){
               _arch->escribeBloque(nuevo->getBuffer(),nuevo->getSize(),posreg);
               insertaRegistro(ent,getPosEnt(nomEntidad),nuevo,posreg,indnew,posindnew);
           }
           else{
               _arch->escribeBloque(aux->getBuffer(),aux->getSize(),posreg);
               insertaRegistro(ent,getPosEnt(nomEntidad),aux,posreg,ind,posind);
               _error_ |=ERR_REGEXIST;
           }
           
        }            
        else
            _error_ |= ERR_REGNOTFOUND;
        
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Indexada::ConsultaIndexada(char* nomentidad){

    DIR_t cabatr,cabdatos,cabent,cabind;
    int err=0;
    cabent=_arch->leeCab();
    Registro *reg;
    Indice* ind;
    int nregs=0;
    if(!cabent)
        return ERR_DICNOTFOUND;
    
    //printw("\nEntra consulta\n");
    //getch();
    while(cabent!=EOF){
        Entidad* ent;
        if(!strcmp(nomentidad,""))
           ent=_arch->leeEntidad(cabent);
        else
            ent=buscaEnt(nomentidad);
        
        
        cabatr=ent->getDirAtributos();
        cabind=ent->getDirDatos();
        
        while(cabind!=EOF){
            ind=_arch->leeIndice(cabind);
            cabdatos=ind->getPtrDatos();
            reg=new Registro(ent,_arch);
            
            while(cabdatos!=EOF){
                reg->setBuffer(_arch->leeBloque(reg->getSize(),cabdatos));
              cabdatos=reg->getSiguiente();
              nregs++;
            //  printw("\nEntra contador\n");
              //getch();
            }
            cabind=ind->getSig();
        }
        cabatr=ent->getDirAtributos();
        cabdatos=ent->getDirDatos();
        printw("\n--------------------------------------------------------");
        printw("\n\t\tTabla: %s    Registros: %d",ent->getNombre(),nregs);
        printw("\n--------------------------------------------------------\n");
        //getch();
        while(cabatr!=EOF){
            Atributo *atr=_arch->leeAtributo(cabatr);
            if(atr->getLlave()==PRIMARIA)
                _cons->Printf("(k)%s\t\t",atr->getNombre());
            else
                _cons->Printf("%s\t\t",atr->getNombre());
            cabatr=atr->getSiguiente();
            //getch();
        }
        _cons->Printf("Indice\n\n");
        reg=new Registro(ent,_arch);
        cabind=ent->getDirDatos();
        while(cabind!=EOF){
            ind=_arch->leeIndice(cabind);
            cabdatos=ind->getPtrDatos();
            while(cabdatos!=EOF){
              reg->setBuffer(_arch->leeBloque(reg->getSize(),cabdatos));
              reg->imprime();
              _cons->Printf("\t%d\n",ind->getInicio());
              //printw("\nEntra registro %d\n",cabdatos);
              //getch();
              cabdatos=reg->getSiguiente();

            }
            cabind=ind->getSig();
        }
        
        printw("\n--------------------------------------------------------\n");
        if(strcmp(nomentidad,""))
             return 0;
        cabent=ent->getSiguiente();
    }
    return err;
}

Registro* Indexada::pideRegistro(Entidad* ent){
    
    DIR_t cabatr=ent->getDirAtributos();
    Registro *b=new Registro(ent,_arch);
    void* dato;
    while(cabatr!=EOF){
        Atributo* atr= _arch->leeAtributo(cabatr);
        dato=pideDato(atr);
        
        if(dato)               
           b->empaqueta(dato,atr); 
            
        cabatr=atr->getSiguiente();
    }
    
    return b;
}
Registro* Indexada::pideRegistroFrom(Entidad* ent,Registro* reg){
    
    DIR_t cabatr=ent->getDirAtributos();
    Registro *b=new Registro(ent,_arch);
    void* dato;
    while(cabatr!=EOF){
        Atributo* atr= _arch->leeAtributo(cabatr);
        dato=pideDatoFrom(atr,reg->desempaqueta(atr));
        
        if(dato)               
           b->empaqueta(dato,atr); 
            
        cabatr=atr->getSiguiente();
    }
    
    return b;
}
void* Indexada::pideDato(Atributo* atr){
    
    void* dato=NULL;
    int t;
    char in[100]="";
    bzero(in,100);
    if(atr->getLlave()==PRIMARIA)
        printw("-> (k) %s: ",atr->getNombre());
    else
        printw("-> %s: ",atr->getNombre());
    
    switch(atr->getTipo()){
            case ENTERO:
            case LONG:
                dato=(void*)_cons->ReadNumber();
                break;
            case CADENA:
                dato=malloc(_cons->ReadLine(in));
                strcpy((char*)dato,in);
                break;
            case FLOTANTE:
            case DOBLE:       
                    double d;
                    d=_cons->ReadDecimal();
                    dato=&d;               
                break;
            case CARACTER:
                char c;
                c=_cons->ReadChar();
                   dato=(void*)c;
                break;
        }
    
    return dato;
}
void* Indexada::pideDatoFrom(Atributo* atr, void* dato){
    
    void* ret=NULL;
    int t;
    char in[100]="";
    bzero(in,100);
    if(atr->getLlave()==PRIMARIA)
        printw("-> (k) %s: ",atr->getNombre());
    else
        printw("-> %s: ",atr->getNombre());
    
    switch(atr->getTipo()){
            case ENTERO:
            case LONG:
                ret=(void*)_cons->ReadNumberFrom((long long)dato);
                break;
            case CADENA:
                char in[MAX_INPUT];
                strcpy(in,(char*)dato);
                ret=malloc(_cons->ReadLineFrom(in));
                strcpy((char*)ret,in);
                break;
            case FLOTANTE:
            case DOBLE:       
                    double d;
                    d=*(float*)dato;
                    d=_cons->ReadDecimalFrom(d);
                    ret=&d;               
                break;
            case CARACTER:
                char c;
                c=_cons->ReadCharFrom(*(char*)dato);
                ret=(void*)c;
                break;
        }
    
    return ret;
}
int Indexada::esEntero(char* cad){
    
    char* aux=cad;
    if(aux[0]=='-')
        aux++;
    
    while(aux && *aux!='\0')
        if(!isdigit(*aux++))
            return 0;
    return 1;
}
int Indexada::esDecimal(char* cad){
 
    char* aux=cad;
    int tienePunto=0;
    if(aux[0]=='-')
        aux++;
    
    while(aux && *aux!='\0'){
       
        if(*aux=='.')
            if(!tienePunto)
                tienePunto=1;
            else 
                return 0;
        
        if(!isdigit(*aux) || *aux!='.')
            return 0;   
        
        aux++;
    }
    return 1;
}

int Indexada::insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg, Indice* indice, DIR_t posind){
    
    
    
    DIR_t cabdatos=indice->getPtrDatos();
    Registro* bloq= new Registro(ent,_arch);
    Atributo* atr;
    
    atr=getAtrPrimario(ent);
    
    
    if(cabdatos!=EOF)
        bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabdatos));
    
    if(cabdatos==EOF || reg->compara(bloq,atr)<0)
    {
        reg->setSiguiente(cabdatos);
        indice->setPtrDatos(posReg);
        _arch->escribeIndice(indice,posind);
    }
    else
    {
        Registro* bloqant=bloq;       
        DIR_t posAnt=cabdatos;
        while(cabdatos!=EOF && reg->compara(bloq,atr)>0){
            posAnt=cabdatos;
            bloqant=bloq;
            
            cabdatos=bloq->getSiguiente();            
            if(cabdatos!=EOF)
            {
                bloq= new Registro(ent,_arch);
                bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabdatos));
            }
            
        }
        
        reg->setSiguiente(bloqant->getSiguiente());
        bloqant->setSiguiente(posReg);
        _arch->escribeBloque(bloqant->getBuffer(),bloqant->getSize(),posAnt);        
    }
    
    _arch->escribeBloque(reg->getBuffer(),reg->getSize(),posReg);
}
DIR_t Indexada::eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,Indice* indice, DIR_t posind){
    
    DIR_t cabDatos=indice->getPtrDatos();
    Registro* bloq= new Registro(ent,_arch);
    Atributo* atr;
    
    atr=getAtrPrimario(ent);
    if(cabDatos!=EOF)
        bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
    
    if(reg->compara(bloq,atr)==0)
    {
        indice->setPtrDatos(bloq->getSiguiente());
        _arch->escribeIndice(indice,posind);
        
    }
    else{
        
        Registro* bloqant;
        DIR_t posAnt;
        while(cabDatos!=EOF && reg->compara(bloq,atr)!=0){
            posAnt=cabDatos;
            bloqant=bloq;
            
            cabDatos=bloq->getSiguiente();            
            if(cabDatos!=EOF)
            {
                bloq= new Registro(ent,_arch);
                bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
            }
            
        }
        bloqant->setSiguiente(bloq->getSiguiente());
        _arch->escribeBloque(bloqant->getBuffer(),bloqant->getSize(),posAnt);        
    }
    return cabDatos;
}
int Indexada::buscaRegistro(Entidad* ent, Registro* reg,Indice* indice){
    DIR_t p;
     return buscaReg(ent,reg,&p,indice)!=NULL;
}
Registro* Indexada::buscaReg(Entidad* ent, Registro* reg, DIR_t *pos,Indice* indice){
    
    Registro *bloque=new Registro(ent,_arch);
    Atributo* atr=getAtrPrimario(ent);
    
    DIR_t cabreg=indice->getPtrDatos();

    while(cabreg!=EOF){

        bloque->setBuffer(_arch->leeBloque(bloque->getSize(),cabreg));
        *pos=cabreg;
        if(!reg->compara(bloque,atr))   
            return bloque;
        cabreg=bloque->getSiguiente();
    }
            
        
    return NULL;
}

Entidad* Indexada::buscaEnt(char* nombre){

	DIR_t  cab= _arch->leeCab();
	
    if(!cab)
        _error_ |= ERR_DICNOTFOUND;
    else
    {   
    	Entidad* ent;     
        while(cab!=EOF){
            ent=_arch->leeEntidad(cab);
            if(!strcmp(nombre,ent->getNombre()))
                return ent;

            cab=ent->getSiguiente();
        }
        return NULL;
    }
    return NULL;
}
int Indexada::buscaEntidad(char* nombre){

	return (this->buscaEnt(nombre) != NULL);
        
}
int Indexada::buscaEntidad(Entidad* entidad){

    return this->buscaEntidad(entidad->getNombre());
}

DIR_t Indexada::getPosEnt(char* NombreEntidad){
    DIR_t  cab= _arch->leeCab();
	
    if(!cab)
        _error_ |= ERR_DICNOTFOUND;
    else
    {   
    	Entidad* ent;     
        while(cab!=EOF){
            ent=_arch->leeEntidad(cab);
            if(!strcmp(NombreEntidad,ent->getNombre()))
                return cab;

            cab=ent->getSiguiente();
        }
    }
    return 0;
}

Indice* Indexada::dameIndice(Entidad* ent, Registro* reg, DIR_t *posIndice){
    
    Atributo* atr= getAtrPrimario(ent);
    Indice* ind=buscaIndice(ent,reg,atr,posIndice);
    
    if(!ind){
        int clave;
    
        switch(atr->getTipo()){
        
            case ENTERO: 
                clave=(int)reg->desempaqueta(atr);
                break;
            case LONG: clave=(long)reg->desempaqueta(atr);break;
            case CADENA: 
                clave=((char*)reg->desempaqueta(atr))[0];break;
            case FLOTANTE:
            case DOBLE:
                clave=(int)reg->desempaqueta(atr);break;
            case CARACTER:
                clave=*(char*)reg->desempaqueta(atr);
                break;        
        }
        ind=new Indice(clave/RANGO,(clave/RANGO)*RANGO+(RANGO-1));
        *posIndice=_arch->escribeIndice(ind,EOF);
        InsertaIndice(ent, getPosEnt(ent->getNombre()),ind, *posIndice);
    }
    
    return ind;
}
Indice* Indexada::buscaIndice(Entidad* ent, Registro* reg, Atributo* atrPrimario, DIR_t *posIndice){
    
    DIR_t cabind=ent->getDirDatos();
    
    int clave;
    
    switch(atrPrimario->getTipo()){
        
        case ENTERO: 
            clave=(int)reg->desempaqueta(atrPrimario);
            break;
        case LONG: clave=(long)reg->desempaqueta(atrPrimario);break;
        case CADENA: 
            clave=((char*)reg->desempaqueta(atrPrimario))[0];break;
        case FLOTANTE:
        case DOBLE:
            clave=(int)reg->desempaqueta(atrPrimario);break;
        case CARACTER:
            clave=*(char*)reg->desempaqueta(atrPrimario);
            break;
        
        }
    
    while(cabind!=EOF){
        Indice* ind=_arch->leeIndice(cabind);
        if(ind->getInicio()==clave/RANGO)
        {   *posIndice=cabind;
            return ind;
        }
        
        cabind=ind->getSig();
        
    }
    
    return NULL;
}
void Indexada::InsertaIndice(Entidad* ent,DIR_t posent,Indice* ind, DIR_t posind){
    
    DIR_t cabind=ent->getDirDatos();
    Indice* indice;
    
    if(cabind!=EOF)
        indice=_arch->leeIndice(cabind);
    
    if(cabind==EOF || (ind->getInicio()< indice->getInicio())){
        ent->setDirDatos(posind);
        _arch->escribeEntidad(ent,posent);
    }
    else
    {
        indice=_arch->leeIndice(cabind);
        Indice* indant=indice;
        DIR_t posant=cabind;
        
        while(cabind!=EOF && (ind->getInicio()> indice->getInicio()) ){
            indant=indice;
            posant=cabind;            
            cabind=indice->getSig();
            if(cabind!=EOF)
                indice=_arch->leeIndice(cabind);
        }
        ind->setSig(indant->getSig());
        indant->setSig(posind);
        _arch->escribeIndice(indant,posant);
    }
    _arch->escribeIndice(ind,posind);
}

Atributo* Indexada::getAtrPrimario(Entidad* ent){
    DIR_t cabatr=ent->getDirAtributos();
    Atributo* atr=NULL;
    while(cabatr!=EOF){
        atr=_arch->leeAtributo(cabatr);        
        if(atr->getLlave()==PRIMARIA)
            return atr;
        cabatr=atr->getSiguiente();
    }
    
    return NULL;
}
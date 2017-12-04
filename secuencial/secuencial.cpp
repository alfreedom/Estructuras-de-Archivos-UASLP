/* 
 * File:   Secuencial.cpp
 * Author: alfredo
 * 
 * Created on 8 de abril de 2014, 12:45 PM
 */

#include "secuencial.h"

Secuencial::Secuencial(char* nombreDic) {
    
    _nomdic=new char[strlen(nombreDic)+1];
    strcpy(_nomdic,nombreDic);
    _arch=new Archivo(nombreDic);
    _cons=new Consola();
    _cons->SetPrompt(">>:");
    _cons->Init();
}

Secuencial::Secuencial(const Secuencial& orig) {
}

Secuencial::~Secuencial() {
    _cons->Exit();
}

int Secuencial::ImportaDiccionario(char* nombreDic, char* nombreSec){

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
                
            }
        }else
            printw("Error: No existe el diccionario \"%s\"\n",nombreDic);
    }
    else
        printw("Error: No se pudo creal el diccionario secuencial \"%s\"\n",nombreSec);
    
        
}
int Secuencial::AltaSecuencial(char* nomEntidad){
    
   
   Entidad* ent;
    _error_ = NO_ERROR;
    
    if(ent=buscaEnt(nomEntidad))
    {
        
        if(ent->getDirAtributos()!=EOF){            
        
            printw("\n Alta de la tabla \"%s\"\n",nomEntidad);
            Registro* reg=pideRegistro(ent);
            DIR_t posent=getPosEnt(nomEntidad);
            if(!buscaRegistro(ent,reg)){
                DIR_t dirBloque=_arch->escribeBloque(reg->getBuffer(),reg->getSize(),EOF);
                insertaRegistro(ent,posent,reg,dirBloque);

            }
            else
                _error_ |= ERR_REGEXIST ;
        }
        else
            _error_ |= ERR_NOTATR;
              
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
     
    return _error_;
}
int Secuencial::BajaSecuencial(char* nomEntidad, char* key){
    
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
        
        if(buscaRegistro(ent,reg))
            eliminaRegistro(ent,getPosEnt(nomEntidad),reg);
        else
            _error_ |= ERR_REGNOTFOUND;
        
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Secuencial::ModificaSecuencial(char* nomEntidad, char* key){

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
        
        Registro* aux;
        DIR_t posreg;
        if(aux=buscaReg(ent,reg,&posreg)){
           eliminaRegistro(ent,getPosEnt(nomEntidad),reg);
           Registro* nuevo=pideRegistroFrom(ent,aux);
           if(!buscaRegistro(ent,nuevo)){
               _arch->escribeBloque(nuevo->getBuffer(),nuevo->getSize(),posreg);
               insertaRegistro(ent,getPosEnt(nomEntidad),nuevo,posreg);
           }
           else{
               _arch->escribeBloque(aux->getBuffer(),aux->getSize(),posreg);
               insertaRegistro(ent,getPosEnt(nomEntidad),aux,posreg);
               _error_ |=ERR_REGEXIST;
           }
           
        }            
        else
            _error_ |= ERR_REGNOTFOUND;
        
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Secuencial::ConsultaSecuencial(char* nomentidad){

    DIR_t cabatr,cabdatos,cabent;
    int err=0;
    cabent=_arch->leeCab();
    
    if(!cabent)
        return ERR_DICNOTFOUND;
    
    while(cabent!=EOF){
        Entidad* ent;
        if(!strcmp(nomentidad,""))
           ent=_arch->leeEntidad(cabent);
        else
            ent=buscaEnt(nomentidad);
        
        
        cabatr=ent->getDirAtributos();
        cabdatos=ent->getDirDatos();
        
        Registro *reg=new Registro(ent,_arch);
        int nregs=0;
        while(cabdatos!=EOF){
            reg->setBuffer(_arch->leeBloque(reg->getSize(),cabdatos));
          cabdatos=reg->getSiguiente();
          nregs++;
        }
        cabatr=ent->getDirAtributos();
        cabdatos=ent->getDirDatos();
        printw("\n--------------------------------------------------------");
        printw("\n\t\tTabla: %s    Registros: %d",ent->getNombre(),nregs);
        printw("\n--------------------------------------------------------\n");
        while(cabatr!=EOF){
            Atributo *atr=_arch->leeAtributo(cabatr);
            if(atr->getLlave()==PRIMARIA)
                _cons->Printf("(k)%s\t\t",atr->getNombre());
            else
                _cons->Printf("%s\t\t",atr->getNombre());
            cabatr=atr->getSiguiente();
        }
        _cons->Printf("\n\n");
        reg=new Registro(ent,_arch);
        while(cabdatos!=EOF){
          reg->setBuffer(_arch->leeBloque(reg->getSize(),cabdatos));
          reg->imprime();
          _cons->Printf("\n");
          cabdatos=reg->getSiguiente();
          
        }
        
        printw("\n--------------------------------------------------------\n");
        if(strcmp(nomentidad,""))
             return 0;
        cabent=ent->getSiguiente();
    }
    return err;
}

Registro* Secuencial::pideRegistro(Entidad* ent){
    
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
Registro* Secuencial::pideRegistroFrom(Entidad* ent,Registro* reg){
    
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
void* Secuencial::pideDato(Atributo* atr){
    
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
void* Secuencial::pideDatoFrom(Atributo* atr, void* dato){
    
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
int Secuencial::esEntero(char* cad){
    
    char* aux=cad;
    if(aux[0]=='-')
        aux++;
    
    while(aux && *aux!='\0')
        if(!isdigit(*aux++))
            return 0;
    return 1;
}
int Secuencial::esDecimal(char* cad){
 
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

int Secuencial::insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg){
    
    DIR_t cabDatos=ent->getDirDatos();
    Registro* bloq= new Registro(ent,_arch);
    Atributo* atr;
    
    atr=getAtrPrimario(ent);
    
    if(cabDatos!=EOF)
        bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
    
    if(cabDatos==EOF || reg->compara(bloq,atr)<0)
    {
        reg->setSiguiente(cabDatos);
        ent->setDirDatos(posReg);
        _arch->escribeEntidad(ent,posEnt);
    }
    else
    {
        Registro* bloqant=bloq;       
        DIR_t posAnt=cabDatos;
        while(cabDatos!=EOF && reg->compara(bloq,atr)>0){
            posAnt=cabDatos;
            bloqant=bloq;
            
            cabDatos=bloq->getSiguiente();            
            if(cabDatos!=EOF)
            {
                bloq= new Registro(ent,_arch);
                bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
            }
            
        }
        
        reg->setSiguiente(bloqant->getSiguiente());
        bloqant->setSiguiente(posReg);
        _arch->escribeBloque(bloqant->getBuffer(),bloqant->getSize(),posAnt);        
    }
    
    _arch->escribeBloque(reg->getBuffer(),reg->getSize(),posReg);
}
DIR_t Secuencial::eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg){
    
    DIR_t cabDatos=ent->getDirDatos();
    Registro* bloq= new Registro(ent,_arch);
    Atributo* atr;
    
    atr=getAtrPrimario(ent);
    
    if(cabDatos!=EOF)
        bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
    
    if(reg->compara(bloq,atr)==0)
    {
        ent->setDirDatos(bloq->getSiguiente());
        _arch->escribeEntidad(ent,posEnt);
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
int Secuencial::buscaRegistro(Entidad* ent, Registro* reg){
    DIR_t p;
     return buscaReg(ent,reg,&p)!=NULL;
}
Registro* Secuencial::buscaReg(Entidad* ent, Registro* reg, DIR_t *pos){
    
    DIR_t cabreg=ent->getDirDatos();
    Registro *bloque=new Registro(ent,_arch);
    Atributo* atr=getAtrPrimario(ent);
    
    while(cabreg!=EOF){

        bloque->setBuffer(_arch->leeBloque(bloque->getSize(),cabreg));
        *pos=cabreg;
        if(!reg->compara(bloque,atr))   
            return bloque;
        cabreg=bloque->getSiguiente();
    }
   
    return NULL;
}
Entidad* Secuencial::buscaEnt(char* nombre){

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
int Secuencial::buscaEntidad(char* nombre){

	return (this->buscaEnt(nombre) != NULL);
        
}
int Secuencial::buscaEntidad(Entidad* entidad){

    return this->buscaEntidad(entidad->getNombre());
}

DIR_t Secuencial::getPosEnt(char* NombreEntidad){
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
Atributo* Secuencial::getAtrPrimario(Entidad* ent){
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
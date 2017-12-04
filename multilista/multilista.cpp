/* 
 * File:   Multilista.cpp
 * Author: alfredo
 * 
 * Created on 8 de abril de 2014, 12:45 PM
 */

#include "multilista.h"
#include "listabloque.h"
Multilista::Multilista(char* nombreDic) {
    
    _nomdic=new char[strlen(nombreDic)+1];
    strcpy(_nomdic,nombreDic);
    _arch=new Archivo(nombreDic);
    _cons=new Consola();
    _cons->SetPrompt("Multilista>:");
    _cons->Init();
}

Multilista::Multilista(const Multilista& orig) {
}

Multilista::~Multilista() {
    _cons->Exit();
}

int Multilista::ImportaDiccionario(char* nombreDic, char* nombreSec){

    
    int ret=0;
    Archivo *dicMul = new Archivo(nombreSec);
    Archivo *dic =  new Archivo(nombreDic);
    
    if( dicMul->creaArchivo() ){
        dicMul->escribeCab(sizeof(DIR_t));
        DIR_t cabent=dic->leeCab();
        
        if(cabent){
            
            Entidad* ent=NULL;
            while(cabent!=EOF){
                ent=dic->leeEntidad(cabent);
                cabent=ent->getSiguiente();  
                DIR_t cabatr=ent->getDirAtributos();
                
                DIR_t pose=dicMul->escribeEntidad(ent,EOF);
                
                if(ent->getDirAtributos()!=EOF)
                    ent->setDirAtributos(dicMul->getDirFin());
                while(cabatr!=EOF){
                    Atributo* atr=dic->leeAtributo(cabatr);
                    cabatr=atr->getSiguiente();
                    atr->setLlave(NONE);
                    DIR_t posa=dicMul->escribeAtributo(atr,EOF);
                    if(cabatr!=EOF)
                        atr->setSiguiente(dicMul->getDirFin());
                    dicMul->escribeAtributo(atr,posa);
                }
                
                if(cabent!=EOF)
                    ent->setSiguiente(dicMul->getDirFin());                 
                dicMul->escribeEntidad(ent,pose);
                
                ret=1;
            }
        }else
            printf("Error: No existe el diccionario \"%s\"\n",nombreDic);
    }
    else
        printf("Error: No se pudo creal el diccionario Multilista \"%s\"\n",nombreSec);
    
    return ret;
}
int Multilista::AltaMultilista(char* nomEntidad){
    
   
   Entidad* ent;
    _error_ = NO_ERROR;
    
    if(ent=buscaEnt(nomEntidad))
    {
        
        if(ent->getDirAtributos()!=EOF){            
            printw("\n*** Alta Multilista: ***");
            printw("\nAlta en la tabla \"%s\"\n\n",nomEntidad);
            Registro* reg=pideRegistro(ent);
            DIR_t posent=getPosEnt(nomEntidad);
            DIR_t posind;
            Indice* ind=NULL;//dameIndice(ent,reg,&posind);
            printw("\n*** ***");
            if(!buscaRegistro(ent,reg,ind)){
                DIR_t dirBloque=_arch->escribeBloque(reg->getBuffer(),reg->getSize(),EOF);
                insertaRegistro(ent,posent,reg,dirBloque,ind,posind);
                //printw("\n*** Registro insertado en el indice: %d ***",ind->getInicio());
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
int Multilista::BajaMultilista(char* nomEntidad,char* nomAtributo, char* key){
    
    Entidad* ent;
    _error_ = NO_ERROR;
    void* dato;
    Atributo *atr;
    listabloque *lb;
    if(ent=buscaEnt(nomEntidad))
    {
        if(atr=buscaAtr(ent,nomAtributo)){
            
            
            Registro* reg= new Registro(ent,_arch);        



            printw("\n*** Modifica Multilista: ***");
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
            Indice* ind=NULL;//dameIndice(ent,reg,&posind);
            lb=buscaRegistros(ent,reg,atr);
            
            int indreg;
            
            if(lb->Size()){
                lb->Rewind();
                
                int i=1;
                printw("\n\nSeleccione el registro a modificar:\n");
                while((aux=lb->GetNext())){
                    printw("\n%d) ",i++);
                    aux->imprime();
                }
                printw("\n\nRegistro (0 para cancelar): ");
                indreg=_cons->ReadNumber();
                if(indreg==0)
                    return CANCEL;
                if(indreg<=lb->Size())
                {
                    lb->Rewind();
                    for(int i=0; i<indreg;i++){
                        aux=lb->GetNext();      
                        //aux->imprime();
                        
                    }
                    eliminaRegistro(ent,getPosEnt(nomEntidad),aux,NULL,0);
                    
                }
                
            }
            else
                _error_ |= ERR_REGNOTFOUND;
           // if(aux=buscaReg(ent,reg,&posreg,ind)){
             //  eliminaRegistro(ent,getPosEnt(nomEntidad),reg,ind,posind);
              // Registro* nuevo=pideRegistroFrom(ent,aux);

               //DIR_t posindnew;
               //Indice* indnew=NULL;//dameIndice(ent,nuevo,&posindnew);
               
               //else{
                 //  _arch->escribeBloque(aux->getBuffer(),aux->getSize(),posreg);
                   //insertaRegistro(ent,getPosEnt(nomEntidad),aux,posreg,ind,posind);
                   //_error_ |=ERR_REGEXIST;
               //}

            //}            
            //else
               // _error_ |= ERR_REGNOTFOUND;
        }
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Multilista::ModificaMultilista(char* nomEntidad,char* nomAtributo, char* key){

    Entidad* ent;
    _error_ = NO_ERROR;
    void* dato;
    Atributo *atr;
    listabloque *lb;
    if(ent=buscaEnt(nomEntidad))
    {
        if(atr=buscaAtr(ent,nomAtributo)){
            
            
            Registro* reg= new Registro(ent,_arch);        



            printw("\n*** Modifica Multilista: ***");
            printw("\nModificacion en la tabla \"%s\"\n",nomEntidad);

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
            Indice* ind=NULL;//dameIndice(ent,reg,&posind);
            lb=buscaRegistros(ent,reg,atr);
            lb->Ordena(atr);
            int indreg;
            if(lb->Size()){
                lb->Rewind();
                Registro *aux;
                int i=1;
                printw("\n*************************************");
                printw("\nSeleccione el registro a modificar:\n");
                while((aux=lb->GetNext())){
                    printw("\n%d) ",i++);
                    aux->imprime();
                }
                printw("\n\n*************************************");
                printw("\n\nRegistro (0 para cancelar): ");                
                indreg=_cons->ReadNumber();
                printw("\n*************************************\n");
                if(indreg==0)
                    return CANCEL;
                if(indreg<=lb->Size())
                {
                    lb->Rewind();
                    for(int i=0; i<indreg;i++){
                        reg=lb->GetNext();                        
                    }
                    //buscaReg(ent,reg,&posreg,NULL);
                    posreg=eliminaRegistro(ent,getPosEnt(nomEntidad),reg,NULL,0);
                    Registro* nuevo=pideRegistroFrom(ent,reg);
                    
                    if(!buscaRegistro(ent,nuevo,NULL)){
                        _arch->escribeBloque(nuevo->getBuffer(),nuevo->getSize(),posreg);  
                        //printw("1:  pos: %ld  size: %d",posreg,nuevo->getSize());
                        insertaRegistro(ent,getPosEnt(nomEntidad),nuevo,posreg,NULL,0);
                    }
                    else{
                       DIR_t posnew= _arch->escribeBloque(reg->getBuffer(),reg->getSize(),EOF); 
                        printw("1:  pos: %ld  size: %d",posreg,nuevo->getSize());
                        insertaRegistro(ent,getPosEnt(nomEntidad),reg,posnew,NULL,0);
                        _error_ |=ERR_REGEXIST;
                   }
                }
                else
                    printw("\nError: numero de registro invalido.\n");
                
            }
            else
                _error_ |= ERR_REGNOTFOUND;
           // if(aux=buscaReg(ent,reg,&posreg,ind)){
             //  eliminaRegistro(ent,getPosEnt(nomEntidad),reg,ind,posind);
              // Registro* nuevo=pideRegistroFrom(ent,aux);

               //DIR_t posindnew;
               //Indice* indnew=NULL;//dameIndice(ent,nuevo,&posindnew);
               
               //else{
                 //  _arch->escribeBloque(aux->getBuffer(),aux->getSize(),posreg);
                   //insertaRegistro(ent,getPosEnt(nomEntidad),aux,posreg,ind,posind);
                   //_error_ |=ERR_REGEXIST;
               //}

            //}            
            //else
               // _error_ |= ERR_REGNOTFOUND;
        }
    }else
        _error_ |= ERR_ENTNOTFOUND;
    
    return _error_;
}
int Multilista::ConsultaMultilista(char* nomentidad,char* nomatributo){

    DIR_t cabatr,cabdatos,cabent,cabind;
    int err=0;
    cabent=_arch->leeCab();
    Registro *reg;
    Indice* ind;
    int nregs=0;
    Entidad *enti;
    Atributo* atr;
    listabloque lb;
    DIR_t cabreg;
    
    if(!strcmp(nomentidad,"ALL")){
        if(!cabent)
            return ERR_DICNOTFOUND;
        
        while(cabent!=EOF){
            enti=_arch->leeEntidad(cabent);
            nregs=0;
            int natrs=0;
            int i=1;
            cabreg=enti->getDirDatos();
            while(cabreg!=EOF){
                reg= new Registro(enti,_arch);
                reg->setBuffer(_arch->leeBloque(reg->getSize(),cabreg));
                nregs++;
                cabreg=reg->getSiguiente();
            }
            
            cabatr=enti->getDirAtributos();
            while(cabatr!=EOF){
                Atributo *atr=_arch->leeAtributo(cabatr);
                natrs++;
                cabatr=atr->getSiguiente();
            }
            printw("\n--------------------------------------------------------");
            printw("\n   Entidad: %s   # Atributos: %d   # Registros: %d",enti->getNombre(),natrs,nregs);
            printw("\n--------------------------------------------------------\n");

            cabatr=enti->getDirAtributos();
            while(cabatr!=EOF){
                Atributo *atr=_arch->leeAtributo(cabatr);
                _cons->Printf("\n%d) %s",i++,atr->getNombre());
                cabatr=atr->getSiguiente();
            }
            _cons->Printf("\n");
            cabent=enti->getSiguiente();
        }
    }
    else{
    
        if((enti=buscaEnt(nomentidad))){
            if(!strcmp(nomatributo,"ALL")){
                cabatr=enti->getDirAtributos();
                atr=_arch->leeAtributo(cabatr);
            }
            else
                atr=buscaAtr(enti,nomatributo);

            if(atr){

                cabreg=enti->getDirDatos();
                while(cabreg!=EOF){
                    reg= new Registro(enti,_arch);
                    reg->setBuffer(_arch->leeBloque(reg->getSize(),cabreg));
                    lb.Add(reg);
                    cabreg=reg->getSiguiente();
                }
                lb.Ordena(atr);

                printw("\n--------------------------------------------------------");
                printw("\n\t\tTabla: %s    Registros: %d",enti->getNombre(),lb.Size());
                printw("\n--------------------------------------------------------\n");

                cabatr=enti->getDirAtributos();
                while(cabatr!=EOF){
                    Atributo *atr=_arch->leeAtributo(cabatr);
                    _cons->Printf("%s\t\t",atr->getNombre());
                    cabatr=atr->getSiguiente();
                }
                printw("\n");
                Registro* raux;
                lb.Rewind();
                while((raux=lb.GetNext())!=NULL){
                    printw("\n");
                    raux->imprime();  
                }
                printw("\n--------------------------------------------------------\n");


            }
            else
                return ERR_ATRNOTFOUND;
    }
    else
        return ERR_ENTNOTFOUND;
    }
    
   /* 
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
    }*/
    return err;
}

Registro* Multilista::pideRegistro(Entidad* ent){
    
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
Registro* Multilista::pideRegistroFrom(Entidad* ent,Registro* reg){
    
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
void* Multilista::pideDato(Atributo* atr){
    
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
void* Multilista::pideDatoFrom(Atributo* atr, void* dato){
    
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
int Multilista::esEntero(char* cad){
    
    char* aux=cad;
    if(aux[0]=='-')
        aux++;
    
    while(aux && *aux!='\0')
        if(!isdigit(*aux++))
            return 0;
    return 1;
}
int Multilista::esDecimal(char* cad){
 
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

int Multilista::isRegistroEqual(Entidad* ent, Registro *r1,Registro *r2){
    
    DIR_t cabatr=ent->getDirAtributos();
    Atributo* atr;
    int found=1;
    while(cabatr!=EOF && found){
            atr=_arch->leeAtributo(cabatr);
            if(r1->compara(r2,atr))
               found=0;
            
            cabatr=atr->getSiguiente();
        }
        
        
     return found;
}
int Multilista::insertaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,DIR_t posReg, Indice* indice, DIR_t posind){
    
    
    
    DIR_t cabdatos=ent->getDirDatos();
    
    //atr=getAtrPrimario(ent);
    
    
    //if(cabdatos!=EOF)
        //bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabdatos));
    
    //if(cabdatos==EOF || reg->compara(bloq,atr)<0)
    {
        reg->setSiguiente(cabdatos);
        ent->setDirDatos(posReg);
        //indice->setPtrDatos(posReg);
        _arch->escribeBloque(reg->getBuffer(),reg->getSize(),posReg); //***
        _arch->escribeEntidad(ent,posEnt);
    }
   /* else
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
    }*/
    
    //_arch->escribeBloque(reg->getBuffer(),reg->getSize(),posReg);
}
DIR_t Multilista::eliminaRegistro(Entidad* ent,DIR_t posEnt, Registro* reg,Indice* indice, DIR_t posind){
    
    DIR_t cabDatos=ent->getDirDatos();
    Registro* bloq= new Registro(ent,_arch);
    Atributo* atr;
    
    //atr=getAtrPrimario(ent);
    if(cabDatos!=EOF)
        bloq->setBuffer(_arch->leeBloque(bloq->getSize(),cabDatos));
    
    if(isRegistroEqual(ent,bloq,reg))
    {
        ent->setDirDatos(reg->getSiguiente());
        printw("\ncabecera: %ld",ent->getDirDatos());
        _arch->escribeEntidad(ent,posEnt);
        
    }
    else{
        
        Registro* bloqant;
        DIR_t posAnt;
        while(cabDatos!=EOF && !isRegistroEqual(ent,bloq,reg)){
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
        _arch->escribeBloque(bloqant->getBuffer(),bloq->getSize(),posAnt);        
    }
   
    return cabDatos;
}
int Multilista::buscaRegistro(Entidad* ent, Registro* reg,Indice* indice){
    DIR_t p;
     return buscaReg(ent,reg,&p,indice)!=NULL;
}
Registro* Multilista::buscaReg(Entidad* ent, Registro* reg, DIR_t *pos,Indice* indice){
    
    Registro *bloque=new Registro(ent,_arch);
    DIR_t cabreg=ent->getDirDatos();   
        
    while(cabreg!=EOF){

        bloque=new Registro(ent,_arch);
        bloque->setBuffer(_arch->leeBloque(bloque->getSize(),cabreg));
        *pos=cabreg;
        
        if(isRegistroEqual(ent,reg,bloque))
            return bloque;
          
        cabreg=bloque->getSiguiente();
    }
    
  
            
        
    return NULL;
}
listabloque* Multilista::buscaRegistros(Entidad* ent, Registro* reg, Atributo* atrRef){
    
    Registro *bloque;
    Atributo* atr;
    listabloque* lb=new listabloque();
    DIR_t cabreg=ent->getDirDatos();
    int found=1;
    
        
    while(cabreg!=EOF){
        bloque=new Registro(ent,_arch);
        bloque->setBuffer(_arch->leeBloque(bloque->getSize(),cabreg));
        
        if(!reg->compara(bloque,atrRef))
            lb->Add(bloque);
             
                
        cabreg=bloque->getSiguiente();
    }
    
    lb->Ordena(atrRef);
            
        
    return lb;
}
Entidad* Multilista::buscaEnt(char* nombre){

	DIR_t  cab= _arch->leeCab();
	Entidad* ent;  
    if(!cab)
        _error_ |= ERR_DICNOTFOUND;
    else
    {   
    	   
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
int Multilista::buscaEntidad(char* nombre){

	return (this->buscaEnt(nombre) != NULL);
        
}
int Multilista::buscaEntidad(Entidad* entidad){

    return this->buscaEntidad(entidad->getNombre());
}

Atributo* Multilista::buscaAtr(Entidad* entidad, char* nombreAtributo){

    DIR_t cabatr=entidad->getDirAtributos();
    Atributo *atr;
    
    while(cabatr!=EOF){
        atr=_arch->leeAtributo(cabatr);
        
        if(!strcmp(nombreAtributo,atr->getNombre()))
                return atr;
        cabatr=atr->getSiguiente();
    }
    
    return NULL;
}
int Multilista::buscaAtributo(Entidad* entidad, char* nombreAtributo){
    return buscaAtr(entidad,nombreAtributo)!=NULL;
}
int Multilista::buscaAtributo(Entidad* entidad,Atributo* atributo){
    return buscaAtr(entidad,atributo->getNombre())!=NULL;
}
    
DIR_t Multilista::getPosEnt(char* NombreEntidad){
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

Indice* Multilista::dameIndice(Entidad* ent, Registro* reg, DIR_t *posIndice){
    
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
Indice* Multilista::buscaIndice(Entidad* ent, Registro* reg, Atributo* atrPrimario, DIR_t *posIndice){
    
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
void Multilista::InsertaIndice(Entidad* ent,DIR_t posent,Indice* ind, DIR_t posind){
    
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

Atributo* Multilista::getAtrPrimario(Entidad* ent){
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
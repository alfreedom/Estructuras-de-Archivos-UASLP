/* 
 * File:   consola.cpp
 * Author: alfredo
 * 
 * Created on 10 de abril de 2014, 09:04 PM
 */

#include <ctype.h>

#include "consola.h"





Consola::Consola() { 
  
    strcpy(_prompt,"@:");
    
}

Consola::Consola(const Consola& orig) {
    
   
    
}

Consola::~Consola() {
}
int Consola::Run(){
    
    
    this->Init();
    int cc=0;
    char line[100];
    printw("\nIngrese texto: ");
    cc=this->ReadLine(line);
    printw("# %d : %s",cc,line);
    printw("\nIngrese texto: ");
    cc=this->ReadLine(line);
    printw("# %d : %s",cc,line);
    printw("\nIngrese texto: ");
    cc=this->ReadLine(line);
    printw("# %d : %s",cc,line);
    
    printw("\nIngrese char: ");
    printw("%c",this->ReadChar());
    printw("\nIngrese char: ");
    printw("%c",this->ReadChar());
    printw("\nIngrese char: ");
    printw("%c",this->ReadChar());
 
    printw("\nIngrese entero: ");
    printw("%d",this->ReadNumber());
    printw("\nIngrese entero: ");
    printw("%d",this->ReadNumber());
    printw("\nIngrese entero: ");
    printw("%d",this->ReadNumber());
    
    printw("\nIngrese flotante: ");
    printw("%f",this->ReadDecimal());
    printw("\nIngrese flotante: ");
    printw("%f",this->ReadDecimal());
    printw("\nIngrese flotante: ");
    printw("%f",this->ReadDecimal());
    
    getch();
    
    this->Exit();
    /*
    int exit=0;
    int tecla;
    int count=0;
    initscr();
    keypad(stdscr, TRUE);
	curs_set(1);	
    noecho();
    cbreak ();
    printw("%s",prompt);
    while(!exit){
        
        if(tecla=getch()){
            
            switch(tecla){
                case 27: exit=1; break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);
                     
                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }
                     
                     deleteChar(input,count-1);
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     count--;
                    }
                    break;
                case 10:// Enter
                    bzero(last_input,MAX_INPUT);
                    strcpy(last_input,input);                    
                    bzero(input,MAX_INPUT);
                    
                    clear();
                    printw("%s",prompt);
                    count=0;
                    break;
                case KEY_UP:
                        while(count){
                        input[--count]='\0';                        
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }
                        printw("%s",last_input);
                        count=strlen(last_input);
                        strcpy(input,last_input);
                        
                    break;
                case KEY_DOWN:
                    while(count){
                        input[--count]='\0';                        
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                    }
                    break;
                
                case KEY_F(1):
                case KEY_F(2):
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);
                     
                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }
                     
                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;
                
                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);
                     
                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }
                     
                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    break;
            }
        }
            
    }
    
    endwin();*/
    return 0;
}

int Consola::Init(){
    initscr();
    keypad(stdscr, TRUE);
    scrollok(stdscr,TRUE);
    scroll(stdscr);
    start_color();
	curs_set(1);	
    noecho();
    cbreak ();
    printw("%s",_prompt);
    return 1;
}
int Consola::Exit(){
    endwin();
    return 0;
}
int Consola::Clear(){
    clear();
}
int Consola::Printf(char* fmt, ...){
    
    char *p;
    int i;
    unsigned u;
    char *s;
    va_list argp;
    va_start(argp, fmt);
    p=fmt;
    for(p=fmt; *p!='\0';p++)
    {
        if(*p!='%'){
        addch(*p);continue;}
        
        p++;
        switch(*p)
        {
            case 'c' : i=va_arg(argp,int);addch(i);break;
            case 'd' : i=va_arg(argp,int);
                        if(i<0){i=-i;addch('-');}printw("%s",convert(i,10));break;
            case 'o': i=va_arg(argp,unsigned int); printw("%s",convert(i,8));break;
            case 's': s=va_arg(argp,char *); printw(s); break;
            case 'u': u=va_arg(argp, unsigned int); printw("%s",convert(u,10));break;
            case 'x': u=va_arg(argp, unsigned int); printw("%s",convert(u,16));break;
            case '%': addch('%');break;
        }
    }
    va_end(argp);
}
char* Consola::convert(unsigned int num, int base){
    static char buff[33];
    char *ptr;
    ptr=&buff[sizeof(buff)-1];
    *ptr='\0';
    do
    {
    *--ptr="0123456789abcdef"[num%base];
    num/=base;
    }while(num!=0);
    return(ptr);
}
int Consola::Getch(){
    return getch();
}

long long Consola::ReadNumber(){

    int exit=0;
    int tecla;
    int count=0;
    int minus=0;
    int ok;
    bzero(input,MAX_INPUT);
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            
            if((tecla>='0' && tecla<='9'))
                ok=1;
            
           
            if(tecla=='-' && !minus && !count)
            {
                minus=1;
                ok=1;
            }
            
            switch(tecla){
                case 10:// Enter
                    printw("\n");
                    return atoll(input);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     if(deleteChar(input,--count)=='-')
                         minus=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}
float Consola::ReadDecimal(){
    int exit=0;
    int tecla;
    int count=0;    
    int ok;
    
    int minus=0;
    int point=0;
    
    bzero(input,MAX_INPUT);
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            
            if((tecla>='0' && tecla<='9'))
                ok=1;
            
           
            if(tecla=='-' && !minus && !count)
            {
                minus=1;
                ok=1;
            }
            if(tecla=='.' && !point)
            {
                point=1;
                ok=1;
            }
            
            switch(tecla){  
                case 10:// Enter
                    printw("\n");
                    return atof(input);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     char deleted=deleteChar(input,--count);
                     if(deleted=='-')
                         minus=0;
                     if(deleted=='.')
                         point=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}
char Consola::ReadChar(){

    int tecla;
    int count=0;
    int ret=0;
    while(tecla=getch()){
        
        if(isprint(tecla) && !count)
        {
            addch(tecla);
            count=1;
            ret=tecla;
        }
        else
            if(tecla==KEY_BACKSPACE && count){
                move(getcury(stdscr),getcurx(stdscr)-1);
                delch();
                count=0;
                ret=0;
            }
            else if(tecla==10){
                printw("\n");
                return ret;
            }
                
    }
    printw("\n");
    return 0;
    
}
int Consola::ReadLine(char* string){
    
    int exit=0;
    int tecla;
    int count=0;
    int minus=0;
    int ok;
    bzero(input,MAX_INPUT);
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            if(isprint(tecla))
                ok=1;            
            
            switch(tecla){
                case 10:// Enter
                    deleteSpaces(input);
                    strcpy((char*)string,input);
                     int aux;
                     aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);
                     printw("\n");
                    return strlen(string);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     if(deleteChar(input,--count)=='-')
                         minus=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}

long long Consola::ReadNumberFrom(long long n){
    int exit=0;
    int tecla;
    int count=0;
    int minus=0;
    int ok;
    bzero(input,MAX_INPUT);
    sprintf(input,"%lld",n);
    if(n<0)
        minus=1;
    count=strlen(input);
    printw("%s",input);
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            
            if((tecla>='0' && tecla<='9'))
                ok=1;
            
           
            if(tecla=='-' && !minus && !count)
            {
                minus=1;
                ok=1;
            }
            
            switch(tecla){
                case 10:// Enter
                    printw("\n");
                    return atoll(input);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     if(deleteChar(input,--count)=='-')
                         minus=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}
float Consola::ReadDecimalFrom(float f){
    
    int exit=0;
    int tecla;
    int count=0;    
    int ok;
    
    int minus=0;
    int point=0;
    
    bzero(input,MAX_INPUT);
    
    sprintf(input,"%f",f);
    if(f<0.0)
        minus=1;
    
    float aux=f-(int)f;
    
    if(aux>0)
        point=1;
    count=strlen(input);
    printw("%s",input);
    
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            
            if((tecla>='0' && tecla<='9'))
                ok=1;
            
           
            if(tecla=='-' && !minus && !count)
            {
                minus=1;
                ok=1;
            }
            if(tecla=='.' && !point)
            {
                point=1;
                ok=1;
            }
            
            switch(tecla){  
                case 10:// Enter
                    printw("\n");
                    return atof(input);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     char deleted=deleteChar(input,--count);
                     if(deleted=='-')
                         minus=0;
                     if(deleted=='.')
                         point=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}
char Consola::ReadCharFrom(char c){
    int tecla;
    int count=1;
    int ret=c;
    printw("%c",c);
    while(tecla=getch()){
        
        if(isprint(tecla) && !count)
        {
            addch(tecla);
            count=1;
            ret=tecla;
        }
        else
            if(tecla==KEY_BACKSPACE && count){
                move(getcury(stdscr),getcurx(stdscr)-1);
                delch();
                count=0;
                ret=0;
            }
            else if(tecla==10){
                printw("\n");
                return ret;
            }
                
    }
    printw("\n");
    return 0;
}
int  Consola::ReadLineFrom(char* string){
    
    int exit=0;
    int tecla;
    int count=0;
    int minus=0;
    int ok;
    bzero(input,MAX_INPUT);
    sprintf(input,"%s",string);
    count=strlen(input);
    printw("%s",input);
    
    while(!exit){
        
        if(tecla=getch()){     
            ok=0;
            if(isprint(tecla))
                ok=1;            
            
            switch(tecla){
                case 10:// Enter
                    deleteSpaces(input);
                    strcpy((char*)string,input);
                     int aux;
                     aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);
                     printw("\n");
                    return strlen(string);
                    break;
                case KEY_BACKSPACE:
                    if(count){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     if(deleteChar(input,--count)=='-')
                         minus=0;
                     printw("%s",input); 
                     move(getcury(stdscr),posant-1);
                     
                    }
                    break;
                case 330:// suprimir
                    if(count<strlen(input)){
                     int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        delch();
                        }

                     deleteChar(input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant);
                    }
                    break;
                case KEY_LEFT:
                    if(count){                               
                     move(getcury(stdscr),getcurx(stdscr)-1);
                     count--;
                    }
                    break;

                case KEY_RIGHT:
                    if(count<strlen(input)){
                        count++;
                        move(getcury(stdscr),getcurx(stdscr)+1);
                    }
                    break;
                default: 
                    if(ok){
                    int posant=getcurx(stdscr);
                     int aux=count;
                     while(aux++<strlen(input))
                     move(getcury(stdscr),getcurx(stdscr)+1);

                     aux=strlen(input);
                     while(aux--){                       
                        move(getcury(stdscr),getcurx(stdscr)-1);
                        }

                     appendChar(tecla,input,count);
                     printw("%s",input);           
                     move(getcury(stdscr),posant+1);
                     count++;
                    }
                    break;
            }
            
        }
    }
    printw("\n");
    return 0;
}

void Consola::SetPrompt(char* prompt){
    strcpy(_prompt,prompt);
}
void SetBkgrColor(){
    
    
}
void Consola::SetTextColor(){}
int Consola::GetX(){
    return getcurx(stdscr);
}
int Consola::GetY(){
    return getcury(stdscr);
}
void Consola::GotoXY(int x, int y){
    move(x,y);
}


void Consola::appendChar(char c,char* string, int pos){
    
    int i=MAX_INPUT-1;
    while(i>=pos){
        
        string[i]=string[i-1];
        i--;
    }
       string[pos]=c;
     

}
char Consola::deleteChar(char* string, int pos){
    
    int i=pos;
    char ret=string[pos];
    while(i<MAX_INPUT-1){        
        string[i]=string[i+1];
        i++;
    }
    return ret;

}
void Consola::deleteSpaces(char* string){
    
    int tam=strlen(string);
    
    //elimina espacios al final
    for (int i = tam - 1; i >= 0 && string[i] == ' '; i--) 
     string[i] = '\0'; 
    
   //elimina espacios al principio
     while(string[0]==' ')
         for(int j=0;j<tam;j++)
             string[j]=string[j+1];
}
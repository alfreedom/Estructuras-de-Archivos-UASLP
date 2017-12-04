/* 
 * File:   consola.h
 * Author: alfredo
 *
 * Created on 10 de abril de 2014, 09:04 PM
 */

#ifndef CONSOLA_H
#define	CONSOLA_H


#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#define MAX_INPUT 500

class Consola {
public:
    Consola();
    Consola(const Consola& orig);
    virtual ~Consola();
    
    int Run();
    int Init();
    int Exit();
    
    int Clear();
    int Printf(char* fmt, ...);
    int Getch();
    long long ReadNumber();
    float ReadDecimal();
    char ReadChar();
    int  ReadLine(char* string);
    
    long long ReadNumberFrom(long long n);
    float ReadDecimalFrom(float f);
    char ReadCharFrom(char c);
    int  ReadLineFrom(char* string);
    
    void SetPrompt(char* prompt);
    void SetBkgrColor();
    void SetTextColor();
    int GetX();
    int GetY();
    void GotoXY(int x, int y);
    
    
private:
    void appendChar(char c,char* string, int pos);
    char deleteChar(char* string, int pos);
    void eliminaEspacios(char* string);
    
    char* convert(unsigned int num, int base);
    void deleteSpaces(char* string);
    int ptrin;
    char input[MAX_INPUT];
    char last_input[MAX_INPUT];
    
    char _prompt[MAX_INPUT];
    

};

#endif	/* CONSOLA_H */


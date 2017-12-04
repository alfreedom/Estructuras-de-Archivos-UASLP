/* 
 * File:   error.h
 * Author: alfredo
 *
 * Created on 21 de abril de 2014, 01:43 PM
 */

#ifndef ERROR_H
#define	ERROR_H

#define NO_ERROR                0x0000
#define ERR_DICNOTFOUND         0x0002
#define ERR_ENTNOTFOUND         0x0004
#define ERR_KEYNOTFOUND         0x0008
#define ERR_INPUTEMPTY          0x0010
#define ERR_REGNOTFOUND         0x0020
#define ERR_REGEXIST            0x0040
#define ERR_NUMERROR            0x0080
#define ERR_DECIMALERROR        0x0100
#define ERR_BADCOMAND           0x0200
#define ERR_PARAMEMPTY          0x0400
#define ERR_DICNOTSELECT        0x0800
#define ERR_KEYEMPTY            0x1000
#define ERR_NOTATR              0x2000
#define ERR_ATRNOTFOUND         0x4000
#define CANCEL                  0x8000

static int _error_;



#endif	/* ERROR_H */


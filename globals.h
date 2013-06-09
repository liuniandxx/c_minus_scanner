/**********************************************/
/* File: globals.h                            */
/* Globals types and vars for minus compiler  */
/* must come before other include files       */
/*  Yang Jiangbin                             */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif 

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved of reserved words */
#define MAXRESERVED 6


typedef enum {
  /* book-keeping tokens */
  ENDFILE, ERROR,
  /* reserved words */
  ELSE, IF, INT, RETURN, VOID, WHILE,
  /* multicharacter tokens */
  ID, NUM,COMMENT,
  /* sepcial symbols */
  PLUS, MINUS, TIMES, OVER, LITTLE, LE, GREAT, GE, EQUAL, NE,ASSIGN, SEMI, COMMA,
  LLPAREN, LRPAREN, MLPAREN, MRPAREN, GLPAREN, GRPAREN,
} TokenType;

extern FILE* source;
extern FILE* listing;

extern int lineno;

extern int EchoSource;
extern int TraceScan;

#endif

/*********************************************/
/* File: util.c                              */
/* Utility function implementation           */
/* for c-minus compiler                      */
/* Yang Jiangbin                             */

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file 
 */

void printToken(TokenType token, const char* tokenString) 
{
  switch(token)
  {
  case ELSE:
  case IF:
  case INT:
  case RETURN:
  case VOID:
  case WHILE:
    fprintf(listing, "reserved word: %s\n",tokenString);
    break;
  case PLUS: fprintf(listing, "+\n"); break;
  case MINUS: fprintf(listing, "-\n"); break;
  case TIMES: fprintf(listing, "*\n"); break;
  case OVER: fprintf(listing, "/\n"); break;
  case LITTLE: fprintf(listing, "<\n"); break;
  case LE: fprintf(listing, "<=\n"); break;
  case GREAT: fprintf(listing, ">\n"); break;
  case GE: fprintf(listing, ">=\n"); break;
  case EQUAL: fprintf(listing, "==\n"); break;
  case NE: fprintf(listing, "!=\n"); break;
  case ASSIGN: fprintf(listing, "=\n"); break;
  case SEMI: fprintf(listing, ";\n"); break;
  case COMMA: fprintf(listing, ",\n"); break;
  case LLPAREN: fprintf(listing, "(\n"); break;
  case LRPAREN: fprintf(listing, ")\n"); break;
  case MLPAREN: fprintf(listing, "[\n"); break;
  case MRPAREN: fprintf(listing, "]\n"); break;
  case GLPAREN: fprintf(listing, "{\n"); break;
  case GRPAREN: fprintf(listing, "}\n"); break;
  case NUM: 
    fprintf(listing, "NUM, val = %s\n", tokenString);
    break;
  case ID:
    fprintf(listing, "ID, name = %s\n", tokenString);
    break;
  case ERROR:
    fprintf(listing, "ERROR, %s\n", tokenString);
    break;
  default:
    fprintf(listing, "Unknown token: %d\n", token);
  }
}

/* Funtion copyString allocates and make a new 
 * copy of an existing string
 */
char* copyString(char *s)
{
  char *t;
  int n;
  if(s == NULL) 
    return NULL;
  
  n = strlen(s);
  t = (char *)malloc(n + 1);
  if(t == NULL) 
    fprintf(listing, "out of memory error at line %d\n", lineno);
  else
    strcpy(t, s);
  return t;
}

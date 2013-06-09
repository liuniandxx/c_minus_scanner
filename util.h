/************************************************/
/* File: util.h                                 */
/* Utility functions for c-miuns compliler      */
/* Yang Jiangbin                                */

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedure printToken prints a token
 * and its lexeme to the listing file 
 */
void printToken(TokenType , const char *);

/* Function copyString allocates and makes a new 
 * copy of an existing string
 */
char * copyString(char *);

#endif

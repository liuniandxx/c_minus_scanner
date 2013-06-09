/*************************************/
/* File: main.c                      */
/* Main program for C-minus compiler */
/* Yang JiangBin                     */

#include "globals.h"

//#define NO_PARSE TRUE

#include "util.h"

//#if NO_PARSE 
#include "scan.h"
//#endif 

int lineno = 0;
FILE * source;
FILE * listing;

int EchoSource = TRUE;
int TraceScan = TRUE;

int main(int argc, char *argv[]) {
  char pgm[20];
  if(argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  
  strcpy(pgm, argv[1]);
  source = fopen(pgm, "r");
  if(source == NULL) 
  {
    fprintf(stderr, "File %s not found\n", pgm);
    exit(1);
  }
  
  listing = stdout;
  fprintf(listing, "\nC-MINUS COMPILATION: %s\n", pgm);
  
  //#if NO_PARSE
  while(getToken() != ENDFILE);
  //#endif
  return 0;
  
}

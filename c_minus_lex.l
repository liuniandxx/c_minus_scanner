/*****************************************/
/* File: c_minus_lex.l                   */
/* lex specification for c-minus         */
/* Yang Jiangbin                         */

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN + 1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"else"    {return ELSE;}
"if"      {return IF;}
"int"     {return INT;}
"return"  {return RETURN;}
"void"    {return VOID;}
"while"   {return WHILE;}
"+"       {return PLUS;}
"-"       {return MINUS;}
"*"       {return TIMES;}
"/"       {return OVER;}
"<"       {return LITTLE;}
"<="      {return LE;}
">"       {return GREAT;}
">="      {return GE;}
"=="      {return EQUAL;}
"!="      {return NE;}
"="       {return ASSIGN;}
";"       {return SEMI;}
","       {return COMMA;}
"("       {return LLPAREN;}
")"       {return LRPAREN;}
"["       {return MLPAREN;}
"]"       {return MRPAREN;}
"{"       {return GLPAREN;}
"}"       {return GRPAREN;}
{number}  {return NUM;}
{identifier}  {return ID;}
{newline} {lineno++;}
{whitespace} { /* skip whitespace */}
"/*"      { char c;
            char t;
            do {
                 c = input();
                 if(c == '\n')
                   lineno++;
                 if(c == '*')
                 {
                   t = input();
                   if(t == '/')
                     return COMMENT;
                   else 
                    unput(t);
                 } 
               }while(1);
          }

%%
TokenType getToken(void) 
{
  TokenType currentToken;
  lineno = 1;
  yyin = source;
  yyout = listing;
  currentToken = yylex();
  strncpy(tokenString, yytext, MAXTOKENLEN);
  
  if(TraceScan)
  {
    fprintf(listing, "\t%d: ", lineno);
    printToken(currentToken, tokenString);
  }
  return currentToken;
} 

int yywrap()
{
 return 1;
}

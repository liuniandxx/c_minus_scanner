/*******************************************/
/* File: scan.h                            */
/* The scanner implementation              */
/* for c-minus compiler                    */
/* Yang Jiangbin                           */

#include "globals.h"
#include "util.h"
#include "scan.h"

/* state in scanner DFA */
typedef enum {
  START, INNUM, INID, INSCOMMENT, INCOMMENT, INECOMMENT, INASSIGN, INLE, INGE,
  INNE, DONE
}StateType;

/* lexeme if identifier or reserved word */
char tokenString[MAXTOKENLEN + 1];

/* BUFLEN = length of the input buffer for 
 * source code lines 
 */
#define BUFLEN 256

static char lineBuf[BUFLEN]; // hold the current line
static int linepos = 0;      // current pos in lineBuf
static int bufsize = 0;      // current size of the lineBuf is 

/* getNextChar in the lineBuf */
static char getNextChar(void)
{
	if(!(linepos < bufsize))
	{
		lineno++;
		if(fgets(lineBuf,BUFLEN - 1,source))
		{
			if (EchoSource)
			{
				fprintf(listing,"%4d: %s\n",lineno,lineBuf);
			}
			bufsize = strlen(lineBuf);
			linepos = 0;
			return lineBuf[linepos++];
		}
		else
			return EOF;
	}
	else
	{
		return lineBuf[linepos++];
	}
}

/* ungetNextChar backtracks one characrer in lineBuf */
static void ungetNextChar(void)
{
	linepos--;
}

/* lookup table of reserved words */
static struct
{
	char * str;
	TokenType tok;
}reservedWords[MAXRESERVED] =
{
	{"else",ELSE},{"if",IF},{"int",INT},
	{"return",RETURN},{"void",VOID},{"while",WHILE}
};

/* lookup an identifier to see if it is reserved word */
/* use linear search */
static TokenType reservedLookup(char *s)
{
  int i;
  for(i = 0; i < MAXRESERVED; i++)
  {
    if(!strcmp(s, reservedWords[i].str))
      return reservedWords[i].tok;
  }
  return ID;
}

/***************************************/
/* The primary function of the scanner */
/***************************************/

/* function getToken returns the next   
 * token in the source file 
 */

TokenType getToken(void) 
{
  int tokenStringIndex = 0;
  TokenType currentToken;
  StateType state = START;
  int save;
  
  while(state != DONE)
  {
    char c = getNextChar();
    save = TRUE;
    switch(state)
    {
    case START:
      if(isdigit(c))
      {
	state = INNUM;
      }
      else if(isalpha(c))
      {
	state = INID;
      }
      else if(c == '/')
      {
	state = INSCOMMENT;
      }
      else if(c == '<')
      {
	state  = INLE;
      }
      else if(c == '>')
      {
       state = INGE;
      }
      else if(c == '=')
      {
       state = INASSIGN;
      }
      else if(c == '!')
      {
	state = INNE;
      }
      else if((c == ' ') || (c == '\t') || (c == '\n'))
      {
        save = FALSE;
      }
      else
      {
	state  = DONE;
	switch(c)
	{
	case EOF:
	  currentToken = ENDFILE;
	  break;
	case '+':
	  currentToken = PLUS;
	  break;
	case '-':
	  currentToken = MINUS;
	  break;
        case '*':
	  currentToken = TIMES;
	  break;
	case ';':
	  currentToken = SEMI;
	  break;
	case ',':
	  currentToken = COMMA;
	  break;
	case '(':
	  currentToken = LLPAREN;
	  break;
	case ')':
	  currentToken = LRPAREN;
	  break;
	case '[':
	  currentToken = MLPAREN;
	  break;
	case ']':
	  currentToken = MRPAREN;
	  break;
	case '{':
	  currentToken = GLPAREN;
	  break;
	case '}':
	  currentToken = GRPAREN;
	  break;
	default:
	  currentToken = ERROR;
	  break;
	}
      }
      break;
    case INSCOMMENT:
      if(c == '*')
      {
	state = INCOMMENT;
      }
      else
      {
	save = FALSE;
	state = DONE;
	currentToken = OVER;
	ungetNextChar();
      }
      break;
    case INCOMMENT:
      save = FALSE;
      if(c == '*')
      {
	state = INECOMMENT;
      }
      break;
    case INECOMMENT:
      if(c == '/')
      {
	state =DONE;
	currentToken = COMMENT;
      }
      else
      {
	state = INCOMMENT;
      }
      break;
    case INLE:
      if(c == '=')
      {
	save = FALSE;
	state = DONE;
	currentToken = LE;
      }
      else
      {
	ungetNextChar();
	save = FALSE;
	state = DONE;
	currentToken = LITTLE;
      }
      break;
    case INGE:
      if(c == '=')
      {
	save = FALSE;
	state = DONE;
	currentToken = GE;
      }
      else
      {
	ungetNextChar();
	save = FALSE;
	state = DONE;
	currentToken = GREAT;
      }
      break;
    case INASSIGN:
      if(c == '=')
      {
	save = FALSE;
	state = DONE;
	currentToken = EQUAL;
      }
      else
      {
	ungetNextChar();
	save = FALSE;
	state = DONE;
	currentToken = ASSIGN;
      }
      break;
    case INNE:
      if(c == '=')
      {
	save = FALSE;
	state = DONE;
	currentToken = NE;
      }
      else
      {
	ungetNextChar();
	save = FALSE;
	currentToken =  ERROR;
      }
      break;
    case INNUM:
      if(!isdigit(c))
      {
	ungetNextChar();
	save = FALSE;
	state = DONE;
	currentToken = NUM;
      }
      break;
    case INID:
      if(!isalpha(c))
      {
	ungetNextChar();
	save = FALSE;
	state = DONE;
	currentToken = ID;
      }
      break;
    case DONE:
      fprintf(listing,"Scanner Bug:state = %d\n",state);
      state = DONE;
      currentToken = ERROR;
      break;
    }
    if((save) && tokenStringIndex <= MAXTOKENLEN)
      tokenString[tokenStringIndex++] = c;
    if(state == DONE)
    {
      tokenString[tokenStringIndex] = '\0';
      if(currentToken == ID)
      {
	currentToken = reservedLookup(tokenString);
      }
    }
  }

  if(TraceScan)
  {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}



/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void expr(void);
void term(void);
void factor(void);
void error(void);
/* Character classes */
#define LETTER 0 //[a-zA-Z]
#define DIGIT 1 //[0-9]
#define SINGLEQUOTE 2 //[\']
#define DOUBLEQUOTE 3 //[\"]
#define DECIMAL 4 //[\.]
#define UNKNOWN 99 //[^a-zA-Z0-9]

/* Token codes */
#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DECIMAL_POINT 27
#define SEMICOLON 28
#define MODULO 29
#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37




/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
    //expr();
	 } while (nextToken != EOF);

    expr();
	 }
	 return 0;
}


/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '.':
			 addChar();
			 nextToken = DECIMAL_POINT;
			 break;
     case ';':
       addChar();
       nextToken = SEMICOLON;
       break;
     case '%':
       addChar();
       nextToken = MODULO;
       break;
     default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
        while (charClass == LETTER || charClass == DIGIT) {
         addChar();
         getChar();
        }
        if (strcmp(lexeme, "for") == 0) {
          nextToken = FOR_CODE;
         }
        else if(strcmp(lexeme ,"if") == 0) {
          nextToken = IF_CODE;
        }
        else if(strcmp(lexeme ,"else") == 0) {
          nextToken = ELSE_CODE;
        }
        else if(strcmp(lexeme ,"while") == 0) {
          nextToken = WHILE_CODE;
        }
        else if(strcmp(lexeme ,"do") == 0) {
          nextToken = DO_CODE;
        }
        else if(strcmp(lexeme ,"int") == 0) {
          nextToken = INT_CODE;
        }
        else if(strcmp(lexeme, "float") == 0) {
          nextToken = FLOAT_CODE;
        }
        else if(strcmp(lexeme ,"switch") == 0) {
          nextToken = SWITCH_CODE;
        }
        else {
          nextToken = IDENT;
        }

			 break;
		/* Integer & Float literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
       nextToken = INT_LIT;
       if (nextChar == 'u' || nextChar == 'U' || nextChar == 'l' || nextChar == 'L') {
         addChar();
         getChar();

         if(nextChar == 'l' || nextChar == 'L') {
           addChar();
           getChar();

         }
         nextToken = INT_LIT;
       }
       if (nextChar == 'e' || nextChar == 'E') {
         addChar();
         getChar();

         if (nextChar == '-') {
           addChar();
           getChar();
           while (charClass == DIGIT) {
             addChar();
             getChar();
           }
         }
         nextToken = FLOAT_LIT;
       }

       if (charClass == UNKNOWN && nextChar == '.'){
         addChar();
				 getChar();
         while (charClass == DIGIT) {
				  addChar();
				  getChar();
			   }
         if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();

          }
         }
          if (nextChar == '-') {
            addChar();
            getChar();
            while (charClass == DIGIT) {
              addChar();
              getChar();
            }
          }
         nextToken = FLOAT_LIT;
       }

		 	break;
    case DECIMAL:
          addChar();
				  getChar();
          if (charClass == DIGIT){
            addChar();
				    getChar();
            while (charClass == DIGIT) {
				      addChar();
				      getChar();
			      }
            nextToken = FLOAT_LIT;
          }
          else {
              nextToken = DECIMAL_POINT;
          }
     break;
		/* Parentheses and operators */
		 case UNKNOWN:
      if (nextChar == '-') {
        addChar();
        getChar();
        if (charClass == DIGIT) {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();
          }
          if (charClass == UNKNOWN && nextChar == '.'){
            addChar();
				    getChar();
            while (charClass == DIGIT) {
				    addChar();
				    getChar();
			      }
            if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
              addChar();
              getChar();
              while (charClass == DIGIT) {
                addChar();
                getChar();
              }
              if (nextChar == '-') {
                addChar();
                getChar();
                while (charClass == DIGIT) {
                  addChar();
                  getChar();
                }
              }
            }
          }
        } else {
          nextToken = SUB_OP;
        }
      }
      else if (nextChar == '.') {
        addChar();
        getChar();
        if (charClass == DIGIT) {
        addChar();
        getChar();
        while (charClass == DIGIT) {
          addChar();
          getChar();
        }
        if (nextChar == 'e' || nextChar == 'E' || nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L') {
          addChar();
          getChar();
          while (charClass == DIGIT) {
            addChar();
            getChar();
          }
          if (nextChar == '-') {
            addChar();
            getChar();
          }
        }
        nextToken = FLOAT_LIT;
        }
        else {
          nextToken = DECIMAL_POINT;
        }
      }
      else {
			    lookup(nextChar);
			    getChar();
      }

			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */



void expr(void) {
   printf("Enter <expr>\n");
   /*Parse the first term */
	 term();
   /* As long as the next token is + or -, get
	 the next token and parse the next term */
	 while (nextToken == ADD_OP || nextToken == SUB_OP) {
		 lex();
		 term();
	 }
   printf("Exit <expr>\n");
}

/* term
 Parses strings in the language generated by the rule:
 <term> -> <factor> {(* | /) <factor>}
 */
void term(void) {
   printf("Enter <term>\n");
   /* Parse the first factor */
	 factor();
   /* As long as the next token is *, /, or % get the
	 next token and parse the next factor */
	 while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MODULO) {
		 lex();
		 factor();
	 }
   printf("Exit <term>\n");
}

/* factor
 Parses strings in the language generated by the rule:
 <factor> -> id | int_constant | ( <expr> )
 */
void factor(void) {
     printf("Enter <factor>\n");
     /* Determine which RHS */
	 if (nextToken == IDENT || nextToken == INT_LIT || nextToken == FLOAT_LIT)
     /* Get the next token */
		 lex();
     /* If the RHS is ( <expr> ), call lex to pass over the
		 left parenthesis, call expr, and check for the right
		 parenthesis */
	 else { if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN)
		 	lex();
		 else
		 	error();
		 }
     /* It was not an id, an integer literal, or a left
		 parenthesis */
		 else
		 error();
	 }
	 printf("Exit <factor>\n");
}
void error(void){
 exit(1);
}

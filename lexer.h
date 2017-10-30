/*
==========================================
Librerias utilizadas
==========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
==========================================
CONSTANTES PARA COLOREAR IMPRESION
==========================================
*/

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
/*
==========================================
Prototipado de las funciones definidas
==========================================
*/

typedef char* string;

int classifierTable(char);
void lexer(string);
int reserverdWord(string);
string concatenate(string, char);
string tokenType(int);
void printBorders(FILE *, int);




enum TRANSITIONS
{
    REJECT = 0,
    INITIAL = 1,
    WORD,
    DIGITS,
    SPACE = 37,

};

int transition_table[][26] ={
    {    1,	31,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	16,	0,	18,	19,	20,	21,	21,	38,	37,38},
    {    1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	22,	0 ,0},
    {    0,	0,	23,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	24,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	25,	25,	0,	0,	25,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	26,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	27,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    14,14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	28,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14 ,14},
    {    0,	0,	26,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    30,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	33,	30,	30,	30,	30,	30,	30,	30,	30,	30 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    30,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30 ,30},
    {    0,	31,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0 ,0},
    {    30,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	34,	30,	30,	30,	30,	30,	30,	30,	30 ,30},
    {    35,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30 ,30},
    {    35,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	36,	30,	30,	30,	30,	30,	30,	30,	30 ,30},
    {    35,30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30 ,30},
    {    0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0  ,0},
    {    38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	0,38}
    };
    

//lista de palabras reservadas

char reseverd_words[][6] = {
    {"read"},
    {"echo"},
    {"if"},
    {"then"},
    {"elif"},
    {"else"},
    {"fi"}, 
    {"case"}, 
    {"in"}, 
    {"while"}, 
    {"do"}, 
    {"done"}, 
    {"for"} 
    };
    


typedef struct stack{
    int data;
    struct stack *link;

} S;

void lexerAnalyzer(string expression, int numberLine, FILE * errorsFile, FILE *tokensFile){

    S temp;
    int column = REJECT;
    int currentState = REJECT;
    char currentChar;
    int prevState = INITIAL;
    char lexeme[1024];
    int i = 0;
    int sizeLine = strlen(expression)-1; // especifica el tamaño maximo de la linea que se lee
    int charPosition = 0;
    
    while(charPosition < sizeLine)
    {
        //lee caracter por caracter hasta llegar a la final de la linea
        //La variable currentChar 
        currentChar = expression[charPosition];

        //actualiza el numero de columna que se va analizar en la tabla dependiendo simbolo que se evalua
        //la lista de simbolo va de 0 hasta el 25 
        //Si tiene mas duda sobre los valores que tiene que retornar dependiendo el caracter revise la tabla de apoyo
        column = classifierTable(currentChar);
        
        //actualiza el estado que mapea la tabla apartir de currentState y column
        currentState = transition_table[currentState][column];

        
        if(currentState == REJECT && prevState != SPACE)
        {   
            
           
            lexeme[i] = '\0';
            // Los tokens reconocidos se imprimiran en un archivo llamado output
            // fprintf(output,"%d  %s  %s\n",lexeme )

            // Para simplificar el catcheo de palabras reservadas, en el automata las tomo como indenticador
            // y aqui verifico si este pertenece al conjunto de las palabras reservadas haciendo un chequeo 
            // de las 13 palabras reservadas. Si la funcion serverdWord regresa un valor de 13 significa que no esta incluida
            
            if(prevState == 38)// Impresion en pantalla y en el archivo errorsFile
            {   
                
                printf(RED"  %-14d %-50s  %-10s\n"RESET,numberLine, lexeme,tokenType(prevState));
                fprintf(errorsFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));
               
            }
            
            else if(reserverdWord(lexeme) != 13 ) // Para identificar si el lexema es una palabra reservada
            { 
      
                fprintf(tokensFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(reserverdWord(lexeme)));
                printf("  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(reserverdWord(lexeme)));
            }
            else // Todos los demas simbolos
            {
                fprintf(tokensFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));
                printf("  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));

            }
            i=0;
            

            
        }
        else if(currentState != REJECT)
        {   
            // Esta condicional evita que se le concatene caracteres de espacio al Lexeme
            // Aunque hay casos en el que esto es necesario por ejemplo en comentarios o en strings
            // por esa razon se toma en cuenta cuando la variable currentState es 14 o 30 ya 
            // que son el estado de string y la de comentarios
            if(isspace(currentChar) == 0 || currentState == 14 || currentState == 30 )
                lexeme[i++] = currentChar;

            ++charPosition;

        }
        //actualiza el prevState anterior con la variable currentState
        prevState = currentState;


    }

    // Se vuelve a revisar si hay un lexema que no se haya procesado despues de la nueva linea
    if(currentState != SPACE && lexeme != NULL)
    {
        
        lexeme[i] = '\0';
       
        // Los tokens reconocidos se imprimiran en un archivo llamado output
        // fprintf(output,"%d  %s  %s\n",lexeme )
        if(prevState == 38)
        {   
            
            printf(RED"  %-14d %-50s  %-10s\n"RESET,numberLine, lexeme,tokenType(prevState));
            fprintf(errorsFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));
        }
        
        else if(reserverdWord(lexeme) != 13 )
        { 
  
            fprintf(tokensFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(reserverdWord(lexeme)));
            printf("  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(reserverdWord(lexeme)));
            
        }

        else
        {
            fprintf(tokensFile,"  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));
            printf("  %-14d %-50s  %-10s\n",numberLine, lexeme,tokenType(prevState));
        }
        i = 0;
    }

}

// esta funcion se encarga de regresar el numero de la columna al caracter que le corresponde
int classifierTable(char c){
    
    // retorna 0 si el char c es una letra
    if(isalpha(c)){
        return 0;
    }
    // retorna 1 si el char c es un digito
    else if(isdigit(c)){
        return 1;
    }
    else if(ispunct(c)){
        switch(c){

            case '=': return 2; break;
            case '<': return 3; break;
            case '>': return 4; break;
            case '$': return 5; break;
            case '(': return 6; break;
            
            case ')': return 7; break; 
            case '[': return 8; break;
            
            case ']': return 9; break; 
            case '{': return 10; break;
            
            case '}': return 11; break; 
            case '|': return 12; break; 
            case '&': return 13; break;
            case '"': return 14; break;            
            case '!': return 15; break;
            case '/': return 16; break;
            case '@': return 17; break;
            case '#': return 18; break;
           
            case ':': case ';':case ',':case '.': 
                      return 19;  break;
            
            case '`': return 20;  break;            
            case '*': return 21;  break;  
                      
            case '-': case '+': case '%': 
                      return 22;  break;
            case '_': return 23; break;
            
            default:
                return 25;
            

        }

    }

    else if(isspace(c))
        return 24;

    else
        return 25;
}

// Esta funcion sirve para indentificar si el token evaluado es un una palabra reservada
// Si se da el caso se regresara un valor de [0, 12] de lo contrario se regresa el valor 13
// strcmp regresa un valor igual a 0 si las cadenas comparadas son iguales
int reserverdWord(string word){
    
        int index = 0;
    
       
        while(strcmp(word, reseverd_words[index]) != 0  && index < 13){
            index++;
        }
    
        return index == 13 ? 13 : 39 + index ;
        
    }
    



// Devuelve el token del estado anterior
string tokenType(int state){

    switch(state){

        // seccion de errores
        case   0: 
        case   22: 
        case   38:
                return    "UNKNOWN_SIMBOLS       301";     break;

        case   13: 
        case   14: return "INAPPROPIATE_PATTERN  302";  break;

        // Otros simbolos que analizador debe de reconocer
        case   1: return  "IDENTIFIER            101"; break;
        case   2: return  "ASSIGNATION           102"; break;
        case   3: return  "LESS_THAN             103"; break;
        case   4: return  "GREATER_THAN          103"; break;
        case   5: return  "ACCESS_VAR            104"; break;
        case   6: return  "LEFT_PARENTHESIS      105"; break;
        case   7: return  "RIGHT_PARENTHESIS     106"; break;
        case   8: return  "lEFT_BRACKETS         107"; break; 
        case   9: return  "RIGHT_BRACKETS        108"; break;
        case   10: return "LEFTCURLY_BRACKETS    109"; break;
        case   11: return "RIGHTCURLY_BRACKETS   110"; break;
        case   12: return "PIPE                  111"; break;
        
        case   15: return "NEGATION              112"; break;
        case   16: return "ARITMETIC_OPERATOR    113"; break;
        case   17: return "POSITION_VARIABLE     117"; break;
        case   18: return "COMMENTS              114"; break;
        case   19: return "PUNCTUATION_MARK      115"; break;
        case   20: return "APOSTROPHE            116"; break;
        case   21: return "ARITMETHIC_OPERATOR   113"; break;
        case   23: return "EQUAL_SIGN            103"; break;
        case   24: return "EQUAL_LESS            103"; break;
        case   25: return "POSITION_VARIABLE     117"; break;
        case   26: return "OR_OPERATOR           118"; break;
        case   27: return "AND_OPERATOR          119"; break;
        case   28: return "STRING                121"; break;
        case   29: return "DIFFERENT             103"; break;
        case   30: return "COMMENTS              115"; break;
        case   31: return "DIGITS                120"; break;
        case   32: return "GREATER_EQUAL         103"; break;
        case   33: return "COMMENTS              115"; break;
        case   35: return "PATH_INTERPRETER      122"; break;
        case   36: return "COMMENTS              115"; break;
        // Seccion de palabras reservadas
        
        case   39: return "RESERVEDWORD_READ     401"; break;
        case   40: return "RESERVEDWORD_ECHO     402"; break;
        case   41: return "RESERVEDWORD_IF       403"; break;
        case   42: return "RESERVEDWORD_THEN     404"; break;
        case   43: return "RESERVEDWORD_ELIF     405"; break;
        case   44: return "RESERVEDWORD_ELSE     406"; break;
        case   45: return "RESERVEDWORD_FI       407"; break;
        case   46: return "RESERVEDWORD_CASE     408"; break;
        case   47: return "RESERVEDWORD_IN       409"; break;
        case   48: return "RESERVEDWORD_WHILE    410"; break;
        case   49: return "RESERVEDWORD_DO       411"; break;
        case   50: return "RESERVEDWORD_DONE     412"; break;
        case   51: return "RESERVEDWORD_FOR      413"; break;

    
    
    }

}

// Hice
void printBorders(FILE *fileInput, int flag){

    fprintf(fileInput,"##############################################################################################\n");
    fprintf(fileInput,"# %-14s %-50s  %-10s              #\n","Numberline" ,"Lexeme" ,flag ?"Tokens" :"TypeError");
    fprintf(fileInput,"##############################################################################################\n");


}
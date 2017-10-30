/*
==========================================
Author: Hendrik Martina

==========================================
*/

#include "lexer.h"


int main() {
    
    char line[1024];
    char input[10];
    // input es el archivo de entrada
    FILE *tokens = fopen("tokens.txt","w");
    FILE *errors = fopen("errors.txt","w");
    FILE *fp;

    printf(BLUE"Input the name of the file you wanna read\n$ "RESET);
    scanf("%s", input);
    fp = fopen(input,"r");
    if(fp == NULL)
    {
        printf(RED"File not found [press any botton to exit]...");
        getchar();
        getchar();
        exit(0);

    }
    
          
    puts(GREEN"##############################################################################################");
    printf("# %-14s %-50s  %-10s              #\n","Numberline" ,"Lexeme" ,"Token");
    puts("##############################################################################################"RESET);
    
    printBorders(tokens,1);
    printBorders(errors, 0);

    char * TEMP;
    int numberLine = 1;

    while( fgets(line,1024,fp) ) {
        lexerAnalyzer(line, numberLine, errors, tokens);
        numberLine++;
    
    }
    
    
    fclose(fp);
    fclose(tokens);
    fclose(errors);
    return 0;
}



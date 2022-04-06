#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
#define UNKNOWN_SYMBOL_ERR 0
enum DFA_STATES{q0,q1,q2,q3,q4,q5,q6};
int Current_state;

// DFA for IF
#define IF_TOTAL_STATES 4
#define IF_FINAL_STATES 1
#define IF_ALPHABET_CHARCTERS 2
enum IF_input{i,f};
int IF_Accepted_states[IF_FINAL_STATES]={q2};
char IF_alphabet[IF_ALPHABET_CHARCTERS]={'i','f'};
int IF_Transition_Table[IF_TOTAL_STATES][IF_ALPHABET_CHARCTERS];


// DFA for Identifiers
#define ID_TOTAL_STATES 3
#define ID_FINAL_STATES 1
#define ID_ALPHABET_CHARCTERS 2
enum ID_input{A,B};
int ID_Accepted_States[ID_FINAL_STATES]={q1};
char ID_alphabet[ID_ALPHABET_CHARCTERS]={'A','B'};
int ID_Transition_Table[ID_TOTAL_STATES][ID_ALPHABET_CHARCTERS];


// DFA for while
#define WHILE_TOTAL_STATES 7
#define WHILE_FINAL_STATES 1
#define WHILE_ALPHABET_CHARCTERS 5
//enum WHILE_input{w,h,I,l,e};
int WHILE_Accepted_states[WHILE_FINAL_STATES] = {q5};
char WHILE_alphabet[WHILE_ALPHABET_CHARCTERS]={'w', 'h', 'i', 'l', 'e'};
int WHILE_Transition_Table[WHILE_TOTAL_STATES][WHILE_ALPHABET_CHARCTERS];


// DFA for break
#define BREAK_TOTAL_STATES 7
#define BREAK_FINAL_STATES 1
#define BREAK_ALPHABET_CHARCTERS 5
int BREAK_Accepted_states[BREAK_FINAL_STATES] = {q5};
char BREAK_alphabet[BREAK_ALPHABET_CHARCTERS]={'b', 'r', 'e', 'a', 'k'};
int BREAK_Transition_Table[BREAK_TOTAL_STATES][BREAK_ALPHABET_CHARCTERS];

// DFA for curly brackets
#define CURLY_TOTAL_STATES 3
#define CURLY_FINAL_STATES 1
#define CURLY_ALPHABET_CHARCTERS 2
int CURLY_Accepted_states[CURLY_FINAL_STATES] = {q1};
char CURLY_alphabet[CURLY_ALPHABET_CHARCTERS]={'{', '}'};
int CURLY_Transition_Table[CURLY_TOTAL_STATES][CURLY_ALPHABET_CHARCTERS];

// DFA for arithmatic operators
#define MATH_TOTAL_STATES 3
#define MATH_FINAL_STATES 1
#define MATH_ALPHABET_CHARCTERS 4
int MATH_Accepted_states[MATH_FINAL_STATES] = {q1};
char MATH_alphabet[MATH_ALPHABET_CHARCTERS]={'+', '*', '/', '-'};
int MATH_Transition_Table[MATH_TOTAL_STATES][MATH_ALPHABET_CHARCTERS];

// DFA for print
#define PRINT_TOTAL_STATES 7
#define PRINT_FINAL_STATES 1
#define PRINT_ALPHABET_CHARCTERS 5
int PRINT_Accepted_states[PRINT_FINAL_STATES] = {q5};
char PRINT_alphabet[PRINT_ALPHABET_CHARCTERS]={'p', 'r', 'i', 'n', 't'};
int PRINT_Transition_Table[PRINT_TOTAL_STATES][PRINT_ALPHABET_CHARCTERS];

// DFA for accepting float values
#define FLOAT_TOTAL_STATES 5
#define FLOAT_FINAL_STATES 2
#define FLOAT_ALPHABET_CHARCTERS 2
int FLOAT_Accepted_states[FLOAT_FINAL_STATES] = {q2, q4};
char FLOAT_alphabet[FLOAT_ALPHABET_CHARCTERS]={'A', 'B'};
int FLOAT_Transition_Table[FLOAT_TOTAL_STATES][FLOAT_ALPHABET_CHARCTERS];

// DFA for comparison
#define COMP_TOTAL_STATES 7
#define COMP_FINAL_STATES 2
#define COMP_ALPHABET_CHARCTERS 6
enum compOp{g,a,n,e,o};
int COMP_Accepted_states[COMP_FINAL_STATES] = {q1, q2};
char COMP_alphabet[COMP_ALPHABET_CHARCTERS]={'g', 'a', 'n', 'e', 'o'};
int COMP_Transition_Table[COMP_TOTAL_STATES][COMP_ALPHABET_CHARCTERS];

// DFA for rounded brackets
#define ROUNDED_TOTAL_STATES 3
#define ROUNDED_FINAL_STATES 1
#define ROUNDED_ALPHABET_CHARCTERS 2
int ROUNDED_Accepted_states[ROUNDED_FINAL_STATES] = {q1};
char ROUNDED_alphabet[ROUNDED_ALPHABET_CHARCTERS]={'(', ')'};
int ROUNDED_Transition_Table[ROUNDED_TOTAL_STATES][ROUNDED_ALPHABET_CHARCTERS];

char recognizedIdentifers[1000][1000];
int recognizedIdentifersCount = 0;

//files
char tokenOutput[1000] = {'\0'};
int tokenOutputCount = 0;
char symbolTable[1000] = {'\0'};
int symbolTableCount = 0;
int lexemeCount = 1;

void lexemeToDFA(int, int, char *);
void DefineIfDFA();
void DefineIdDFA();
void DefineBreakDFA();
void DefineCurlyDFA();
void DefineMathDFA();
void DefinePrintDFA();
void DefineFloatDFA();
void DefineWhileDFA();
void DefineCompDFA();
void DefineRoundDFA();
int ifDFA(char current_symbol);
int idDFA(char current_symbol);
int breakDFA(char current_symbol);
int curlyDFA(char current_symbol);
int mathDFA(char current_symbol);
int printDFA(char current_symbol);
int floatDFA(char current_symbol);
int whileDFA(char current_symbol);
int compDFA(char current_symbol);
int roundedDFA(char current_symbol);
bool runDFA(char *lexeme,void(*TransTable)(),int(*DFA)(char));
void appendTokenOutput(char *lexeme);
void appendSymbolTable(char *lexeme, int value);

int main(){
    FILE* fptr;
    
    fptr = fopen("code.txt","r");
    if (fptr == NULL)
    {
        printf("Error! The file did not open!");
        exit(0);
    }

    char* buffer = (char*) malloc(sizeof(char)*1000);
    memset(buffer,'\0',1000);

    char lexeme[200] = {'\0'};
    int lexemeBegin = 0;  
    int forward = 0;
    char ch;
    int commentFlag = 0;

    while(!feof(fptr))
    {   
        ch = fgetc(fptr);
        if (commentFlag == 1 && (ch != '\n'|| ch == '\t')){
            continue;
        }

        if (ch == '>' || ch == '<' || ch == '=' || ch == '!' || ch =='|' || ch == '&' || ch == '/'){
            lexemeToDFA(lexemeBegin, forward, buffer);
            buffer[forward] = ch;
            lexemeBegin = forward;
            forward++;

            char prev = ch;
            ch = fgetc(fptr);


            if ((prev == '>' || prev == '<' || prev == '=' || prev == '!') && ch == '='){
                buffer[forward] = ch;
                forward++;
                lexemeToDFA(lexemeBegin, forward, buffer);

                lexemeBegin = forward;
                continue;
            }
            else if ((prev == '|') && ch == '|'){
                buffer[forward] = ch;
                forward++;
                lexemeToDFA(lexemeBegin, forward, buffer);

                lexemeBegin = forward;
                continue;
            }
            else if ((prev == '&') && ch == '&'){
                buffer[forward] = ch;
                forward++;
                lexemeToDFA(lexemeBegin, forward, buffer);

                lexemeBegin = forward;
                continue;
            }
            else if ((prev == '/') && ch == '/'){
                commentFlag = 1;
                //lexemeBegin--;
                forward--; 
                continue;
            }
            else {
                lexemeToDFA(lexemeBegin, forward, buffer);
                lexemeBegin++;
            }

        }
        if ( ch == ' ' || ch == '\t'){
            continue;
        }
        if (ch == '\n'){
            commentFlag = 0;
            lexemeToDFA(lexemeBegin, forward, buffer);
            lexemeBegin = forward + 1;
            forward++;
            continue; 
        }
        if (ch == '(' || ch == ')' || ch == '{' || ch== '}' || ch == '+' || ch == '-' || ch == '/' || ch == '*'){
            lexemeToDFA(lexemeBegin, forward, buffer);
            buffer[forward] = ch;
            lexemeBegin = forward;
            forward++;
            lexemeToDFA(lexemeBegin, forward, buffer);
            lexemeBegin++;
            continue;
        }

        buffer[forward] = ch;
        forward++;
        
    }
    fclose(fptr);

    FILE* fptr2;
    fptr2 = fopen("token.txt","w");
    int results = fputs(tokenOutput,fptr2);
    if( results == EOF ){
        printf("Failed to copy");
    }
    fclose(fptr2);

    FILE* fptr3;
    fptr3 = fopen("symboltable.txt","w");
    int resultsTwo = fputs(symbolTable,fptr3);
    if( resultsTwo == EOF ){
        printf("Failed to copy");
    }
    fclose(fptr3);
    return 0;
}

void lexemeToDFA(int starting, int ending, char *bufferArray){
    if (starting == ending ){
        return;
    }

    char lexeme[1000] = {'\0'};
    int count = 0;
    for (int i = starting; i < ending; i++){
        lexeme[count] = bufferArray[i];
        count++;
        
    }

    bool identifierResult = runDFA(lexeme, DefineIdDFA, idDFA);
    bool ifResult = runDFA(lexeme, DefineIfDFA, ifDFA);
    bool whileResult = runDFA(lexeme, DefineWhileDFA, whileDFA);
    bool breakResult = runDFA(lexeme, DefineBreakDFA, breakDFA);
    bool printResult = runDFA(lexeme, DefinePrintDFA, printDFA);
    bool floatResult = runDFA(lexeme, DefineFloatDFA, floatDFA);
    bool compResult = runDFA(lexeme, DefineCompDFA, compDFA);
    bool mathResult = runDFA(lexeme, DefineMathDFA, mathDFA);
    bool roundResult = runDFA(lexeme, DefineRoundDFA, roundedDFA);
    bool curlyResult = runDFA(lexeme, DefineCurlyDFA, curlyDFA);


    char output[1000] = {'\0'};
    if (ifResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:if\nTOKEN TYPE: KEYWORD\n");
        return;
    }
    if (whileResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:while\nTOKEN TYPE: KEYWORD\n");
        return;
    }
    if (breakResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:break\nTOKEN TYPE: KEYWORD\n");
        return;
    }
    if (printResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:print\nTOKEN TYPE: KEYWORD\n");
        return;
    }
    if (floatResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 1);
        printf("TOKEN:%s\nTOKEN TYPE: FLOAT\n",lexeme);
        return;
    }
    if (compResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:%s\nTOKEN TYPE: COMPARISON OP\n",lexeme);
        return;
    }
    if (mathResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:%s\nTOKEN TYPE: OP\n",lexeme);
        return;
    }
    if (roundResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:%s\nTOKEN TYPE: BRACKET\n",lexeme);
        return;
    }
    if (curlyResult == true){
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);
        printf("TOKEN:%s\nTOKEN TYPE: CURLY BRACKET\n",lexeme);
        return;
    }
       
    if(identifierResult == true){
        for (int i = 0; i < recognizedIdentifersCount; i ++){
            if (strcmp(recognizedIdentifers[i],lexeme) == 0){
                return;
            }
        }
        appendTokenOutput(lexeme);
        appendSymbolTable(lexeme, 0);

        strcpy(recognizedIdentifers[recognizedIdentifersCount],lexeme);
        recognizedIdentifersCount++;

        printf("TOKEN:%s\n",lexeme);
        printf("TOKEN TYPE: IDENTIFIER\n");
        return;
    }

    /*
    printf("identifierResult:");
    if (identifierResult == true){
        printf("true\n");
    } else {
        printf("false\n");
    }
    printf("ifResult:");
    if (ifResult == true){
        printf("true\n");
    } else {
        printf("false\n");
    }*/

}

void appendTokenOutput(char *lexeme){
    for(int i = 0; i < strlen(lexeme); i++){
        tokenOutput[tokenOutputCount] = lexeme[i];
        tokenOutputCount++;
    }
    tokenOutput[tokenOutputCount] = '\n';
    tokenOutputCount++;
}

void appendSymbolTable(char *lexeme, int value){
    if(symbolTableCount == 0){
        //Handles adding coloumn labels at the start
        char labels[16] = {'#','n','o','\t','T','o','k','e','n','\t','V','a','l','u','e','\n'};
        strcpy(symbolTable,labels);
        symbolTableCount = 16;
    }
    //Appends lexeme no
    char intArray[11];
    sprintf(intArray,"%ld", lexemeCount);
    for(int i = 0; i < strlen(intArray); i++){
        symbolTable[symbolTableCount] = intArray[i];
        symbolTableCount++;
    }
    lexemeCount++;
    symbolTable[symbolTableCount] = '.'; 
    symbolTableCount++;
    symbolTable[symbolTableCount] = '\t'; 
    symbolTableCount++;

    //Checks if it is a float 
    if(value == 1){
        //Handles adding float to the symbol table
        char floaty[11] = {'F','L','O','A','T','_','T','O','K','E','N'};
        for (int i = 0; i < strlen(floaty); i++){
            symbolTable[symbolTableCount] = floaty[i];
            symbolTableCount++;
        }
        symbolTable[symbolTableCount] = '\t';
        symbolTableCount++;
        for (int i = 0; i < strlen(lexeme); i++){
            symbolTable[symbolTableCount] = lexeme[i];
            symbolTableCount++;
        }
    }
    else{
        //Handles adding everthing else to the symbol table
        for (int i = 0; i < strlen(lexeme); i++){
            symbolTable[symbolTableCount] = lexeme[i];
            symbolTableCount++;
        }
        symbolTable[symbolTableCount] = '\t';
        symbolTableCount++;
        symbolTable[symbolTableCount] = '-';
        symbolTableCount++;
    }

    symbolTable[symbolTableCount] = '\n';
    symbolTableCount++;

}

void DefineIfDFA()
{
    IF_Transition_Table[q0][i] = q1;
    IF_Transition_Table[q0][f] = q3;
    IF_Transition_Table[q1][i] = q3;
    IF_Transition_Table[q1][f] = q2;
    IF_Transition_Table[q2][i] = q3;
    IF_Transition_Table[q2][f] = q3;
    IF_Transition_Table[q3][i] = q3;
    IF_Transition_Table[q3][f] = q3;
}


void DefineIdDFA()
{
    ID_Transition_Table[q0][A] = q1;
    ID_Transition_Table[q0][B] = q2;
    ID_Transition_Table[q1][A] = q1;
    ID_Transition_Table[q1][B] = q1;
    ID_Transition_Table[q2][A] = q2;
    ID_Transition_Table[q2][B] = q2;
}
void DefineWhileDFA(){
    WHILE_Transition_Table[q0][0] = q1;
    WHILE_Transition_Table[q0][1] = q6;
    WHILE_Transition_Table[q0][2] = q6;
    WHILE_Transition_Table[q0][3] = q6;
    WHILE_Transition_Table[q0][4] = q6;
    WHILE_Transition_Table[q1][0] = q6;
    WHILE_Transition_Table[q1][1] = q2;
    WHILE_Transition_Table[q1][2] = q6;
    WHILE_Transition_Table[q1][3] = q6;
    WHILE_Transition_Table[q1][4] = q6;
    WHILE_Transition_Table[q2][0] = q6;
    WHILE_Transition_Table[q2][1] = q6;
    WHILE_Transition_Table[q2][2] = q3;
    WHILE_Transition_Table[q2][3] = q6;
    WHILE_Transition_Table[q2][4] = q6;
    WHILE_Transition_Table[q3][0] = q6;
    WHILE_Transition_Table[q3][1] = q6;
    WHILE_Transition_Table[q3][2] = q6;
    WHILE_Transition_Table[q3][3] = q4;
    WHILE_Transition_Table[q3][4] = q6;
    WHILE_Transition_Table[q4][0] = q6;
    WHILE_Transition_Table[q4][1] = q6;
    WHILE_Transition_Table[q4][2] = q6;
    WHILE_Transition_Table[q4][3] = q6;
    WHILE_Transition_Table[q4][4] = q5;
    WHILE_Transition_Table[q5][0] = q6;
    WHILE_Transition_Table[q5][1] = q6;
    WHILE_Transition_Table[q5][2] = q6;
    WHILE_Transition_Table[q5][3] = q6;
    WHILE_Transition_Table[q5][4] = q6;
    WHILE_Transition_Table[q6][0] = q6;
    WHILE_Transition_Table[q6][1] = q6;
    WHILE_Transition_Table[q6][2] = q6;
    WHILE_Transition_Table[q6][3] = q6;
    WHILE_Transition_Table[q6][4] = q6;
}

void DefineBreakDFA(){
    BREAK_Transition_Table[q0][0] = q1;
    BREAK_Transition_Table[q0][1] = q6;
    BREAK_Transition_Table[q0][2] = q6;
    BREAK_Transition_Table[q0][3] = q6;
    BREAK_Transition_Table[q0][4] = q6;
    BREAK_Transition_Table[q1][0] = q6;
    BREAK_Transition_Table[q1][1] = q2;
    BREAK_Transition_Table[q1][2] = q6;
    BREAK_Transition_Table[q1][3] = q6;
    BREAK_Transition_Table[q1][4] = q6;
    BREAK_Transition_Table[q2][0] = q6;
    BREAK_Transition_Table[q2][1] = q6;
    BREAK_Transition_Table[q2][2] = q3;
    BREAK_Transition_Table[q2][3] = q6;
    BREAK_Transition_Table[q2][4] = q6;
    BREAK_Transition_Table[q3][0] = q6;
    BREAK_Transition_Table[q3][1] = q6;
    BREAK_Transition_Table[q3][2] = q6;
    BREAK_Transition_Table[q3][3] = q4;
    BREAK_Transition_Table[q3][4] = q6;
    BREAK_Transition_Table[q4][0] = q6;
    BREAK_Transition_Table[q4][1] = q6;
    BREAK_Transition_Table[q4][2] = q6;
    BREAK_Transition_Table[q4][3] = q6;
    BREAK_Transition_Table[q4][4] = q5;
    BREAK_Transition_Table[q5][0] = q6;
    BREAK_Transition_Table[q5][1] = q6;
    BREAK_Transition_Table[q5][2] = q6;
    BREAK_Transition_Table[q5][3] = q6;
    BREAK_Transition_Table[q5][4] = q6;
    BREAK_Transition_Table[q6][0] = q6;
    BREAK_Transition_Table[q6][1] = q6;
    BREAK_Transition_Table[q6][2] = q6;
    BREAK_Transition_Table[q6][3] = q6;
    BREAK_Transition_Table[q6][4] = q6;
    
}

void DefinePrintDFA(){
    PRINT_Transition_Table[q0][0] = q1;
    PRINT_Transition_Table[q0][1] = q6;
    PRINT_Transition_Table[q0][2] = q6;
    PRINT_Transition_Table[q0][3] = q6;
    PRINT_Transition_Table[q0][4] = q6;
    PRINT_Transition_Table[q1][0] = q6;
    PRINT_Transition_Table[q1][1] = q2;
    PRINT_Transition_Table[q1][2] = q6;
    PRINT_Transition_Table[q1][3] = q6;
    PRINT_Transition_Table[q1][4] = q6;
    PRINT_Transition_Table[q2][0] = q6;
    PRINT_Transition_Table[q2][1] = q6;
    PRINT_Transition_Table[q2][2] = q3;
    PRINT_Transition_Table[q2][3] = q6;
    PRINT_Transition_Table[q2][4] = q6;
    PRINT_Transition_Table[q3][0] = q6;
    PRINT_Transition_Table[q3][1] = q6;
    PRINT_Transition_Table[q3][2] = q6;
    PRINT_Transition_Table[q3][3] = q4;
    PRINT_Transition_Table[q3][4] = q6;
    PRINT_Transition_Table[q4][0] = q6;
    PRINT_Transition_Table[q4][1] = q6;
    PRINT_Transition_Table[q4][2] = q6;
    PRINT_Transition_Table[q4][3] = q6;
    PRINT_Transition_Table[q4][4] = q5;
    PRINT_Transition_Table[q5][0] = q6;
    PRINT_Transition_Table[q5][1] = q6;
    PRINT_Transition_Table[q5][2] = q6;
    PRINT_Transition_Table[q5][3] = q6;
    PRINT_Transition_Table[q5][4] = q6;
    PRINT_Transition_Table[q6][0] = q6;
    PRINT_Transition_Table[q6][1] = q6;
    PRINT_Transition_Table[q6][2] = q6;
    PRINT_Transition_Table[q6][3] = q6;
    PRINT_Transition_Table[q6][4] = q6;
}

void DefineFloatDFA(){
    FLOAT_Transition_Table[q0][A] = q1;
    FLOAT_Transition_Table[q0][B] = q2;
    FLOAT_Transition_Table[q1][A] = q3;
    FLOAT_Transition_Table[q1][B] = q4;
    FLOAT_Transition_Table[q2][A] = q4;
    FLOAT_Transition_Table[q2][B] = q2;
    FLOAT_Transition_Table[q3][A] = q3;
    FLOAT_Transition_Table[q3][B] = q3;
    FLOAT_Transition_Table[q4][A] = q3;
    FLOAT_Transition_Table[q4][B] = q4;
}

void DefineCompDFA(){
    COMP_Transition_Table[q0][g] = q1;
    COMP_Transition_Table[q0][a] = q3;
    COMP_Transition_Table[q0][n] = q4;
    COMP_Transition_Table[q0][e] = q1;
    COMP_Transition_Table[q0][o] = q5;
    COMP_Transition_Table[q1][g] = q6;
    COMP_Transition_Table[q1][a] = q6;
    COMP_Transition_Table[q1][n] = q6;
    COMP_Transition_Table[q1][e] = q2;
    COMP_Transition_Table[q1][o] = q6;
    COMP_Transition_Table[q2][g] = q6;
    COMP_Transition_Table[q2][a] = q6;
    COMP_Transition_Table[q2][n] = q6;
    COMP_Transition_Table[q2][e] = q6;
    COMP_Transition_Table[q2][o] = q6;
    COMP_Transition_Table[q3][g] = q6;
    COMP_Transition_Table[q3][a] = q2;
    COMP_Transition_Table[q3][n] = q6;
    COMP_Transition_Table[q3][o] = q6;
    COMP_Transition_Table[q3][e] = q6;
    COMP_Transition_Table[q4][g] = q6;
    COMP_Transition_Table[q4][a] = q6;
    COMP_Transition_Table[q4][n] = q6;
    COMP_Transition_Table[q4][o] = q6;
    COMP_Transition_Table[q4][e] = q2;
    COMP_Transition_Table[q5][g] = q6;
    COMP_Transition_Table[q5][a] = q6;
    COMP_Transition_Table[q5][n] = q6;
    COMP_Transition_Table[q5][e] = q6;
    COMP_Transition_Table[q5][o] = q2;
    COMP_Transition_Table[q6][g] = q6;
    COMP_Transition_Table[q6][a] = q6;
    COMP_Transition_Table[q6][n] = q6;
    COMP_Transition_Table[q6][o] = q6;
    COMP_Transition_Table[q6][e] = q6;
}

void DefineMathDFA(){
    //p = 0
    //m
    MATH_Transition_Table[q0][0] = q1;
    MATH_Transition_Table[q0][1] = q1;
    MATH_Transition_Table[q0][2] = q1;
    MATH_Transition_Table[q0][3] = q1;
    MATH_Transition_Table[q1][0] = q2;
    MATH_Transition_Table[q1][1] = q2;
    MATH_Transition_Table[q1][2] = q2;
    MATH_Transition_Table[q1][3] = q2;
    MATH_Transition_Table[q2][0] = q2;
    MATH_Transition_Table[q2][1] = q2;
    MATH_Transition_Table[q2][2] = q2;
    MATH_Transition_Table[q2][3] = q2;


}
void DefineCurlyDFA(){
    CURLY_Transition_Table[q0][0] = q1;
    CURLY_Transition_Table[q0][1] = q1;
    CURLY_Transition_Table[q1][0] = q2;
    CURLY_Transition_Table[q1][1] = q2;
    CURLY_Transition_Table[q2][0] = q2;
    CURLY_Transition_Table[q2][1] = q2;

}


void DefineRoundDFA(){
    ROUNDED_Transition_Table[q0][0] = q1;
    ROUNDED_Transition_Table[q0][1] = q1;
    ROUNDED_Transition_Table[q1][0] = q2;
    ROUNDED_Transition_Table[q1][1] = q2;
    ROUNDED_Transition_Table[q2][0] = q2;
    ROUNDED_Transition_Table[q2][1] = q2;
}


int ifDFA(char current_symbol)
{
    int i, pos;
    for(pos=0;pos<IF_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==IF_alphabet[pos])   
            break;//stops if any character other than a or b
    if(pos==IF_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<IF_FINAL_STATES;i++)
        if((Current_state=IF_Transition_Table[Current_state][pos])==IF_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}


int idDFA(char current_symbol){

    if ((current_symbol >= 65 && current_symbol <= 90) || (current_symbol >= 97 && current_symbol <= 122)){
        current_symbol = 'A';
    }
    else if (current_symbol >= 48 && current_symbol <= 57){
        current_symbol = 'B';
    }

    int i,pos;
    for(pos=0;pos<ID_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==ID_alphabet[pos])   
            break;//stops if any character other than a or b
    if(pos==ID_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<ID_FINAL_STATES;i++)
        if((Current_state=ID_Transition_Table[Current_state][pos])==ID_Accepted_States[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}

int whileDFA(char current_symbol){
    int i, pos;
    for(pos=0;pos<WHILE_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==WHILE_alphabet[pos])
            break;
    if(pos==WHILE_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<WHILE_FINAL_STATES;i++)
        if((Current_state=WHILE_Transition_Table[Current_state][pos])==WHILE_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}

int breakDFA(char current_symbol){
    int i, pos;
    for(pos=0;pos<BREAK_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==BREAK_alphabet[pos])
            break;
    if(pos==BREAK_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<BREAK_FINAL_STATES;i++)
        if((Current_state=BREAK_Transition_Table[Current_state][pos])==BREAK_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;

}

int printDFA(char current_symbol){
       int i, pos;
    for(pos=0;pos<PRINT_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==PRINT_alphabet[pos])
            break;
    if(pos==PRINT_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<PRINT_FINAL_STATES;i++)
        if((Current_state=PRINT_Transition_Table[Current_state][pos])==PRINT_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;

}

int floatDFA(char current_symbol){
    // A = .
    // B = 0 - 9

    if (current_symbol == '.'){
         current_symbol = 'A';
    }
    else if (current_symbol >= 48 && current_symbol <= 57){
        current_symbol = 'B';
    }

    int i,pos;
    for(pos=0;pos<FLOAT_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==FLOAT_alphabet[pos])
            break;
    if(pos==FLOAT_ALPHABET_CHARCTERS)
        return UNKNOWN_SYMBOL_ERR;


    Current_state=FLOAT_Transition_Table[Current_state][pos];
    for(i=0;i<FLOAT_FINAL_STATES;i++){
        if(( Current_state )==FLOAT_Accepted_states[i]){
            return REACHED_FINAL_STATE;
        }
    }
    return NOT_REACHED_FINAL_STATE;
}

int mathDFA(char current_symbol){
    int i, pos;
    for(pos=0;pos<MATH_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==MATH_alphabet[pos])
            break;
    if(pos==MATH_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<MATH_FINAL_STATES;i++)
        if((Current_state=MATH_Transition_Table[Current_state][pos])==MATH_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;

}

int compDFA(char current_symbol)
{
    //g = greater
    //a = ampersand
    //n = not
    //e = equals
    //o = or
    if (current_symbol == '>' || current_symbol == '<'){
        current_symbol = 'g';
    }
    if (current_symbol == '&'){
        current_symbol = 'a';
    }
    if (current_symbol == '!'){
        current_symbol = 'n';
    }
    if (current_symbol == '='){
        current_symbol = 'e';
    }
    if (current_symbol == '|'){
        current_symbol = 'o';
    }
    
    int i,pos;
    for(pos=0;pos<COMP_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==COMP_alphabet[pos])
            break;
    if(pos==COMP_ALPHABET_CHARCTERS)
        return UNKNOWN_SYMBOL_ERR;


    Current_state=COMP_Transition_Table[Current_state][pos];
    for(i=0;i<COMP_FINAL_STATES;i++){
        if(( Current_state )==COMP_Accepted_states[i]){
            return REACHED_FINAL_STATE;
        }
    }
    return NOT_REACHED_FINAL_STATE;
}

int roundedDFA(char current_symbol)
{
    int i, pos;
    for(pos=0;pos<ROUNDED_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==ROUNDED_alphabet[pos])
            break;
    if(pos==ROUNDED_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<ROUNDED_FINAL_STATES;i++)
        if((Current_state=ROUNDED_Transition_Table[Current_state][pos])==ROUNDED_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}

int curlyDFA(char current_symbol){
    int i, pos;
    for(pos=0;pos<CURLY_ALPHABET_CHARCTERS; pos++)
        if(current_symbol==CURLY_alphabet[pos])
            break;
    if(pos==CURLY_ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<CURLY_FINAL_STATES;i++)
        if((Current_state=CURLY_Transition_Table[Current_state][pos])==CURLY_Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;

}

bool runDFA(char *lexeme,void(*TransTable)(),int(*DFA)(char))
{
    char current_symbol;
    int result;
    bool check = false;
    Current_state = q0;
 
    (*TransTable)();    //Fill transition table
 
    for (int i = 0; i < strlen(lexeme); i ++){
        if((result = (*DFA)(lexeme[i]))==UNKNOWN_SYMBOL_ERR){
            break;
        }
    }
    switch(result) {
        case UNKNOWN_SYMBOL_ERR:
            check = false;
            break;
        case NOT_REACHED_FINAL_STATE:
            check = false;
            break;
        case REACHED_FINAL_STATE:
            check = true;
            break;
        default:
            check = false;

    }
 

    return check;
}

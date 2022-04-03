#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TOTAL_STATES 7
#define FINAL_STATES 2
#define UNKNOWN_SYMBOL_ERR 0
#define ALPHABET_CHARCTERS 6
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
enum DFA_STATES{q0,q1,q2,q3,q4,q5,q6};

//g = greater
//a = ampersand
//n = not
//e = equals
//o = or

enum input{g, a, n, e, o};
int Accepted_states[FINAL_STATES] = {q1, q2};
char alphabet[ALPHABET_CHARCTERS]={'g', 'a', 'n', 'e', 'o'};
int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
int Current_state = q0;

void DefineDFA()
{
    Transition_Table[q0][g] = q1;
    Transition_Table[q0][a] = q3;
    Transition_Table[q0][n] = q4;
    Transition_Table[q0][e] = q1;
    Transition_Table[q0][o] = q5;
    Transition_Table[q1][g] = q6;
    Transition_Table[q1][a] = q6;
    Transition_Table[q1][n] = q6;
    Transition_Table[q1][e] = q2;
    Transition_Table[q1][o] = q6;
    Transition_Table[q2][g] = q6;  
    Transition_Table[q2][a] = q6; 
    Transition_Table[q2][n] = q6; 
    Transition_Table[q2][e] = q6; 
    Transition_Table[q2][o] = q6; 
    Transition_Table[q3][g] = q6; 
    Transition_Table[q3][a] = q2; 
    Transition_Table[q3][n] = q6; 
    Transition_Table[q3][o] = q6; 
    Transition_Table[q3][e] = q6;
    Transition_Table[q4][g] = q6; 
    Transition_Table[q4][a] = q6; 
    Transition_Table[q4][n] = q6; 
    Transition_Table[q4][o] = q6; 
    Transition_Table[q4][e] = q2; 
    Transition_Table[q5][g] = q6;  
    Transition_Table[q5][a] = q6; 
    Transition_Table[q5][n] = q6; 
    Transition_Table[q5][e] = q6; 
    Transition_Table[q5][o] = q2; 
    Transition_Table[q6][g] = q6;  
    Transition_Table[q6][a] = q6; 
    Transition_Table[q6][n] = q6; 
    Transition_Table[q6][o] = q6;
    Transition_Table[q6][e] = q6; 
}

int DFA(char current_symbol)
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
    for(pos=0;pos<ALPHABET_CHARCTERS; pos++)
        if(current_symbol==alphabet[pos])   
            break;//stops if any character other than a or b
    if(pos==ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;


    Current_state=Transition_Table[Current_state][pos];
    for(i=0;i<FINAL_STATES;i++){
        if(( Current_state )==Accepted_states[i]){
            return REACHED_FINAL_STATE;
        }
    }
    return NOT_REACHED_FINAL_STATE;
}


int main(void)
{
    char current_symbol;
    int result;
    bool check = true;
    char lexeme[1] = {'<'};

    DefineDFA();    //Fill transition table
 
    printf("\nEnter a comparison operator: \n");

 
    while((current_symbol=getchar())!= '\n'){
        if((result= DFA(current_symbol))==UNKNOWN_SYMBOL_ERR)
            break;
    }
    switch (result) {
        case UNKNOWN_SYMBOL_ERR:
            printf("Unknown Symbol %c", current_symbol); 
            break;
        case NOT_REACHED_FINAL_STATE:
            printf("Not accepted"); break;
        case REACHED_FINAL_STATE:printf("Accepted");break;
        default: printf("Unknown Error");
    }

    //printf("%d",DFA(lexeme[0]));
    //printf("%d",DFA(lexeme[1]));
    /*
    printf("Length of string:%d\n",strlen(lexeme));
    for (int i = 0; i < strlen(lexeme); i ++){
        result = DFA(lexeme[i]);
        if((result)==UNKNOWN_SYMBOL_ERR){
            break;
        }
    }
    printf("%d", result);
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
    if (check == true ){
        printf("true");
    } else {
        printf("false");
    }*/

    printf("\n\n\n");
    return 0;
}
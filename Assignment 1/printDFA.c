#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_STATES 7
#define FINAL_STATES 1
#define ALPHABET_CHARCTERS 5
#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
enum DFA_STATES{q0, q1, q2, q3, q4, q5, q6};
enum input{p, r, i, n, t};
int Accepted_states[FINAL_STATES] = {q5};
char alphabet[ALPHABET_CHARCTERS]={'p', 'r', 'i', 'n', 't'};
int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
int Current_state = q0;

void DefineDFA()
{
    Transition_Table[q0][p] = q1;
    Transition_Table[q0][r] = q6;
    Transition_Table[q0][i] = q6;
    Transition_Table[q0][n] = q6;
    Transition_Table[q0][t] = q6;
    Transition_Table[q1][p] = q6;
    Transition_Table[q1][r] = q2;
    Transition_Table[q1][i] = q6;
    Transition_Table[q1][n] = q6;
    Transition_Table[q1][t] = q6;
    Transition_Table[q2][p] = q6;
    Transition_Table[q2][r] = q6;
    Transition_Table[q2][i] = q3;
    Transition_Table[q2][n] = q6;
    Transition_Table[q2][t] = q6;
    Transition_Table[q3][p] = q6;
    Transition_Table[q3][r] = q6;
    Transition_Table[q3][i] = q6;
    Transition_Table[q3][n] = q4;
    Transition_Table[q3][t] = q6;
    Transition_Table[q4][p] = q6;
    Transition_Table[q4][r] = q6;
    Transition_Table[q4][i] = q6;
    Transition_Table[q4][n] = q6;
    Transition_Table[q4][t] = q5;
    Transition_Table[q5][p] = q6;
    Transition_Table[q5][r] = q6;
    Transition_Table[q5][i] = q6;
    Transition_Table[q5][n] = q6;
    Transition_Table[q5][t] = q6;
    Transition_Table[q6][p] = q6;
    Transition_Table[q6][r] = q6;
    Transition_Table[q6][i] = q6;
    Transition_Table[q6][n] = q6;
    Transition_Table[q6][t] = q6;
}

int DFA(char current_symbol)
{
    int i,pos;
    for(pos=0;pos<ALPHABET_CHARCTERS; pos++)
        if(current_symbol==alphabet[pos])
            break;//stops if any character other than a or b
    if(pos==ALPHABET_CHARCTERS)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<FINAL_STATES;i++)
        if((Current_state=Transition_Table[Current_state][pos])==Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}


int main(void)
{
    char current_symbol;
    int result;
 
    DefineDFA();    //Fill transition table
 
    printf("\nEnter the word 'print': \n");
 
 
    while((current_symbol=getchar())!= '\n')
        if((result= DFA(current_symbol))==UNKNOWN_SYMBOL_ERR)
            break;
    switch (result) {
        case UNKNOWN_SYMBOL_ERR:
            printf("Unknown Symbol %c", current_symbol);
            break;
        case NOT_REACHED_FINAL_STATE:
            printf("Not accepted"); break;
        case REACHED_FINAL_STATE:printf("Accepted");break;
        default: printf("Unknown Error");
    }
    printf("\n\n\n");
    return 0;
}

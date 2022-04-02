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
enum input{b, r, e, a, k};
int Accepted_states[FINAL_STATES] = {q5};
char alphabet[ALPHABET_CHARCTERS]={'b', 'r', 'e', 'a', 'k'};
int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
int Current_state = q0;

void DefineDFA()
{
    Transition_Table[q0][b] = q1;
    Transition_Table[q0][r] = q6;
    Transition_Table[q0][e] = q6;
    Transition_Table[q0][a] = q6;
    Transition_Table[q0][k] = q6;
    Transition_Table[q1][b] = q6;
    Transition_Table[q1][r] = q2;
    Transition_Table[q1][e] = q6;
    Transition_Table[q1][a] = q6;
    Transition_Table[q1][k] = q6;
    Transition_Table[q2][b] = q6;
    Transition_Table[q2][r] = q6;
    Transition_Table[q2][e] = q3;
    Transition_Table[q2][a] = q6;
    Transition_Table[q2][k] = q6;
    Transition_Table[q3][b] = q6;
    Transition_Table[q3][r] = q6;
    Transition_Table[q3][e] = q6;
    Transition_Table[q3][a] = q4;
    Transition_Table[q3][k] = q6;
    Transition_Table[q4][b] = q6;
    Transition_Table[q4][r] = q6;
    Transition_Table[q4][e] = q6;
    Transition_Table[q4][a] = q6;
    Transition_Table[q4][k] = q5;
    Transition_Table[q5][b] = q6;
    Transition_Table[q5][r] = q6;
    Transition_Table[q5][e] = q6;
    Transition_Table[q5][a] = q6;
    Transition_Table[q5][k] = q6;
    Transition_Table[q6][b] = q6;
    Transition_Table[q6][r] = q6;
    Transition_Table[q6][e] = q6;
    Transition_Table[q6][a] = q6;
    Transition_Table[q6][k] = q6;
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
 
    printf("\nEnter the word 'break': \n");
 
 
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

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
enum input{w, h, i, l, e};
int Accepted_states[FINAL_STATES] = {q5};
char alphabet[ALPHABET_CHARCTERS]={'w', 'h', 'i', 'l', 'e'};
int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
int Current_state = q0;

void DefineDFA()
{
    Transition_Table[q0][w] = q1;
    Transition_Table[q0][h] = q6;
    Transition_Table[q0][i] = q6;
    Transition_Table[q0][l] = q6;
    Transition_Table[q0][e] = q6;
    Transition_Table[q1][w] = q6;
    Transition_Table[q1][h] = q2;
    Transition_Table[q1][i] = q6;
    Transition_Table[q1][l] = q6;
    Transition_Table[q1][e] = q6;
    Transition_Table[q2][w] = q6;
    Transition_Table[q2][h] = q6;
    Transition_Table[q2][i] = q3;
    Transition_Table[q2][l] = q6;
    Transition_Table[q2][e] = q6;
    Transition_Table[q3][w] = q6;
    Transition_Table[q3][h] = q6;
    Transition_Table[q3][i] = q6;
    Transition_Table[q3][l] = q4;
    Transition_Table[q3][e] = q6;
    Transition_Table[q4][w] = q6;
    Transition_Table[q4][h] = q6;
    Transition_Table[q4][i] = q6;
    Transition_Table[q4][l] = q6;
    Transition_Table[q4][e] = q5;
    Transition_Table[q5][w] = q6;
    Transition_Table[q5][h] = q6;
    Transition_Table[q5][i] = q6;
    Transition_Table[q5][l] = q6;
    Transition_Table[q5][e] = q6;
    Transition_Table[q6][w] = q6;
    Transition_Table[q6][h] = q6;
    Transition_Table[q6][i] = q6;
    Transition_Table[q6][l] = q6;
    Transition_Table[q6][e] = q6;
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
 
    printf("\nEnter the word 'while': \n");
 
 
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

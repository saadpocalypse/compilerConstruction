#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_STATES 3
#define FINAL_STATES 1
#define UNKNOWN_SYMBOL_ERR 0
#define ALPHABET_CHARCTERS 2
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
enum DFA_STATES{q0, q1, q2};
// l = (
// r = )
enum input{l, r};
int Accepted_states[FINAL_STATES] = {q1};
char alphabet[ALPHABET_CHARCTERS]={'(', ')'};
int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
int Current_state = q0;

void DefineDFA()
{
    Transition_Table[q0][l] = q1;
    Transition_Table[q0][r] = q1;
    Transition_Table[q1][l] = q2;
    Transition_Table[q1][r] = q2;
    Transition_Table[q2][l] = q2;
    Transition_Table[q2][r] = q2;

    
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
 
    printf("\nEnter a round bracket: \n");
 
 
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

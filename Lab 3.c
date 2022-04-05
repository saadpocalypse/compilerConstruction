// Ahmad Saad, 231461463, Lab 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global
#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
enum DFA_STATES{q0, q1, q2, q3, q4, q5, q6};
int Current_state = q0;

// Question 1
#define TOTAL_STATES_ONE 5
#define FINAL_STATES_ONE 1
#define ALPHABET_CHARCTERS_ONE 2
int Accepted_states_ONE[FINAL_STATES_ONE]={q4};
char alphabet_ONE[ALPHABET_CHARCTERS_ONE]={'0', '1'};
int Transition_Table_ONE[TOTAL_STATES_ONE][ALPHABET_CHARCTERS_ONE];

// Question 2
#define TOTAL_STATES_TWO 7
#define FINAL_STATES_TWO 1
#define ALPHABET_CHARCTERS_TWO 2
int Accepted_states_TWO[FINAL_STATES_TWO]={q5};
enum input{a, b};
char alphabet_TWO[ALPHABET_CHARCTERS_TWO]={'a', 'b'};
int Transition_Table_TWO[TOTAL_STATES_TWO][ALPHABET_CHARCTERS_TWO];

void define_DFA_one()
{
    Transition_Table_ONE[q0][0] = q0;
    Transition_Table_ONE[q0][1] = q1;
    Transition_Table_ONE[q1][0] = q2;
    Transition_Table_ONE[q1][1] = q1;
    Transition_Table_ONE[q2][0] = q3;
    Transition_Table_ONE[q2][1] = q1;
    Transition_Table_ONE[q3][0] = q0;
    Transition_Table_ONE[q3][1] = q4;
    Transition_Table_ONE[q4][0] = q2;
    Transition_Table_ONE[q4][1] = q1;
}

void define_DFA_two()
{
    Transition_Table_TWO[q0][a] = q0;
    Transition_Table_TWO[q0][b] = q1;
    Transition_Table_TWO[q1][a] = q2;
    Transition_Table_TWO[q1][b] = q1;
    Transition_Table_TWO[q2][a] = q6;
    Transition_Table_TWO[q2][b] = q3;
    Transition_Table_TWO[q3][a] = q6;
    Transition_Table_TWO[q3][b] = q4;
    Transition_Table_TWO[q4][a] = q5;
    Transition_Table_TWO[q4][b] = q6;
    Transition_Table_TWO[q5][a] = q6;
    Transition_Table_TWO[q5][b] = q6;
    Transition_Table_TWO[q6][a] = q6;
    Transition_Table_TWO[q6][b] = q2;
}

int DFA_ONE(char current_symbol)
{
    int i, pos;
    for(pos=0;pos<ALPHABET_CHARCTERS_ONE; pos++)
        if(current_symbol==alphabet_ONE[pos])
            break;
    if(pos==ALPHABET_CHARCTERS_ONE)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<FINAL_STATES_ONE;i++)
        if((Current_state=Transition_Table_ONE[Current_state][pos])==Accepted_states_ONE[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}

int DFA_TWO(char current_symbol)
{
    int i, pos;
    for(pos=0;pos<ALPHABET_CHARCTERS_TWO; pos++)
        if(current_symbol==alphabet_TWO[pos])
            break;
    if(pos==ALPHABET_CHARCTERS_TWO)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<FINAL_STATES_TWO;i++)
        if((Current_state=Transition_Table_TWO[Current_state][pos])==Accepted_states_TWO[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}


int main(void)
{
    char current_symbol;
    int result;
 
    define_DFA_one();
 
    printf("Enter a string with 0s and 1s:\n Press Enter Key to stop\n");
 
 
    while((current_symbol=getchar())!= '\n')
        if((result= DFA_ONE(current_symbol))==UNKNOWN_SYMBOL_ERR)
            break;
    switch (result) {
        case UNKNOWN_SYMBOL_ERR:
            printf("Unknown Symbol %c",current_symbol);
            break;
        case NOT_REACHED_FINAL_STATE:
            printf("Not accepted"); break;
        case REACHED_FINAL_STATE:printf("Accepted");break;
        default: printf("Unknown Error");
    }


    define_DFA_two(); 
    Current_state = q0;
 
    printf("\nEnter a string with a's and b's:\n Press Enter Key to stop\n");
 
 
    while((current_symbol=getchar())!= '\n')
        if((result= DFA_TWO(current_symbol))==UNKNOWN_SYMBOL_ERR)
            break;
    switch (result) {
        case UNKNOWN_SYMBOL_ERR:
            printf("Unknown Symbol %c",current_symbol);
            break;
        case NOT_REACHED_FINAL_STATE:
            printf("Not accepted"); break;
        case REACHED_FINAL_STATE:printf("Accepted");break;
        default: printf("Unknown Error");
    }
    printf("\n\n\n");
    return 0;
}
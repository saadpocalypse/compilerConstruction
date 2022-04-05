#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>

 #define TOTAL_STATES 5
 #define FINAL_STATES 2
 #define UNKNOWN_SYMBOL_ERR 0
 #define ALPHABET_CHARCTERS 2
 #define NOT_REACHED_FINAL_STATE 1
 #define REACHED_FINAL_STATE 2
 enum DFA_STATES{q0,q1,q2,q3,q4};

 // A = .
 // B = 0 - 9

 enum input{A, B};
 int Accepted_states[FINAL_STATES] = {q2, q4};
 char alphabet[ALPHABET_CHARCTERS]={'A', 'B'};
 int Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS];
 int Current_state = q0;

 void DefineDFA()
 {
     Transition_Table[q0][A] = q1;
     Transition_Table[q0][B] = q2;
     Transition_Table[q1][A] = q3;
     Transition_Table[q1][B] = q4;
     Transition_Table[q2][A] = q4;
     Transition_Table[q2][B] = q2;
     Transition_Table[q3][A] = q3;
     Transition_Table[q3][B] = q3;
     Transition_Table[q4][A] = q3;
     Transition_Table[q4][B] = q4;
     
 }

 int DFA(char current_symbol)
 {
    // A = .
    // B = 0 - 9

    if (current_symbol == '.'){
         current_symbol = 'A';
    }
    else if (current_symbol >= 48 && current_symbol <= 57){
        current_symbol = 'B';
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
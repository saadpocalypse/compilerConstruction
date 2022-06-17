#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int SIZE = 1;


char C[100][100][100] = {
    {
    {"X->S"},
    {"S->.L=R"},
    {"S->.R"},
    {"L->.*R"},
    {"L->.id"},
    {"R->.L"}
    }

};
//closure function J
char J[100][100];



char grammar[1000][1000] = {'\0'};

char terminals[1000] = {'\0'};
int terminalsPointer = 0;
char nonTerminals[1000] = {'\0'};
int nonTerminalPointer = 0;


char** closure(char** I, int stateIndex);
int findNumProds(int stateIndex);
char** copyItoJ(char** I,int stateIndex);
char findCharAfterDot(char* productionString);


//Add prod to Array     strcpy(I[0][6], "Sanders");

int main(){
    printf("%d\n", findNumProds(0));
    // printf("%lu\n",(sizeof() / sizeof(*I)));

    // J[100][100] = 

    for(int i = 0; i < findNumProds(0); i++){
            printf("%s\n", C[0][i] );
    }

    return 0;
}

char** closure(char** I, int stateIndex){
    //reintialize J 
    memset(J, 0, sizeof(J[0][0]) * 100 * 100);
    bool jChangeFlag = true;

    while( jChangeFlag == true ){

        for(int i = 0;  i < findNumProds(stateIndex); i++){
            char character = findCharAfterDot(J[i]);
            
            if( checkIfTerminal(character) == true ){
                break;
            }

        }
    }

    return J;
}

int findNumProds(int stateIndex){
    int num = 0;
    for (int i = 0; i < 100; i++){
        if( C[stateIndex][i][0] == '\0'){
            break;
        }
        num++;
    }
    return num;
}


char** copyItoJ(char** I, int stateIndex){
    for (int i = 0; i < findNumProds(stateIndex); i++){
        strcpy(J[0][i], I[stateIndex][i]);
    }
}

//Pass in the individual String Xproduction[0]
char findCharAfterDot(char* productionString){
    int dotCol = -1;
    for (int i = 0; i < strlen(productionString) - 1; i++){
        if(productionString[0] == '.'){
            dotCol = i; 
        }
    }

    if(dotCol == - 1 ){
        //Something to break the loop
        return 'Parsed';
    }
    return productionString[dotCol + 1];
    
}
bool checkIfTerminal(char character){
    for( int i = 0; i < strlen(terminals); i++){
        if(terminals[i] == character){
            return true;
        }
    }
    return false;
}
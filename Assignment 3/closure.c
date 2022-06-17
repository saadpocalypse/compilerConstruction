#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int SIZE = 1;


char C[100][100][100] = {
    {
    {"X->.S"}
    }

};
//closure function J
char J[100][100];
char G[100][100] = { {"X->.S"}, {"S->L=R."}, {"S->.R"}, {"L->.*R"}, {"L->.id"}, {"R->.L"} };
char gotoSet[100][100];

char terminals[1000] = {'=','*','i'};
int terminalsPointer = 0;
char nonTerminals[1000] = {'X','S','L','R'};
int nonTerminalPointer = 0;

int findNumProds(int stateIndex);
char findCharAfterDot(char* productionString);

//goto
void gotoFunc(char I[100][100],int stateIndex, char symbol);
void addtoGotoSet(char* productionString);
int findProdsGotoSet();


//Add prod to Array     strcpy(I[0][6], "Sanders");

int main(){
    printf("%d\n", findNumProds(0));

    gotoFunc(G[0],0, findCharAfterDot(G[0]));
    //printf("%d\n", findProdsGotoSet());
    for(int i = 0; i < findProdsGotoSet(); i++){
            printf("%s\n", gotoSet[i] );
    }

    return 0;


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

void gotoFunc(char I[100][100], int stateIndex ,char symbol){
    memset(gotoSet, 0, sizeof(gotoSet[0][0]) * 100 * 100);
    if (symbol=='.'){return;}

    for(int i = 0; i < findNumProds(stateIndex); i++){
        int dotCol = -1;
        char character;
        for (int j = 0; j < strlen(I[i]) - 1; j++){
            if(I[i][j] == '.'){
                dotCol = j;
                break; 
            }
        }
        if(dotCol == - 1 ){
            //Something to break the loop
            character = '.';
        }
        character =  I[i][dotCol + 1];

        //WHAT TO DO if character is i then we have special swapping case
    
        if(character == '.'){
            continue;
        }

        char production[100];
        strcpy(production, I[i]);
        
        if (character == symbol){
            if( character == 'i'){
                production[dotCol] = 'i';
                production[dotCol + 1] = 'd';
                production[dotCol + 2] = '.';
            } else {
                 production[dotCol] = symbol;
                production[dotCol + 1] = '.';
            }
            int gotoSetLength = findProdsGotoSet();
            strcpy(gotoSet[gotoSetLength], production);
        }

        int gotoSetLength = findProdsGotoSet();
        strcpy(gotoSet[gotoSetLength], production);
    }

    //closure(gotoSet)
     
}



int findProdsGotoSet(){
    int num = 0;
    for (int i = 0; i < 100; i++){
        if( gotoSet[i][0] == '\0'){
            break;
        }
        num++;
    }
    return num;
}


char findCharAfterDot(char* productionString){
    int dotCol = -1;
    for (int i = 0; i < strlen(productionString) - 1; i++){
        if(productionString[i] == '.'){
            dotCol = i; 
        }
    }
    if(dotCol == - 1 ){
        //Something to break the loop
        return '.';
    }
    return productionString[dotCol + 1];
}
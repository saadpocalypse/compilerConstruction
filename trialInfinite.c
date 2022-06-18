#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char terminals[100][100];
char nonTerminals[100][100];
char allCharacters[100][100];
char grammar[100][100];
char tempString[100];
int terminalCounter = 0;
int nonTerminalCounter = 0;
int charCounter = 0;
int grammarCounter = 0;

int main(){
    int index = 0;
    int tempCounter = 0;
    bool flag;
    bool orFlag = false;

    FILE *fptr;
    fptr = fopen("grammar.txt", "r");

    while (1){
        flag = true;
        char c = fgetc(fptr);
        if (c == EOF){
            // printf("%s\n", tempString);
            stpcpy(grammar[grammarCounter], tempString);
            grammarCounter++;
            break;
        }
        else{
            if (orFlag == false){
                if (c != '\n'){
                    if (index == 0){
                        for (int counter = 0; counter < terminalCounter; counter++){
                            if (terminals[counter][0] == c){
                                flag = false;
                            }
                        }
                        if (flag == true){
                            terminals[terminalCounter][0] = c;
                            terminalCounter++;
                        }
                        else{
                            flag = true;
                        }
                    }
                    tempString[tempCounter] = c;
                    tempCounter++;
                    index++;
                }
                if (c == '|'){
                    stpcpy(grammar[grammarCounter], tempString);
                    grammarCounter++;
                    memset(tempString,0,sizeof(tempString));
                    tempCounter = 0;
                    orFlag = true;
                }
                else{
                    index = 0;
                    // printf("%s\n", tempString);
                    stpcpy(grammar[grammarCounter], tempString);
                    grammarCounter++;
                    memset(tempString,0,sizeof(tempString));
                    tempCounter = 0;
                    
                }  
            }
            else{
                printf("jksndbfjkn\n");
                orFlag = false;
            } 
        }
    }
    // // printf("%s", tempString);
    // printf("%s", grammar[2]);
    // int indexTwo = 0;
    // FILE *fptrTwo;
    // bool flagTwo = false;
    // fptrTwo = fopen("grammar.txt", "r");

    // while (1){
    //     char cTwo = fgetc(fptrTwo);
    //     if (cTwo == EOF){
    //         break;
    //     }
    //     else{
    //         if (flagTwo != false){

    //         }
            
    //     }
    // }

    


    return 0;
    
}
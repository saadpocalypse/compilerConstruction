#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char augmentedString[100];
char stringHandlingOrs[100];
char terminals[100][100];
char leftHandSide[100];
char rightHandString[100];
char nonTerminals[100][100];
char allCharacters[100][100];
char grammar[100][100];
char realGrammar[100][100];
char tempString[100];
char tempLeft[100];
int terminalCounter = 0;
int nonTerminalCounter = 0;
int charCounter = 0;
int grammarCounter = 0;
int grammarCounterTwo = 0;
char finalGrammar[100][100];
int finalGrammarCounter = 0;


int main(){
    int index = 0;
    int tempCounter = 0;
    bool flag;
    bool flagSpace = false;
    // bool orFlag = false;

    FILE *fptrOne;
    fptrOne = fopen("grammar.txt", "r");
    while (1){
        char cOne = fgetc(fptrOne);
        if (cOne == EOF){
            break;
        }
        else{
            augmentedString[0] = cOne;
            augmentedString[1] = '\'';
            augmentedString[2] = ' ';
            augmentedString[3] = '-';
            augmentedString[4] = '>';
            augmentedString[5] = ' ';
            augmentedString[6] = '.';
            augmentedString[7] = cOne;
            stpcpy(realGrammar[grammarCounterTwo], augmentedString);
            grammarCounterTwo++;
            break;
        }
    }


    FILE *fptr;
    fptr = fopen("grammar.txt", "r");
    bool flagOR = true;
    int ORhandler = 0;
    int rightCounter = 0;
    char left;
    bool leftFlag = true;
    int leftCounter = 0;
    bool rightFlag = false;

    while (1){
        flag = true;
        char c = fgetc(fptr);
        if (c == EOF){
            // printf("%s\n", tempString);
            // printf("%s\n", leftHandSide);
            stpcpy(grammar[grammarCounter], tempString);
            grammarCounter++;

            // ADD TO GRAMMAR HERE
            strcat(leftHandSide, rightHandString);
            stpcpy(realGrammar[grammarCounterTwo], leftHandSide);
            grammarCounterTwo++;
            // printf("%s%s", leftHandSide, rightHandString);
            break;
        }
        else{
            // if (orFlag == false){ 
            if (c != '\n'){
                if (leftFlag == true){
                    leftHandSide[leftCounter] = c;
                    // printf("%c", c);
                    leftCounter++;
                }
                if (index == 5){
                    tempString[tempCounter] = '.';
                    tempCounter++;
                    // printf("%s\n", tempString);
                    flagOR = false;
                }
                if (flagOR == true){
                    stringHandlingOrs[ORhandler] = c;
                    ORhandler++;
                }
                if (index == 0){
                    char left = c;
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
                if (c == '>'){
                    leftHandSide[leftCounter] = ' ';
                    leftHandSide[leftCounter + 1] = '.';
                    leftCounter = leftCounter + 2;
                    leftFlag = false;
                }
            
                if (index > 3 && c != '|'){
                    if (flagSpace == true){
                        if (c != ' '){
                            rightHandString[rightCounter] = c;
                            rightCounter++;
                        }
                    }
                    else{
                        if (rightFlag == true){
                            rightHandString[rightCounter] = c;
                            rightCounter++;
                        }
                        else{
                            if (c != ' '){
                                rightHandString[rightCounter] = c;
                                rightCounter++;
                                rightFlag = true;
                            }
                        }
                    }
                    
                }
                if (c == '|'){
                    flagSpace = true;
                    stpcpy(tempLeft, leftHandSide);
                    strcat(tempLeft, rightHandString);
                    
                    // ADD THIS TO GRAMMAR 
                    stpcpy(realGrammar[grammarCounterTwo], tempLeft);
                    grammarCounterTwo++;
                    memset(rightHandString, 0, sizeof(rightHandString));
                    rightCounter = 0;
                }
                tempString[tempCounter] = c;
                tempCounter++;
                index++;
                
            }
                // if (c == '|'){
                //     stpcpy(grammar[grammarCounter], tempString);
                //     grammarCounter++;
                //     memset(tempString,0,sizeof(tempString));
                //     tempCounter = 0;
                //     // orFlag = true;
                // }
            else{
                rightFlag = false;
                flagSpace = false;
                // strcat(leftHandSide, rightHandString);
                // printf("%s\n", leftHandSide);
                leftFlag = true;
                // printf("%s\n", leftHandSide);
                index = 0;
                // printf("%s\n", tempString);
                stpcpy(grammar[grammarCounter], tempString);
                grammarCounter++;
                memset(tempString,0,sizeof(tempString));
                tempCounter = 0;
                
                // ADD TO GRAMMAR HERE
                strcat(leftHandSide, rightHandString);
                stpcpy(realGrammar[grammarCounterTwo], leftHandSide);
                grammarCounterTwo++;
                memset(rightHandString, 0, sizeof(rightHandString));
                memset(leftHandSide, 0, sizeof(leftHandSide));
                leftCounter = 0;
                rightCounter = 0;
            }  
            // }
            // else{
            //     // printf("jksndbfjkn\n");
            //     orFlag = false;
            // } 
        }
    }
    printf("\n----------FULL GRAMMAR--------------\n");
    for (int counterFinal = 0; counterFinal < grammarCounterTwo; counterFinal++){
        printf("%s\n", realGrammar[counterFinal]);
    }
    printf("Total productions are: %d\n", grammarCounterTwo);




    printf("\n---------TERMINALS---------------\n");
    for (int counterFinal = 0; counterFinal < terminalCounter; counterFinal++){
        printf("%s\n", terminals[counterFinal]);
    }
    printf("Total terminals are: %d\n", terminalCounter);





    // for (int counterFinal = 0; counterFinal < terminalCounter; counterFinal++){
    //     printf("%s\n", terminals[counterFinal]);
    // }
    
    // printf("%s", grammar[0]);
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

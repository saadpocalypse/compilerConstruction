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
int grammarCounter = 0;
int grammarCounterTwo = 0;
char nonterminalsStr[100];


int main(){
    int index = 0;
    int tempCounter = 0;
    bool flag;
    bool flagSpace = false;

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
            stpcpy(grammar[grammarCounter], tempString);
            grammarCounter++;

            strcat(leftHandSide, rightHandString);
            stpcpy(realGrammar[grammarCounterTwo], leftHandSide);
            grammarCounterTwo++;
            break;
        }
        else{
            if (c != '\n'){
                if (leftFlag == true){
                    leftHandSide[leftCounter] = c;
                    leftCounter++;
                }
                if (index == 5){
                    tempString[tempCounter] = '.';
                    tempCounter++;
                    flagOR = false;
                }
                if (flagOR == true){
                    stringHandlingOrs[ORhandler] = c;
                    ORhandler++;
                }
                if (index == 0){
                    left = c;
                    for (int counter = 0; counter < nonTerminalCounter; counter++){
                        if (nonTerminals[counter][0] == c){
                            flag = false;
                        }
                    }
                    if (flag == true){
                        nonterminalsStr[0] = c;
                        stpcpy(nonTerminals[nonTerminalCounter], nonterminalsStr);
                        nonTerminalCounter++;
                        memset(nonterminalsStr, 0, sizeof(nonterminalsStr));
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
                    
                    stpcpy(realGrammar[grammarCounterTwo], tempLeft);
                    grammarCounterTwo++;
                    memset(rightHandString, 0, sizeof(rightHandString));
                    rightCounter = 0;
                }
                tempString[tempCounter] = c;
                tempCounter++;
                index++;
                
            }
            else{
                rightFlag = false;
                flagSpace = false;
                leftFlag = true;
                index = 0;
                stpcpy(grammar[grammarCounter], tempString);
                grammarCounter++;
                memset(tempString,0,sizeof(tempString));
                tempCounter = 0;
                
                strcat(leftHandSide, rightHandString);
                stpcpy(realGrammar[grammarCounterTwo], leftHandSide);
                grammarCounterTwo++;
                memset(rightHandString, 0, sizeof(rightHandString));
                memset(leftHandSide, 0, sizeof(leftHandSide));
                leftCounter = 0;
                rightCounter = 0;
            }  
        }
    }

    int c;
    FILE *file;
    char string[1024] = {0};
    int counter = 0;
    char array[100][100];
    int arrayCounter = 0;
    file = fopen("grammar.txt", "r");
    if (file){
        while ((c = getc(file)) != EOF){
            if(c != '\n'){
                string[counter] = c;
                counter++;
            }
            else{
                string[counter] = ' ';
                counter++;
            }
        }
        fclose(file);
    }
    char *split = strtok(string, " ");
    while(split != NULL){
        stpcpy(array[arrayCounter], split);
        arrayCounter++;
        split = strtok (NULL, " ");
    }

    bool terminalsFlag = true;

    for (int counter = 0; counter < arrayCounter; counter++){
        for (int counterTwo = 0; counterTwo < nonTerminalCounter; counterTwo++){
            if(strcmp(array[counter], nonTerminals[counterTwo]) == 0){
                terminalsFlag = false;
            }
        }
        if (terminalsFlag == true){
            if (strcmp(array[counter], "->") != 0 && strcmp(array[counter], "|") != 0){
                stpcpy(terminals[terminalCounter], array[counter]);
                terminalCounter++;
            }
        }
        terminalsFlag = true;
    }

    char fullGrammar[100][100];
    int fullCount = 0;

    for (int counter = 0; counter < terminalCounter; counter++){
        stpcpy(fullGrammar[fullCount], terminals[counter]);
        fullCount++;
    }
    for (int counter = 0; counter < nonTerminalCounter; counter++){
        stpcpy(fullGrammar[fullCount], nonTerminals[counter]);
        fullCount++;
    }

    printf("\n----------FULL GRAMMAR--------------\n");
    for (int counterFinal = 0; counterFinal < grammarCounterTwo; counterFinal++){
        printf("%s\n", realGrammar[counterFinal]);
    }
    printf("Total productions are: %d\n", grammarCounterTwo);

    printf("\n---------NON-TERMINALS---------------\n");
    for (int counterFinal = 0; counterFinal < nonTerminalCounter; counterFinal++){
        printf("%s\n", nonTerminals[counterFinal]);
    }
    printf("Total non-terminals are: %d\n", nonTerminalCounter);

    printf("\n---------TERMINALS---------------\n");
    for (int counterFinal = 0; counterFinal < terminalCounter; counterFinal++){
        printf("%s\n", terminals[counterFinal]);
    }
    printf("Total terminals are: %d\n", terminalCounter);

    printf("\n------------THE FULL GRAMMAR--------------\n");
    for (int counter = 0; counter < fullCount; counter++){
        printf("%s\n", fullGrammar[counter]);
    }
    printf("Total elements in the grammar are: %d\n", fullCount);
    return 0;
}


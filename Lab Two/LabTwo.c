// Ahmad Saad, 231461463, Lab 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char stringFinal[1000] = {'\0'}; // A string buffer with initialised with 1000 repitions of \0 (to remove garbage values).
    char finalArray[1000] = {'\0'}; // Here, the numbered lines are appended.
    int printablesArray[1000] = {0}; // The character count for each line is added here.
    char charToCount = 'a'; // A character, the repitions for which will be counted.
    int lineCounter = 0; // Counter that keeps count of the number of lines.
    int charCounter = 0; // Counter that keeps count of the number of repititions of the character to be searched.
    int counterOne = 0; // Incremental counter for stringFinal.
    int counterTwo = 0; // Incremental counter for lineNumbers.
    char* buffer = (char*) malloc(sizeof(char)*100); // malloc created as instructed in the lab manual.
    memset(buffer, '\0', 100); //memset applied to the malloc.
    FILE *filePointer; // This is the file we will open.
    FILE* filePointerTwo; // This is when we will repoen the file to overwrite it.

    if(argc != 2) // To handle for incorrect inputs.
    {
        printf("Incorrect input received!\n");
        exit(0);
    }
    filePointer = fopen(argv[1], "r"); 
    if (filePointer == NULL) // To handle an error in the file opening process.
    {
        printf("There was an error in opening the file, try again please!");
        exit(0);
    }


    while (fgets(buffer, 100, filePointer) != NULL) // We are now reading the file line by line.
    {
        lineCounter++; // Each new line increments the counter for number of lines.
        int printableCount = 0; // A counter is intiliazed with the value 0 that keeps count of all the printable characters in each line.
        strcpy(stringFinal, buffer); // This copies the final string from the buffer to the finalString array.
        finalArray[counterOne] = lineCounter + '0'; // The few lines of code below make sure the final output is formatted correctly as per lab manual.
        counterOne++;
        finalArray[counterOne] = '.';
        counterOne++;
        finalArray[counterOne] = ' ';
        counterOne++;
        for (int i = 0; i < strlen(stringFinal); i++) { // Here we read each line character by character.
            if (stringFinal[i] == charToCount) { // Whenever the character we are looking for is found, its counter is incremented.
                charCounter++;
            }
            // 0, 10 and 32 are the ASCII values of \0, \n and space respectively.
            if (stringFinal[i] != 0 && stringFinal[i] != EOF && stringFinal[i] != 10 && stringFinal[i] != 32) {
                printableCount++; // We only increment this counter when a printable character is read.
            }
            finalArray[counterOne] = stringFinal[i];
            counterOne++; 
        }
        printablesArray[counterTwo] = printableCount;
        counterTwo++; // This is to keep the count of each line's characters in a maintained order in a separate array.

    }
    // The code below is just standard printing of all the data.
    printf("%s\n", finalArray); 
    printf("Number of lines: %d\n", lineCounter);
    for (int i = 0; i < counterTwo; i++){
        printf("Number of characters in line %d: %d\n", i+1, printablesArray[i]);
    }
    printf("Character \'%c\' has %d occurrences\n", charToCount, charCounter);
    // The file is closed.
    fclose(filePointer);

    // A second pointer for the file opens it with the write instruction this time and overwrites the data.
    filePointerTwo = fopen(argv[1], "w");
    int finalOutput = fputs(finalArray, filePointerTwo);
    if( finalOutput == EOF ){
        printf("Failed to copy"); // In case there is an error in writing into the file.
    }
    fclose(filePointerTwo); // The file is finally overwritten and closed.
    return 0;
}
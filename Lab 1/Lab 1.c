#include <stdio.h>
#include <stdlib.h>
int BUFF = 1024;

int main(int argc, char *argv[]){
    FILE *filePointer;
    char ch;
    char stringOne[BUFF];
    int counter = 0;
    FILE *filePointerTwo;

    filePointer = fopen(argv[1], "r");
    if (filePointer == NULL){
            printf("File is not available \n");
        }
        else{
            while ((ch = fgetc(filePointer)) != EOF)
            {
                if (ch != 40 && ch != 41 && ch != 91 && ch != 93 && ch != 123 && ch != 125){
                    stringOne[counter] = ch;
                    counter++;
                
                }
            }
        }
        fclose(filePointer);

    filePointerTwo = fopen(argv[2], "w");
            int intoFileTwo = fputs(stringOne, filePointerTwo);
            if (intoFileTwo == EOF){
                printf("Failed to copy file!");
            }
            fclose(filePointerTwo);

        return 0;
}

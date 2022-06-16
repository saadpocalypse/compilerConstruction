#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int sizeX = 4;

int func(char arg, char list[][1024]);

char canonicalNames[1024][1024];

char Aproductions[1024][1024] = {
    {'S', '-', '>', '.', 'L', '=', 'R'},
    {'S', '-', '>', '.', 'R'},
    {'L', '-', '>', '.', '*', 'R'},
    {'L', '-', '>', '.', 'i'},
    {'R', '-', '>', '.', 'L', 'd'}
};

int main(){
    func('S', Aproductions);
    return 0;
}


int func(char arg, char list[][1024]){
    int counter = 0;
    for (int i = 0; i < 1024; i++){
        if (list[i][0] == arg){
            printf("%s\n", Aproductions[i]);
            strcpy(canonicalNames[counter], Aproductions[i]);
            counter++;
        }
    }
    printf("-------------\n%s\n", canonicalNames[0]);
    printf("%s", canonicalNames[1]);
    return 0;
}

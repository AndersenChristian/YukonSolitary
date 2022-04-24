//
// Created by Christian Andersen on 22-04-2022.
//
#include "Header.h"

#include <string.h>
#include <stdio.h>
#include <malloc.h>
/*
char* getPlayerInput(){
    char *input = malloc(4 * sizeof(char));
    printf("\nPick a column and the card nr. seperated by a blank space\n");
    do {
        scanf("%[^\n]", input);
        if(input[0] > 47 && input[0] < 58 && input[1] == 32 && input[2] > 47 && input[2] < 58) {
            input[3] = '\0';
            return input;
        }
        fseek(stdin,0,SEEK_END);
        printf("invalid input, try again!\n");
    } while (true);
}
 */


char input[200];

void showMessage(char* msg){
    printf("Message: %s\n", msg);
}

char* getPlayerInput(){
    printf("INPUT > ");
    fgets (input, 100, stdin);
    return input;
}


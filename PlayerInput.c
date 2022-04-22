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

char* lastCommand;
char input[];

char testMessage[] = "Test Message";

void nextPlayerInput(){
    showPrevCommand();
    showMessage(testMessage);
    char* input = getPlayerInput();
    processPlayerInput(input);
}

void showPrevCommand(){
    printf("LAST Command: %s", lastCommand);
}

void showMessage(char* msg){
    printf("Message: %s\n", msg);
}

char* getPlayerInput(){
    scanf("INPUT > ", &input);
}

void processPlayerInput(char string[]){
    lastCommand = string;

    char* initials = *string + *(string+1)+'\0';

    if (*(string+2) == ':'){ // Game Move

    } else {
        // Things to process
        if (strcmp(initials, "LD") == 1){

        } else if (strcmp(initials, "SW") == 1){

        } else if (strcmp(initials, "SI") == 1){

        } else if (strcmp(initials, "SR") == 1){

        } else if (strcmp(initials, "SD") == 1){

        } else if (strcmp(initials, "QQ") == 1){

        } else if (strcmp(initials, "P") == 1){

        } else if (strcmp(initials, "Q") == 1){

        }
    }
}
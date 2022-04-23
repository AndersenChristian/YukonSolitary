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
char input[200];

char testMessage[] = "Test Message";

void nextPlayerInput(){
    showMessage(testMessage);
    getPlayerInput();
    processPlayerInput(input);
}

char* getLastCommand(){
    return lastCommand;
}

void showMessage(char* msg){
    printf("Message: %s\n", msg);
}

char* getPlayerInput(){
    printf("INPUT > ");
    scanf("%s", input);
    printf("\n");
}

void processPlayerInput(char* string){
    printf("Inputted String: %s\n", string);

    lastCommand = string;

    char initials[3];
    memcpy(initials, string, 2);

    printf("Initials: %s\n", initials);


    if (string[2] == ':'){ // Game Move
        printf("Is a game move!\n");
    } else {
        // Things to process
        if (strcmp(initials, "LD") == 0){
            
        } else if (strcmp(initials, "SW") == 0){

        } else if (strcmp(initials, "SI") == 0){

        } else if (strcmp(initials, "SR") == 0){

        } else if (strcmp(initials, "SD") == 0){

        } else if (strcmp(initials, "QQ") == 0){

        } else if (strcmp(initials, "P") == 0){

        } else if (strcmp(initials, "Q") == 0){

        }
    }
}
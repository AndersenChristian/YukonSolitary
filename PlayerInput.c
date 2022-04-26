//
// Created by Christian Andersen on 22-04-2022.
//
#include "Header.h"

#include <string.h>
#include <stdio.h>


char input[200];

void showMessage(char* msg){
    printf("Message: %s\n", msg);
}

char* getPlayerInput(){
    printf("INPUT > ");
    fflush(stdin);
    fgets (input, 100, stdin);
    return input;
}


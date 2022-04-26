//
// Created by Christian Andersen on 22-04-2022.
//
#include "Header.h"

#include <string.h>
#include <stdio.h>


char input[255];

char* getPlayerInput(){
    printf("INPUT > ");
    fflush(stdin);
    fgets (input, 255, stdin);
    return input;
}


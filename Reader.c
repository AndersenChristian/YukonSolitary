//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>
#include "Header.h"
#include <string.h>

char buffer[5];
FILE *cardFile;

void setupCards(){
    printf("in Reader\n"); //TODO: delete after testing
    char errorMessage[100];

    if (getLastCommand()[2] != 32)
        cardFile = fopen("..\\Cards.txt","r");
    else
        cardFile = fopen(strtok(getLastCommand(),""),"r");
    if (cardFile == NULL) {
        strcpy(errorMessage, "the file does not exist");
        setErrorMessage(errorMessage);
        return;
    }
    initDeck();
    for (int i = 0; i < 52; ++i) {
        if (fgets(buffer, 10, cardFile)){
            pushCardToDeck((char *) buffer);
        }
    }
    fclose(cardFile);
}
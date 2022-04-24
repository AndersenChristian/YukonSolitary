//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>

#include "Header.h"
#include <string.h>

char buffer[5];
FILE *cardFile;

void setupCards(){
    if (getPlayerInput()[2] != 32)
        cardFile = fopen("..\\Cards.txt","r");
    else
        cardFile = fopen(strtok(getPlayerInput(),""),"r");
    if (cardFile == NULL)

    initDeck();
    for (int i = 0; i < 52; ++i) {
        if (fgets(buffer, 10, cardFile)){
            pushCardToDeck((char *) buffer);
        }
    }
    fclose(cardFile);
}
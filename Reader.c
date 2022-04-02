//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>

#include "Header.h"
#include <string.h>

char buffer[3];
FILE *cardFile;

void setupCards(){
    //FILE *cardFile;
    //char buffer[2];

    cardFile = fopen("..\\Cards.txt","r");

    for (int i = 0; i < 52; ++i) {
        if (fgets(buffer, 4, cardFile)){
            buffer[strlen(buffer) - 1] = '\0';
            setCardName((char *) buffer, i);
        }
    }
    fclose(cardFile);
}
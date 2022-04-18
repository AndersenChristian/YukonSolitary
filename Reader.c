//
// Created by Rawfodog on 02-04-2022.
//
#include <stdio.h>

#include "Header.h"
#include <string.h>

char buffer[5];
FILE *cardFile;

void setupCards(){

    cardFile = fopen("..\\Cards.txt","r");

    for (int i = 0; i < 52; ++i) {
        if (fgets(buffer, 10, cardFile)){
            setCardName((char *) buffer, i);
        }
    }
    //creates the dummy cards for the linked list
    buffer[0] = '0';
    buffer[1] = '0';
    for (int i = 0; i < 11; ++i) {
        setCardName((char*) buffer, i+52);
    }
    fclose(cardFile);
}
//
// Created by Rawfodog on 01-04-2022.
//
#include <stdio.h>
#include "Header.h"


void updateDisplay(){

    //pure test display for input variables
    //printing using array of pointers.
    int n = 0;
    while (n < 52) {
        if(n%7 == 0) {
            printf("\n");
        }
        if(getCard(n)->faceUp==1)
            printf("%s\t", getCard(n)->name);
        else
            printf("[]\t");
        n++;
    }

    printf("\n\n\n");

    //printing using linked list
    int cardsToPrint = 0;
    int currentLine = 0;
    int line = 0;
    int finishedLines[7]; //0 = not finished, 1 = is finished.

    for (int i = 0; i < 7; i++) {
        finishedLines[i]=0;
    }

    while (cardsToPrint < 52) {
        //defines when to make a new line
        if(currentLine%7 == 0) {
            printf("\n");
            line++;
        }

        Card * currentSpot = getBoard()[currentLine];

        if(finishedLines[currentLine] == 0){
            for (int i = 0; i < line-1; i++) {
                currentSpot = currentSpot->next;
            }
            if (currentSpot->next == NULL)
                finishedLines[currentLine] = 1;
            printf("%s\t",currentSpot->name);
            cardsToPrint++;
        } else
            printf("\t");

        //ensure that the currentLine pointer goes around the right way.
        if(currentLine != 6)
            currentLine++;
        else
            currentLine = 0;
    }
}
//
// Created by Rawfodog on 01-04-2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void displayInfolines();

void updateDisplay(){
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n"); //always the first line we need printed
    if (!isDeckLoaded())
        displayEmpty();
    else
        defaultDisplay();

    displayInfolines();
}

void displayEmpty(){
    int count = 1;
    for (int i = 0; i < 7; ++i) {
        if (i%2 == 0) {
            for (int j = 0; j <8; ++j) {
                printf("\t");
            }
            printf("[]\tF%d\n",count);
            count++;
        }else {
            printf("\n");
        }
    }
}

void defaultDisplay(){
    int cardPrinted = 0;
    int foundationsPrinted = 0;
    int lineOn = 1;
    Card* currentCard = getDeck()->head;
    do{
        if (currentCard->faceUp || strcmp(getLastCommand(), "SW\n") == 0 )
            printf("%s\t",currentCard->name);
        else
            printf("[]\t");
        if ((cardPrinted +1) % 7 == 0){
            if (foundationsPrinted != 4 && lineOn%2 == 1) {
                printf("\t[]\tF%d", foundationsPrinted + 1);
                foundationsPrinted++;
            }
            printf("\n");
            lineOn++;
        }
        cardPrinted++;
        if (currentCard->next != NULL)
            currentCard = currentCard->next;
    }while (cardPrinted != 52 || foundationsPrinted != 4);
    printf("\n");
}

void gameDisplay(){
    Card* currentCard;
    int cardsPrinted = 0;
    int currentLine = 0;
    int line = 0;
    int finishesPrinted = 0;
    int finishedLines[7]; //0 = not finished, 1 = is finished.

    for (int i = 0; i < 7; i++) {
        if(getBoard()[i].head != NULL)
            finishedLines[i]=0;
        else
            finishedLines[i]=1;
    }

    do {
        if (finishedLines[currentLine] == 0) {
            currentCard = getBoard()[currentLine].head;
            for (int i = 0; i < line; i++){
                currentCard = currentCard->next;
            }
            if (currentCard->faceUp)
                printf("%s\t",currentCard->name);
            else
                printf("[]\t");
            if (currentCard->next == NULL)
                finishedLines[currentLine] = 1;
            cardsPrinted++;
        } else
            printf("\t");
        if (currentLine == 6) {
            if (line == 0 || line == 2 || line == 4 || line == 6) {
                printf("\t[]\tF%d", finishesPrinted + 1);
                finishesPrinted++;
            }
            currentLine = 0;
            line++;
            printf("\n");
        }
        else
            currentLine++;
    }while (cardsPrinted!=52 || finishesPrinted != 4);
}

void displayInfolines() {
    printf("LAST Command: %s", getLastCommand());
    if (getErrorMessage() == NULL || strcmp(getErrorMessage(), "") == 0) //if errormessage points to null or is empty.
        printf("Message: OK\n");
    else
        printf("Message: %s\n",getErrorMessage());
    setErrorMessage("");
}
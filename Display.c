//
// Created by Rawfodog on 01-04-2022.
//
#include <stdio.h>
#include "Header.h"

void displayInfolines();

void updateDisplay(){
    system("cls");

    if (!isDeckLoaded()){
        displayEmpty();
    }else{
        //switch (expression) {

        //}
    }


    for (int i = 0; i < 7; ++i) {
        printf("C%d\t",i+1);
    }
    printf("\n\n");

    int cardsPrinted = 0;
    int currentLine = 0;
    int line = 0;
    int finishedLines[7]; //0 = not finished, 1 = is finished.

    for (int i = 0; i < 7; i++) {
        finishedLines[i]=0;
    }

    /*if (!isDeckLoaded()){

    }*/














/*
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

        Card* currentSpot = getBoard()[currentLine];

        if(finishedLines[currentLine] == 0){
            for (int i = 0; i < line-1; i++) {
                currentSpot = currentSpot->next;
            }
            if (currentSpot->next->name[0] == '0')
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

    //prep to print the 4 piles of suits.
    printf("\n\n");
    int i = 0;
    while (i < 4) {
        Card *pile = getBoard()[7+i];
        if (pile == NULL) { //check if pile is empty
            printf("[]\t");
        } else{
            while (pile->next->name[0] == '0') {
                pile = pile->next;
            }
            printf("%s\t",pile->name);
        }
        i++;
    } */
}

void displayEmpty(){
    system("cls");
    for (int i = 0; i < 7; ++i) {
        printf("C%d\t",i+1);
    }
    printf("\n\n");

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
    displayInfolines();
}

void displayInfolines(char* msg) {
    printf("LAST Command: %s\n", getLastCommand());
    showMessage("OK");
}
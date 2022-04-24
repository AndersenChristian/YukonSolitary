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
        //
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
}

void displayEmpty(){
    //system("cls");
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
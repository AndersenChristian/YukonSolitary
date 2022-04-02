//
// Created by Rawfodog on 01-04-2022.
//
#include <stdio.h>
#include "Header.h"


void updateDisplay(){
    int i = 0;


    while (i < 52) {
        if(i%7 == 0) {
            printf("\n");
        }
        if(getCard(i)->faceUp==1)
            printf("%c%c\t",*(getCard(i)->name),*((getCard(i)->name)+1));
        else
            printf("[]\t");
        i++;
    }
}
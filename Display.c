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
        printf("%s\t",getCard(i).name);
        i++;
    }
}
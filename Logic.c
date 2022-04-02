//
// Created by Rawfodog on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Header.h"

void setupGame() {
    createDeck();
    setupCards();
    shuffle();
}

extern void playGame() {
    //do {
        updateDisplay();
    //}while(winCondition()==true);
}

bool winCondition(){
    //todo test for win condition
}

void shuffle() {
    Card * ptr = getDeck();
    int rannum1, rannum2;
    srand(time(NULL));
    for (int i = 0; i < 100000; ++i) {
        rannum1 = (rand()%52) + 1;
        rannum2 = (rand()%52) + 1;
        swap( ptr+rannum1, ptr+rannum2);
    }
}

void swap(Card *a, Card *b){
    Card temp = *a;
    *a = *b;
    *b = temp;
}
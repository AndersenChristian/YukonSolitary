//
// Created by Christian Andersen on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Header.h"

void setupGame() {
    setupCards();
    shuffle();
    setupBoard();
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
        rannum1 = (rand()%52);
        rannum2 = (rand()%52);
        swap( ptr+rannum1, ptr+rannum2);
    }
}

void swap(Card *a, Card *b){
    Card temp = *a;
    *a = *b;
    *b = temp;
}

void setupBoard(){
    Card * ptr = getDeck();
    Card ** board = getBoard();

    for (int i = 0; i<7; i++){ //create the first point in the linked list
        board[i] = &ptr[i];
    }

    for (int i = 7; i < 52; ++i) { //starts in 7, as those are the unsigned card atm.
        Card * currentSpot = board[i%7];
        while(currentSpot->next != NULL) {
            currentSpot = currentSpot->next;
        }
        currentSpot->next = &ptr[i];
    }

    /*
    for (int i = 0; i < 7; ++i) { //creates the dummy by the end.
        Card * currentSpot = board[i];
        while(currentSpot->next != NULL) {
            currentSpot = currentSpot->next;
        }
        //currentSpot->next = Card dummy;
    } */
}
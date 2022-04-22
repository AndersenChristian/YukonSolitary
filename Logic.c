//
// Created by Christian Andersen on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Header.h"

void setupGame() {
    setupCards();
    shuffle();
    setupBoard();
}

extern void playGame() {
    //do {
        updateDisplay();
        char *input = getPlayerInput();
        printf("%s", input);
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

    //creates the dummy by the end.
    for (int i = 0; i < 7; ++i) {
        Card * currentSpot = board[i];
        while(currentSpot->next != NULL) {
            currentSpot = currentSpot->next;
        }
        currentSpot->next = getCard(52+i);
        getCard(52+i)->prev = currentSpot;
    }

    //insure that the dummy at the end is also alligned with the one in the beginning.
    for (int i = 0; i < 7; ++i) {
        Card * currentSpot = board[i];
        currentSpot->prev = getCard(52+i);
        getCard(52+i)->next = currentSpot;
    }
}
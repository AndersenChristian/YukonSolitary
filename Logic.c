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
    printDeck();
    //shuffle();
    //setupBoard();
}

extern void playGame() {
    //do {
        //updateDisplay();
    //}while(winCondition()==true);
}

bool winCondition(){
    //todo test for win condition
}

void shuffle() {
    LinkedList deck = *getDeck();
    Card *cardH = deck.head;
    Card *cardN = cardH->next;
    Card *card1 = cardH;
    Card *cardP = cardH;
    int j = 0;
    srand(time(NULL));
    while (j < 10000){
        int randomNumber = (rand()%52)+1;
        for (int i = 0; i <= randomNumber; ++i) {
            card1 = card1->next;
        }
        cardP->prev = cardH;
        cardH->prev = card1;
        cardH->next->prev = NULL;

        deck.head = cardN;
        cardH->next = cardP;
        card1->next = cardH;
        cardP = card1->next;
        j++;
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
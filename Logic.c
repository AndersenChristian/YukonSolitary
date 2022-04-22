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
    setupBoard();
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
    Card *cardH; //Dette skal være en getMetode kaldet getLinkedList.
    Card *card1 = cardH;
    Card *cardP = cardH;
    srand(time(NULL));
    int randomNumber = (rand()%52)+1;
    for (int i = 0; i <= randomNumber; ++i) {
        card1 = card1->next;
    }

    cardP->prev = cardH;
    cardH->prev = card1;
    cardH->next->prev = NULL;

    //Updater linkedList metode her.
    cardH->next = cardP;
    card1->next = cardH;
    cardP = card1->next;

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
        boardSlots[i].head = ptrToCard;
        boardSlots[i].tail = ptrToCard;
        ptrToCard = ptrToCard->next;
        boardSlots[i].head->next = NULL;
        boardSlots[i].head->prev = NULL;
    }

    for (int i = 7; i < 52; ++i) { //starts in 7, as those are the unsigned card atm.
        Card* currentSlotsLastCard = boardSlots[i%7].tail;
        currentSlotsLastCard->next = ptrToCard;
        ptrToCard->prev = currentSlotsLastCard;
        boardSlots[i%7].tail = ptrToCard;
        ptrToCard = ptrToCard->next;
        //if (i%7 > 3)
    }
}
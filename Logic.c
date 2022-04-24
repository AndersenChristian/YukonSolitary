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
    displayEmpty();
    do {
        nextPlayerInput();
        displayEmpty();
    }while(!isGameWon());
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
    Card * ptrToCard = getDeck()->head;
    LinkedList* boardSlots = getBoard();

    for (int i = 0; i<7; i++){ //create the first point in the linked list
        boardSlots[i].head = ptrToCard;
        boardSlots[i].tail = ptrToCard;
        ptrToCard = ptrToCard->next;
        boardSlots[i].head->next = NULL;
        boardSlots[i].head->prev = NULL;
    }

    int currentList = 0;
    int offset = 0;
    for (int i = 7; i < 52; ++i) { //starts in 7, as those are the unsigned card atm.
        Card* currentSlotsLastCard = boardSlots[currentList].tail + 1;
        currentSlotsLastCard->next = ptrToCard;
        ptrToCard->prev = currentSlotsLastCard;
        boardSlots[i%7].tail = ptrToCard;
        ptrToCard = ptrToCard->next;
        if (i == 37 || i == 42 || i == 46 || i == 49 || i == 51 || i == 52)
            offset++;
        if (i == 12 || i == 18 || i == 24 || i == 30 || i == 36 || i == 41 || i == 45 || i == 48 || i == 50 || i == 51)
            currentList = 0 + offset;
    }
}

void saveGame(char* filename){
    // TODO to be implemented

}

void exitGame(){
    printf("\n---Exiting Game---\n");
    exit(0);
}
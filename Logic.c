//
// Created by Christian Andersen on 01-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Header.h"

void setupGame() {
    setupCards();
    printDeck();
    //shuffle();
    setupBoard();
    updateDisplay();
}

extern void playGame() {
    displayEmpty();
    do {
        processPlayerInput(getPlayerInput());
        displayEmpty(); // TODO is just display
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


    int cardsPerPile[] = {0,5,6,7,8,9,10};
    int currentList = 0;
    int amountOfCardsUsed = 7;
    do {
        if (cardsPerPile[currentList] != 0) {
            Card *currentSlotsLastCard = boardSlots[currentList].tail;
            currentSlotsLastCard->next = ptrToCard;
            ptrToCard->prev = currentSlotsLastCard;
            boardSlots[currentList].tail = ptrToCard;
            ptrToCard = ptrToCard->next;
            boardSlots[currentList].tail->next=NULL;
            cardsPerPile[currentList]--;
            amountOfCardsUsed++;
        }
        //ensure we get around
        if (currentList == 6)
            currentList = 0;
        else
            currentList++;
    } while (amountOfCardsUsed != 52);
}

void saveGame(char* filename){
    // TODO to be implemented

}

void exitGame(){
    printf("\n---Exiting Game---\n");
    exit(0);
}


void processPlayerInput(char* string){
    //printf("Inputted String: %s\n", string);

    setLastCommand(string);

    if (string[2] == ':' && string[5] == '-' && string[6] == '>'){ // Game Move
        // Get everything from input
        char fromColumn[3];
        char card[3];
        char toColumn[3];

        memcpy(fromColumn, string, 2);
        memcpy(card, &string[3], 2);
        memcpy(toColumn, &string[7], 2);

        card[2] = '\0';
        toColumn[2] = '\0';

        // Process it

    } else {
        char initials[3];
        memcpy(initials, string, 2);
        //printf("Initials: %s\n", initials);

        // Things to process
        if (strcmp(initials, "LD") == 0){

        } else if (strcmp(initials, "SW") == 0){

        } else if (strcmp(initials, "SI") == 0){

        } else if (strcmp(initials, "SR") == 0){

        } else if (strcmp(initials, "SD") == 0){
            char* filename = &string[3];
            saveGame(filename);
        } else if (strcmp(initials, "QQ") == 0){
            exitGame();
        } else if (strcmp(initials, "P ") == 0){

        } else if (strcmp(initials, "Q ") == 0){

        }
    }
}
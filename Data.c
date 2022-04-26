//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList deck;
LinkedList boardSlots[11];

char* lastCommand = "\n";
char* errorMessage;

bool deckLoaded = false;
bool isGameDone = false;
bool deckShuffled = false;
bool gameStarted = false;

void initDeck() {
    deck.length = 0;

    deck.head = (Card *) malloc(sizeof(Card));
    deck.tail = (Card *) malloc(sizeof(Card));

    deck.head = NULL;
    deck.tail = NULL;
}

void pushCardToDeck(char name[3]){
    Card card;
    card.name[0] = name[0];
    card.name[1] = name[1];
    card.name[2] = '\0';
    addCard(&deck, &card);
}
LinkedList* getDeck(){
    return &deck;
}

LinkedList* getBoard(){
    return boardSlots;
}

void printDeck(){
    printList(&deck);
}

bool isDeckLoaded(){
    return deckLoaded;
}

void setIsDeckLoaded(bool flag){
    deckLoaded = flag;
}

bool isGameWon(){
    return isGameDone;
}

void setLastCommand(char* command){
    lastCommand = command;
}

char* getLastCommand(){
    return lastCommand;
}

void setErrorMessage(char message[]){
    if (errorMessage != NULL){
        free(errorMessage);
        errorMessage = NULL;
    }
    errorMessage = malloc(sizeof(&message));
    strcpy(errorMessage, message);
}

char* getErrorMessage(){
    return errorMessage;
}

bool hasGameStarted(){
    return gameStarted;
}

void setGameStarted(bool flag){
    gameStarted = flag;
}
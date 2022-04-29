//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList deck;
LinkedList boardSlots[11]; //0-6 Cards, 7-11 Foundations [C, S, D, H]

char lastCommand[255];
char errorMessage[50]; //set by the various methods of the program to proper display if anything goes wrong.

//the following boolean values are used to keep a track of the current game-state
bool deckLoaded = false;
bool isGameDone = false;
bool gameStarted = false;

void initDeck() {
    deck.length = 0;

    //deck.head = (Card *) malloc(sizeof(Card));
    //deck.tail = (Card *) malloc(sizeof(Card));

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
LinkedList* dataptrToDeck(){
    return &deck;
}

LinkedList* dataptrToBoard(){
    return boardSlots;
}

char* dataPTR_lastCommand(){
    &lastCommand;
}

bool* dataPTR_DeckLoaded(){
    &deckLoaded;
}

bool* dataPTR_IsGameDone(){
    &isGameDone;
}

bool* dataPTR_GameStarted(){
    &gameStarted;
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

char* getLastCommand(){
    return lastCommand;
}

void setErrorMessage(char message[]){
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
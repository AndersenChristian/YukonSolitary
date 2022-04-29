//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList deck = {0, NULL, NULL};
LinkedList boardSlots[11]; //0-6 Cards, 7-11 Foundations [C, S, D, H]

char lastCommand[255] = "\n";
char errorMessage[255]; //set by the various methods of the program to proper display if anything goes wrong.

//the following boolean values are used to keep a track of the current game-state
bool deckLoaded = false;
bool isGameDone = false;
bool gameStarted = false;

LinkedList* dataPTR_ToDeck(){
    return &deck;
}

LinkedList* dataPTR_ToBoard(){
    return boardSlots;
}

char* dataPTR_lastCommand(){
    return lastCommand;
}

char* dataPTR_ErrorMessage(){
    return errorMessage;
}

bool* dataPTR_DeckLoaded(){
    return &deckLoaded;
}

bool* dataPTR_IsGameDone(){
    return &isGameDone;
}

bool* dataPTR_GameStarted(){
    return &gameStarted;
}

void setErrorMessage(char* message){
    strcpy(errorMessage, message);
}
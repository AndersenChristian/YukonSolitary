//
// Created by Christian Andersen on 02-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef YUKON_HEADER_H
#define YUKON_HEADER_H

typedef struct Card Card;
typedef struct LinkedList LinkedList;

// --- Structs ---
struct Card {
    char name[3];
    bool faceUp;
    Card* prev;
    Card* next;
};

struct LinkedList {
    int length;
    Card* head;
    Card* tail;
};

void addCard(LinkedList* list, Card* pCard);
Card* getCard(LinkedList* list, int index);
void printList(LinkedList* list);


//global variables
#define DECK_SIZE 52+11 //the 11 are dummies for linked lists


//Methods
//Data
void initDeck();
bool isDeckLoaded();
void pushCardToDeck(char name[3]);
LinkedList* getDeck();
LinkedList* getBoard();
void printDeck();

//Logic
void setupGame();
void playGame();
bool winCondition();
void shuffle();
void swap(Card*, Card*);
void setupBoard();


//Interface
void updateDisplay();
void displayEmpty();
void displayInfolines();

//Reader
void setupCards();

//PlayerInput
void nextPlayerInput();
char* getPlayerInput();
void processPlayerInput(char string[]);
void showMessage(char* msg);
char* getLastCommand();

#endif //YUKON_HEADER_H

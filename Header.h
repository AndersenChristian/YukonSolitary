//
// Created by Christian Andersen on 02-04-2022.
//
#include <stdbool.h>

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




//global variables
#define DECK_SIZE 52+11 //the 11 are dummies for linked lists


//Methods
//Data
Card * getCard(int position);
void setCardName(char ptr[2], int cardNumber);
Card * getDeck ();
Card ** getBoard();

//Logic
void setupGame();
void playGame();
bool winCondition();
void shuffle();
void swap(Card*, Card*);
void setupBoard();


//Interface
void updateDisplay();

//Reader
void setupCards();

//PlayerInput
char* getPlayerInput();

#endif //YUKON_HEADER_H

//
// Created by Rawfodog on 02-04-2022.
//
#include <stdbool.h>

#ifndef YUKON_HEADER_H
#define YUKON_HEADER_H

 typedef struct{
    char name[2];
    unsigned int faceUp; //0 = faceDown, 1 = faceUp
} Card;

//global variables
#define DECK_SIZE 52


//Methods
//Data
void createDeck();
Card * getCard(int position);
void setCardName(char ptr[2], int cardNumber);
Card * getDeck ();

//Logic
void setupGame();
void playGame();
bool winCondition();
void shuffle();
void swap(Card*, Card*);


//Interface
void updateDisplay();

//Reader
void setupCards();

#endif //YUKON_HEADER_H

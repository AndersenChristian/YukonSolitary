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

LinkedList addCard(LinkedList* list, Card* pCard){
    if (list->head == NULL){
        list->head = pCard;
        list->tail = pCard;
    } else {
        Card oldTail = *list->tail;
        oldTail.next = pCard;
        pCard->prev = &oldTail;
        list->tail = pCard;
    }
    list->length++;
}

LinkedList printList(LinkedList* list){
    Card* currentCard = list->head;
    for (int i = 0; i < list->length; ++i) {
        printf(currentCard->name);
        printf("\t");
        currentCard = currentCard->next;
    }
}




//global variables
#define DECK_SIZE 52+11 //the 11 are dummies for linked lists


//Methods
//Data
Card * getCard(int position);
void pushCardToDeck(char name[3]);
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

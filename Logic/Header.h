//
// Created by Christian Andersen on 02-04-2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef YUKON_HEADER_H
#define YUKON_HEADER_H

/*
typedef struct Card Card;
typedef struct LinkedList LinkedList;

typedef enum {C = 0, D, H, S} CARD_SUITS;

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
*/

void addCard(const char*);
Card* getCardByIndex(LinkedList* list, int index);
Card* getCardByName(LinkedList* list, char* name);
Card* getLastCard(LinkedList* list);
void printList(LinkedList* list);
void moveCardToStack(Card* cardToMove, Card* destination);
void moveCardToFoundation(LinkedList* foundation, Card* card);


//global variables
#define DECK_SIZE (52)



#endif //YUKON_HEADER_H

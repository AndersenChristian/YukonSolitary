//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"

#include <stdio.h>

LinkedList deck;
struct Card* boardSlots[11];


void initDeck() {
    deck.length = 0;

    deck.head = (Card *) malloc(sizeof(Card));
    deck.tail = (Card *) malloc(sizeof(Card));

    deck.head = NULL;
    deck.tail = NULL;
}
Card * getCard(int position){
}

void pushCardToDeck(char name[3]){
    Card card;
    card.name[0] = name[0];
    card.name[1] = name[1];
    card.name[2] = "\0";
    addCard(&deck, &card);
}
LinkedList* getDeck(){
    return &deck;
}

LinkedList* getBoard(){
    return (LinkedList *) boardSlots;
}

void printDeck(){
    printList(&deck);
}

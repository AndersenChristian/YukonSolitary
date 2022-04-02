//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"

struct linkedList_note {
    struct Card data;
    struct linkedList_note* next;
};

struct Card deck[DECK_SIZE];

void createDeck(){
    struct linkedList_note* boardSlots[7];

    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i].name[0] = 'a';
        deck[i].name[1] = 'b';
    }
}

struct Card getCard(int position){
    return deck[position];
}

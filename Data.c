//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"

#include <stdio.h>

struct linkedList_note {
    Card data;
    struct linkedList_note* next;
};

Card deck[DECK_SIZE];

void createDeck(){
    struct linkedList_note* boardSlots[7];

    for (int i = 0; i < DECK_SIZE; ++i) {
        deck[i].faceUp = 1;
    }
}

Card * getCard(int position){
    return &deck[position];
}

void setCardName(char * ptr, int cardNumber){
    printf("%c%c\n",*ptr,*(ptr+1));
    deck[cardNumber].name[0] = *ptr;
    deck[cardNumber].name[1] = *(ptr+1);
}

Card * getDeck (int i){
    return &deck[i];
}

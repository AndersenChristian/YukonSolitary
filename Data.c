//
// Created by Rawfodog on 01-04-2022.
//
#include "Header.h"

#include <stdio.h>

Card deck[DECK_SIZE];
struct Card* boardSlots[11];

Card * getCard(int position){
    return &deck[position];
}

void setCardName(char * ptr, int cardNumber){
    deck[cardNumber].name[0] = *ptr;
    deck[cardNumber].name[1] = *(ptr+1);
    deck[cardNumber].name[2] = '\0';
    deck[cardNumber].faceUp = 1; //TODO: delete (only for testing)
}

Card * getDeck (){
    return (Card *) &deck;
}

Card ** getBoard(){
    return (Card**) &boardSlots;
}
